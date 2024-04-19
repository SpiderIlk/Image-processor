#pragma once
#include <algorithm>
#include <cmath>
#include "filter.h"

class Blur : public Filter {
public:
    explicit Blur(double sigma) : sigma(sigma) {
    }

    void Apply(Image& image) override;

    ~Blur() override = default;

    double sigma;
};
