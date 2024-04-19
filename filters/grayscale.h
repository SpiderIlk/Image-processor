#pragma once
#include "filter.h"

class Grayscale : public Filter {
public:
    void Apply(Image& image) override;

    ~Grayscale() override = default;
};
