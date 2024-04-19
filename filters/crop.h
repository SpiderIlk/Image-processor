#pragma once
#include "filter.h"
#include "grayscale.h"

class Crop : public Filter {
public:
    Crop(int width_target, int height_target) : width_target(width_target), height_target(height_target) {
    }

    void Apply(Image& image) override;

    ~Crop() override = default;

    int width_target;
    int height_target;
};
