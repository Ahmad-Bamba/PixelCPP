#pragma once

#include <array>
#include <memory>
#include <ranges>
#include "tile.h"
#include "palette.h"
#include "graphic.h"
#include "color.h"

namespace SpriteEngine{
    // dimension show how many tiles big in each direction    
    template<std::size_t N, std::size_t M>
    class Background : public Graphic {
        std::array<std::array<Tile, N>, M> tiles { };
        // must set the color palette to use
        std::shared_ptr<PaletteBase> color_palette { new Palette<0>() };
        // treat the first color of the palette as a transparent color
    public:
        template<std::size_t I, std::size_t J>
        void setTile(Tile t) {
            tiles[J][I] = t;
        }

        void setTile(std::size_t i, std::size_t j, Tile t) {
            tiles[j][i] = t;
        }

        template<std::size_t I, std::size_t J>
        inline Tile& getTile() {
            return tiles[J][I];
        }

        Tile& getTile(std::size_t i, std::size_t j) {
            return tiles[j][i];
        }

        std::shared_ptr<PaletteBase> getPalette() {
            return color_palette;
        }

        void setPalette(std::shared_ptr<PaletteBase> p) {
            color_palette = p;
        }

        template<std::size_t PN>
        void setPalette(Palette<PN>& p) {
            color_palette.reset(new Palette<PN>(p));
        }

        template<Integral T>
        void setTileRows(std::vector<T> set_rows, Tile t) {
            using std::views::iota;
            using std::views::take;

            for (auto row : set_rows) {
                for (int i : iota(0) | take(N))
                    tiles[row][i] = t;
            }
        }

        void setAllTiles(Tile t) {
            using std::views::iota;
            using std::views::take;

            for (auto j : iota(0) | take(M))
                for (auto i : iota(0) | take(N))
                    tiles[j][i] = t;
        }

        std::size_t getTileWidth() {
            return N;
        };

        std::size_t getTileHeight() {
            return M;
        };

        bool transparent { false };
        bool isTransparent() { return transparent; }
    };
}