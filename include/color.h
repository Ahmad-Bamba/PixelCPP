#pragma once

#include <initializer_list>
#include <cstdint>
#include <array>
#include <type_traits>

namespace SpriteEngine {
	template<typename T>
	concept Integral = std::is_integral_v<T>;

	double constexpr FUZZY_ZERO = 0.001;

	// size should be 3 bytes
#pragma pack(push, 1)
	struct Color {
		uint8_t red { 0 };
		uint8_t green { 0 };
		uint8_t blue { 0 };

		Color() = default;
		Color(std::size_t, std::size_t, std::size_t);
		Color(Color&&) = default;
		Color(Color const&);
		Color& operator=(Color const&);
		
		template<Integral T>
		Color(std::array<T, 3>);

		std::array<double, 3> to_HSV();
	};
#pragma pack(pop)

	void copy(Color&, Color const&);

	// some useful color presets
	Color const WHITE { 255, 255, 255 };
	Color const BLACK { 0, 0, 0 };
	Color const GREY  { 128, 128, 128 };
	Color const RED   { 255, 0, 0 };
	Color const GREEN { 0, 255, 0 };
	Color const BLUE  { 0, 0, 255 };
}

