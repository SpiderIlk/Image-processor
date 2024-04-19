#include "sharpening.h"

void Sharpening::Apply(Image& image) {
    Image image_copy = image;

    int height = image.GetHeight();
    int width = image.GetWidth();

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {

            Color cur_pixel = image_copy.GetColor(x, y);
            Color up = image_copy.GetColor(x, std::max(0, y - 1));
            Color down = image_copy.GetColor(x, std::min(height - 1, y + 1));
            Color left = image_copy.GetColor(std::max(0, x - 1), y);
            Color right = image_copy.GetColor(std::min(width - 1, x + 1), y);

            Color new_color;
            new_color.r = std::min(1.0f, std::max(0.0f, 5 * cur_pixel.r - up.r - down.r - left.r - right.r));  // NOLINT
            new_color.g = std::min(1.0f, std::max(0.0f, 5 * cur_pixel.g - up.g - down.g - left.g - right.g));  // NOLINT
            new_color.b = std::min(1.0f, std::max(0.0f, 5 * cur_pixel.b - up.b - down.b - left.b - right.b));  // NOLINT

            image.SetColor(new_color, x, y);
        }
    }
}
