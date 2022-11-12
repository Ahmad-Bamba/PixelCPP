#pragma once

#include <vector>
#include <cstddef>
#include <fstream>
#include <variant>
#include "color.h"
#include "palette.h"

namespace SpriteEngine {
	struct Image {
		std::vector<std::vector<std::size_t>> paletteIndices { };
		std::size_t width { };
		std::size_t height { };

		Image() = default;
		Image(std::size_t w, std::size_t h, std::vector<std::vector<std::size_t>> v) :
		width(w), height(h), paletteIndices(v) { }
	};

	struct PNGChunk {
			uint32_t length;
			uint32_t chunk_type;
			std::vector<uint8_t> chunk_data;
			uint32_t CRC;
	};

	class PNGImageFile {
		/* PNG format specific members */
		using PNGHeader = std::array<uint8_t, 8>;

		struct PNGFileData {
			PNGHeader header { 137, 80, 78, 71, 13, 10, 26, 10 };
			std::vector<PNGChunk> chunks;
		} file_data;

		
	public:
		// empty for now
		Image extractPixels() { return Image(); }

		template<std::size_t N>
		Palette<N> extractPalette() { }

		void process();
	};

	class BMPImageFile {
		/* BMP format specific members */
		struct BMPDataStruct {
			using BitMask = std::variant<std::array<uint8_t, 12>, std::array<uint8_t, 16>>;
			std::array<uint8_t, 14> file_header;
			std::vector<uint8_t> DIB_header;
			BitMask pixel_format;
			std::vector<int> color_table; // convert to palette
			std::vector<int> raw_pixels;
		} header;

	public:
		// empty for now
		Image extractPixels() { return Image(); }

		template<std::size_t N>
		Palette<N> extractPalette() { }


		void process();
	};

	// If we want to be able to import PNG and BMP files into the engine, 
	// they are two different file formats difficult to encoe with inheritance.
	// But variants offer a better solution.
	using ImageFile = std::variant<PNGImageFile, BMPImageFile>;

	// method allows us to process any file
	void process_image(ImageFile);
}

