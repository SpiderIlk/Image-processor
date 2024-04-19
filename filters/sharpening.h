#pragma once
#include <algorithm>
#include "filter.h"

class Sharpening : public Filter {
public:
    void Apply(Image& image) override;

    ~Sharpening() override = default;
};
