#include "negative.h"

void Negative::Apply(Image& image) {
    for (int y = 0; y < image.GetHeight(); ++y) {
        for (int x = 0; x < image.GetWidth(); ++x) {
            Color rgb = image.GetColor(x, y);
            rgb.r = 1 - rgb.r;
            rgb.g = 1 - rgb.g;
            rgb.b = 1 - rgb.b;
            image.SetColor(rgb, x, y);
        }
    }
}
