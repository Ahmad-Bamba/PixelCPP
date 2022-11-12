#pragma once

#include "abstract_factory.h"
#include "image.h"
#include "palette.h"
#include "tile.h"
#include "color.h"
#include <memory>

namespace SpriteEngine {
    namespace GFX {
       std::vector<std::vector<std::size_t>> raw
        {
            { 0, 1, 0, 1, 0, 1, 0, 1,  0, 0, 0, 0, 0, 0, 0, 0 },
            { 1, 0, 1, 0, 1, 0, 1, 0,  0, 0, 0, 1, 0, 0, 0, 0 },
            { 0, 1, 0, 1, 0, 1, 0, 1,  0, 0, 0, 0, 0, 0, 0, 0 },
            { 1, 0, 1, 0, 1, 0, 1, 0,  0, 0, 0, 0, 0, 1, 0, 0 },
            { 0, 1, 0, 1, 0, 1, 0, 1,  0, 0, 0, 0, 1, 1, 1, 0 },
            { 1, 0, 1, 0, 1, 0, 1, 0,  0, 0, 1, 0, 0, 1, 0, 0 },
            { 0, 1, 0, 1, 0, 1, 0, 1,  0, 0, 0, 0, 0, 0, 0, 0 },
            { 1, 0, 1, 0, 1, 0, 1, 0,  0, 0, 0, 0, 0, 0, 0, 0 },

            { 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 1, 1, 0, 0, 0,  0, 1, 1, 1, 1, 1, 1, 0 },
            { 0, 0, 1, 1, 1, 1, 0, 1,  0, 1, 1, 1, 1, 1, 1, 0 },
            { 0, 1, 1, 1, 1, 1, 1, 0,  0, 1, 1, 1, 1, 1, 1, 0 },
            { 0, 1, 1, 1, 1, 1, 1, 0,  0, 1, 1, 1, 1, 1, 1, 0 },
            { 0, 0, 1, 1, 1, 1, 0, 0,  0, 1, 1, 1, 1, 1, 1, 0 },
            { 0, 0, 0, 1, 1, 0, 0, 0,  0, 1, 1, 1, 1, 1, 1, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0 },
        };
        std::shared_ptr<Image> sample_image = std::make_shared<Image>(16, 16, raw);

        class Sparkle : public Tile {
        public:
            Sparkle() : Tile(8, 0, sample_image) { }
        };

        class Fuzz : public Tile {
        public:
            Fuzz() : Tile(0, 0, sample_image) { }
        };

        class Ball : public Tile {
        public:
            Ball() : Tile(0, 8, sample_image) { }
        };

        class Square : public Tile {
        public:
            Square() : Tile(8, 8, sample_image) { }
        };

        using TileFactory = abstract_factory<Tile>;
        using GFXSparkleFactory
            = concrete_factory<TileFactory, Sparkle>;
        using GFXFuzzFactory
            = concrete_factory<TileFactory, Fuzz>;
        using GFXBallFactory
            = concrete_factory<TileFactory, Ball>;
        using GFXSquareFactory
            = concrete_factory<TileFactory, Square>;

        std::array<Color, 2> raw_bg_colors = { WHITE, Color({ 163, 247, 186 })};
        std::shared_ptr<PaletteBase> background_palette = std::make_shared<Palette<2>>(raw_bg_colors);
        std::array<Color, 2> raw_sprite_colors1 = { WHITE, Color({ 7, 15, 74 })};
        std::shared_ptr<PaletteBase> sprite_palette1 = std::make_shared<Palette<2>>(raw_sprite_colors1);
        std::array<Color, 2> raw_sprite_colors2 = { WHITE, Color({ 111, 50, 156 }) };
        std::shared_ptr<PaletteBase> sprite_palette2 = std::make_shared<Palette<2>>(raw_sprite_colors2);
    }
}
