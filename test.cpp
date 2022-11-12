#include "sprite_engine.h"

#include <memory>
#include <iostream>
#include <cassert>

//using namespace std;

using namespace SpriteEngine;

// maybe a lot of boilerplate, but rather extendible
int main() {

	// first, use the factory to make the effects we want to use
	std::unique_ptr<GFX::TileFactory> sparkle_factory (std::make_unique<GFX::GFXSparkleFactory>());
	std::unique_ptr<GFX::TileFactory> fuzz_factory(std::make_unique<GFX::GFXFuzzFactory>());
	auto bg_tile (fuzz_factory->create<Tile>());
	auto sparkle1_tile (sparkle_factory->create<Tile>());
	auto sparkle2_tile (sparkle_factory->create<Tile>());
	
	// next, make the graphics
	std::shared_ptr<Sprite> sparkle1 = std::make_shared<Sprite>();
	sparkle1->setPalette(GFX::sprite_palette1);
	sparkle1->setTile<0, 0>(*sparkle1_tile);
	std::shared_ptr<Sprite> sparkle2 = std::make_shared<Sprite>();
	sparkle2->setPalette(GFX::sprite_palette2);
	sparkle2->setTile<0, 0>(*sparkle2_tile);
	std::shared_ptr<Background<18, 20>> bg = std::make_shared<Background<18, 20>>();
	bg->setAllTiles(*bg_tile);
	bg->setPalette(GFX::background_palette);

	// now, make the layers and populate them with the elements we made
	RenderLayer bg_layer;
	bg_layer.elements.push_back({ bg, {0, 0} });
	RenderLayer sprite_layer;
	sprite_layer.elements.push_back({ sparkle1, { 10, 10 }});
	sprite_layer.elements.push_back({ sparkle2, { 72, 80 }});

	// set up the render window with our layers
	RenderWindow rwindow { 144, 160 };
	rwindow.addLayerToTop(bg_layer);
	rwindow.addLayerToTop(sprite_layer);

	std::cout << "Writing file..." << std::endl;
	// render the test image as a .ppm file
	rwindow.render("test_image");
	std::cout << "Done!";
}
