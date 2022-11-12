#pragma once 

#include "color.h"
#include <cstddef>
#include <initializer_list>
#include <algorithm>


namespace SpriteEngine {
	struct PaletteBase {
		virtual Color const& get(std::size_t i) const = 0;
		virtual void set(std::size_t i, Color const& c) = 0;
		virtual void swap(std::size_t i, std::size_t j) = 0;
		virtual constexpr std::size_t get_size() = 0;
	};

	template<std::size_t N>
	class Palette : public PaletteBase {
		std::array<Color, N> colors{ };

	public:
		Palette() = default;

		Palette(Palette const& other) {
			for (int i = 0; i < N; i++)
				colors[i] = other.colors[i];
		}

		Palette(std::array<Color, N> arr) {
			for (int i = 0; i < N; i++)
				colors[i] = arr[i];
		}

		template<Integral T>
		Palette(std::array<std::array<T, 3>, N> arr) {
			for (int i = 0; i < arr.size(); i++) {
				colors[i] = Color(arr[i]);
			}
		}

		// compile-time get function
		template<std::size_t I>
		constexpr Color const& get() const {
			return colors[I];
		}

		Color const& get(std::size_t i) const {
			return colors[i];
		}

		void set(std::size_t i, Color const& c) {
			copy(colors[i], c);
		}

		void set(std::size_t i, uint8_t r, uint8_t g, uint8_t b) {
			colors[i].red = r;
			colors[i].green = g;
			colors[i].blue = b;
		}


		void set(std::size_t i, std::array<uint8_t, 3> arr) {
			colors[i].red = arr[0];
			colors[i].green = arr[1];
			colors[i].blue = arr[2];
		}

		template<std::size_t I, std::size_t J>
		constexpr void swap() {
			std::iter_swap(colors.begin() + I, colors.begin() + J);
		}

		void swap(std::size_t i, std::size_t j) {
			std::iter_swap(colors.begin() + i, colors.begin() + j);
		}

		constexpr std::size_t get_size() {
			return N;
		}
	};
}
