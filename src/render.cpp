#include "render.h"
#include "image.h"
#include "color.h"
#include <thread>
#include <ranges>
#include <algorithm>
#include <iostream>

namespace SpriteEngine {
    RenderWindow::RenderWindow(std::size_t w, std::size_t h) {
        width = w;
        height = h;
    }

    void RenderWindow::addLayerToBottom(RenderLayer& layer) {
        layers.insert(layers.begin(), layer);
    }

    void RenderWindow::addLayerToTop(RenderLayer& layer) {
        layers.push_back(layer);
    }

    void RenderWindow::swapLayers(int a, int b) {
        std::iter_swap(layers.begin() + a, layers.begin() + b);
    }

    void RenderWindow::render(std::string filepath) {
        using std::views::iota;
        using std::views::take;

        std::ofstream writeback(filepath + ".ppm");
        if (!writeback) {
            std::cerr << "Could not open desired PNG file!" << std::endl;
            return;
        }

        // Compile the render into a pixel array
        // with white as the default background color
        std::vector<Color> pixels { width * height, WHITE };

        // for every layer
        for (auto& layer : layers) {
            auto loffset_x = layer.pos.first;
            auto loffset_y = layer.pos.second;

            // for every element in every layer
            for (auto& re : layer.elements) {
                int eoffset_x = loffset_x + re.pos.first;
                int eoffset_y = loffset_y + re.pos.second;

                auto tile_width = re.element->getTileWidth();
                auto tile_height = re.element->getTileHeight();

                auto palette = re.element->getPalette();
                // for every tile in every element
                for (auto j : iota(0) | take(tile_height)) {
                    int toffset_y = 8*j + eoffset_y;
                    for (auto i : iota(0) | take(tile_width)) {
                        int toffset_x = 8*i + eoffset_x;
                        Tile t = re.element->getTile(i, j);
                        // for every pixel in every tile
                        for (auto tj : iota(0) | take(8)) {
                            auto poffset_y = toffset_y + tj;
                            for (auto ti : iota(0) | take(8)) {
                                auto poffset_x = toffset_x + ti;
                                auto pi = poffset_x + width * poffset_y;
                                // if the pixel is in the window, render the color 
                                if (pi < width * height) {
                                    auto color_index = t.getColorIndexAt(ti, tj);
                                    if (!(re.element->isTransparent() && color_index == 0)) {
                                        pixels[pi] = palette->get(color_index); 
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        dump(writeback, pixels);
    }

    // https://en.wikipedia.org/wiki/Netpbm
    void RenderWindow::dump(std::ofstream& file, std::vector<Color>& pixels) {
        // dumps as a netppm file

        // write the file format, width, and height
        file << "P3" << " " << width << " " << height << " " << 255 << std::endl;
        // write every pixel in the form of 8 bit numbers "RGB"
        int count = 0;
        for (auto const& pixel : pixels) {
            file << static_cast<int>(pixel.red) << ' ' << static_cast<int>(pixel.green) << ' ' << static_cast<int>(pixel.blue) << ' ';
            count++;
            if (count > width) {
                file << std::endl;
                count = 0;
            }
        }
        // file.write(reinterpret_cast<char const*>(&pixels[0]), sizeof(pixels));
    }
}
