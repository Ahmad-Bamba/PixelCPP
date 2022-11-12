#include "image.h"

#include <iostream>

namespace SpriteEngine {
    void PNGImageFile::process() {
        /* PNG specific processing things */
        std::cout << "PNG process." << std::endl;
    }

    void BMPImageFile::process() {
        /* BMP specific processing things */
        std::cout << "BMP process." << std::endl;
    }

    void process_image(ImageFile f) {
        std::visit([](auto& x) {
            x.process();
        }, f);
    }
}
