#pragma once
#include <algorithm>
#include "filter.h"
#include "grayscale.h"

class Edge : public Filter {
public:
    explicit Edge(float threshold) : threshold(threshold) {
    }

    void Apply(Image& image) override;

    ~Edge() override = default;

    float threshold;
};
