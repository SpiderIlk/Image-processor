#include "grayscale.h"

void Grayscale::Apply(Image& image) {
    for (int y = 0; y < image.GetHeight(); ++y) {
        for (int x = 0; x < image.GetWidth(); ++x) {
            Color rgb = image.GetColor(x, y);
            float new_color = 0.299f * rgb.r + 0.587f * rgb.g + 0.114f * rgb.b;  // NOLINT
            rgb.r = new_color;
            rgb.g = new_color;
            rgb.b = new_color;
            image.SetColor(rgb, x, y);
        }
    }
}
