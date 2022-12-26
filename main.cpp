#include <iostream>
#include <ostream>

#include "vec3.h"
#include "color.h"

int main() {
    // Image
    const int image_width = 256;
    const int image_height = 256;

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int y = image_height - 1; y >= 0; --y) {
        std::cerr << "\rLines remaining " << y << ' ' << std::flush;
        for (int x = 0; x < image_width; ++x) {
            color pixel_color(double(x) / (image_width - 1),
                              double(y) / (image_height - 1), 0.25);
            write_color(std::cout, pixel_color);
        }
    }
    std::cerr << "\nDone!" << std::endl;
    return 0;
}
