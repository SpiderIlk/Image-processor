#pragma once
#include <string>
#include "image.h"

class ImageFormat {
public:
    ImageFormat() = default;
    virtual ~ImageFormat() = default;

    virtual Image Load(const std::string& path) = 0;
    virtual void Save(const Image& image, const std::string& path) = 0;
};
