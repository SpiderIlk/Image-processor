#include "edge_detection.h"

void Edge::Apply(Image& image) {

    Grayscale filter;
    filter.Apply(image);

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

            float new_rgb = std::min(1.0f, std::max(0.0f, 4 * cur_pixel.r - up.r - down.r - left.r - right.r));

            Color new_color;
            new_color.r = (new_rgb <= threshold) ? 0.0f : 1.0f;
            new_color.g = (new_rgb <= threshold) ? 0.0f : 1.0f;
            new_color.b = (new_rgb <= threshold) ? 0.0f : 1.0f;

            image.SetColor(new_color, x, y);
        }
    }
}
