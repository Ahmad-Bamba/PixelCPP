#pragma once

#include "graphic.h"
#include "tile.h"
#include <string>
#include <memory>
#include <vector>
#include <fstream>
#include <list>

namespace SpriteEngine {
    struct RenderElement {
        std::shared_ptr<Graphic> element;
        Coordinate pos; // offset relative to the layer
    };

    struct RenderLayer {
        std::vector<RenderElement> elements;
        Coordinate pos; // offset relative to render window
        std::string name; // optional layer name
    };

    struct RenderWindow {
        RenderWindow(std::size_t, std::size_t);

        void addLayerToTop(RenderLayer&);
        void addLayerToBottom(RenderLayer&);
        void swapLayers(int a, int b);
        void render(std::string filepath);

        std::size_t width;
        std::size_t height;

    private:
        std::vector<RenderLayer> layers;
        void dump(std::ofstream& file, std::vector<Color>& pixels);
    };
}
