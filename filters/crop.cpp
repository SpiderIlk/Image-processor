#include "crop.h"

void Crop::Apply(Image& image) {
    if (height_target < image.GetHeight()) {
        image.ResizeVertical(height_target);
    }
    if (width_target < image.GetWidth()) {
        image.ResizeHorizontal(width_target);
    }
}
