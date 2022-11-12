#pragma once

#include <utility>
#include <memory>
#include <vector>
#include <algorithm>
#include <ranges>
#include "image.h"
#include "color.h"

namespace SpriteEngine {
    using Coordinate = std::pair<std::size_t, std::size_t>;
    // represents an 8x8 "tile" or contiguous slice of 
    class Tile {
        Coordinate top_corner;
        std::shared_ptr<Image> source_img;
    public:
        Tile() : top_corner(0, 0), source_img(nullptr) { }

        template<Integral T>
        Tile(T x, T y, std::shared_ptr<Image> img) : top_corner(x, y), 
                                                     source_img(img) 
        { }

        Tile(Tile const&) = default;
        Tile(Tile&&) = default;
        Tile& operator=(Tile const&) = default;
        Tile& operator=(Tile&&) = default;

        template<Integral T>
        void updateOffset(T x, T y) {
            top_corner.first = x;
            top_corner.second = y;
        }

        std::size_t getColorIndexAt(std::size_t i, std::size_t j) {
            return source_img->paletteIndices[j + top_corner.second][i + top_corner.first];
        }

        // return as one continguous data block
        auto getColorIndices() const {
            using std::views::iota;
            using std::views::take;

            std::vector<std::size_t> ret;
            ret.reserve(64);

            // start at the x and y index for the top corner and go forward 8 steps
            for (std::size_t i = top_corner.first; i < top_corner.first + 8; i++) {
                for (std::size_t j = top_corner.second; j < top_corner.second + 8; j++)
                    ret.push_back(source_img->paletteIndices[j][i]);
            }

            return ret;
        }

        Coordinate getCoords() {
            return top_corner;
        }
    };
}
