#pragma once
#include "../utility/image.h"

class Filter {
public:
    Filter() = default;
    virtual ~Filter() = default;

    virtual void Apply(Image& image) = 0;
};
