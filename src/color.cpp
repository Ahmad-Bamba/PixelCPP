#include "color.h"

#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>

namespace SpriteEngine {
	Color::Color(std::size_t red, std::size_t green, std::size_t blue) {
		this->red = red;
		this->green = green;
		this->blue = blue;
	}

	template<Integral T>
	Color::Color(std::array<T, 3> arr) {
		red = arr[0] & 0xFF;
		green = arr[1] & 0xFF;
		blue = arr[2] & 0xFF;
	}

	Color::Color(Color const& other) {
		red = other.red;
		green = other.green;
		blue = other.blue;
	}

	Color& Color::operator=(Color const& other) {
		red = other.red;
		green = other.green;
		blue = other.blue;

		return *this;
	}

	std::array<double, 3> Color::to_HSV() {
		double R = static_cast<double>(red) / 255;
		double G = static_cast<double>(green) / 255;
		double B = static_cast<double>(blue) / 255;

		double Cmax = std::max({ R, G, B });
		double Cmin = std::min({ R, G, B });

		double delta = Cmax - Cmin;

		// H, S, V
		std::array<double, 3> ret{ };

		if (delta < FUZZY_ZERO) {
			ret[0] = 0;
		} else if (Cmax == R) {
			ret[0] = std::floor(60 * (static_cast<int>((G - B) / delta) % 6));
		} else if (Cmax == G) {
			ret[0] = std::floor(60 * ((B - R) / delta + 2));
		} else {
			ret[0] = std::floor(60 * ((R - G) / delta + 4));
		}

		if (Cmax < FUZZY_ZERO) {
			ret[1] = 0;
		} else {
			ret[1] = std::floor(delta / Cmax);
		}

		ret[2] = std::floor(Cmax);

		return ret;
	}

	// If I did this right these should all be right next to each other in memory
	void copy(Color& to, Color const& from) {
		to.red = from.red;
		to.blue = from.blue;
		to.green = from.green;
	}
}
