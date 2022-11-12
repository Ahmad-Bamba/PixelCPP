#pragma once

#include <vector>
#include <memory>
#include "tile.h"
#include "palette.h"
#include "graphic.h"

namespace SpriteEngine{
    // dimension show how many tiles big in each direction    
    template<std::size_t N, std::size_t M>
    class MetaSprite : public Graphic {
        std::vector<std::vector<Tile>> tiles;
        std::shared_ptr<PaletteBase> color_palette { new Palette<0>() };
    public:
        MetaSprite() {
            for (int j = 0; j < M; j++) {
                tiles.push_back(std::vector<Tile>());
                for (int i = 0; i < N; i++)
                    tiles[j].push_back(Tile());
            }
        }

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

        std::size_t getTileWidth() {
            return N;
        };

        std::size_t getTileHeight() {
            return M;
        };

        template<std::size_t PN>
        void setPalette(Palette<PN>& p) {
            color_palette.reset(new Palette<PN>(p));
        }

        bool isTransparent() { return true; }
    };

    using Sprite = MetaSprite<1, 1>;
}