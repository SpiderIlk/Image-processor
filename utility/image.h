#pragma once
#include <vector>
#include "color.h"

class Image {
private:
    int width_;
    int height_;
    std::vector<std::vector<Color>> pixels_;
    int x_pixels_per_m_;
    int y_pixels_per_m_;

public:
    Image();

    ~Image();

    Image& operator=(const Image& other);

    Image(int width, int height);

    [[nodiscard]] Color GetColor(int x, int y) const;

    void SetColor(const Color& rgb, int x, int y);

    [[nodiscard]] int GetWidth() const;

    [[nodiscard]] int GetHeight() const;

    [[nodiscard]] int GetXPixels() const;

    [[nodiscard]] int GetYPixels() const;

    void SetXPixels(const int& x);

    void SetYPixels(const int& y);

    void ResizeVertical(int height_target);

    void ResizeHorizontal(int width_target);
};
