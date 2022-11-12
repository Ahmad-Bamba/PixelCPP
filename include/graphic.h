#pragma once

#include "tile.h"
#include "palette.h"
#include <memory>

namespace SpriteEngine {
    struct Graphic {
        virtual Tile& getTile(std::size_t i, std::size_t j) = 0;
        virtual void setTile(std::size_t i, std::size_t j, Tile t) = 0;
        virtual std::shared_ptr<PaletteBase> getPalette() = 0;
        virtual void setPalette(std::shared_ptr<PaletteBase> p) = 0;
        virtual std::size_t getTileWidth() = 0;
        virtual std::size_t getTileHeight() = 0;
        virtual bool isTransparent() = 0; 
    };
}
