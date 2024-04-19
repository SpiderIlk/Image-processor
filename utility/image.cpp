#include "image.h"

Image::Image() : width_(0), height_(0) {
}

Image::~Image() = default;

Image& Image::operator=(const Image& other) {
    this->width_ = other.width_;
    this->height_ = other.height_;
    this->pixels_ = std::vector(height_, std::vector(width_, Color()));
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            this->pixels_[x][y] = other.GetColor(x, y);
        }
    }
    return *this;
}

Image::Image(int width, int height) {
    this->width_ = width;
    this->height_ = height;
    this->pixels_ = std::vector(height, std::vector(width, Color()));
}

Color Image::GetColor(int x, int y) const {
    return pixels_[y][x];
}

void Image::SetColor(const Color& rgb, int x, int y) {
    pixels_[y][x] = rgb;
}

int Image::GetWidth() const {
    return width_;
}

int Image::GetHeight() const {
    return height_;
}

int Image::GetXPixels() const {
    return x_pixels_per_m_;
}

int Image::GetYPixels() const {
    return y_pixels_per_m_;
}

void Image::SetXPixels(const int& x) {
    this->x_pixels_per_m_ = x;
}

void Image::SetYPixels(const int& y) {
    this->y_pixels_per_m_ = y;
}

void Image::ResizeVertical(int height_target) {
    pixels_.resize(height_target);
    height_ = height_target;
}

void Image::ResizeHorizontal(int width_target) {
    for (int y = 0; y < height_; ++y) {
        pixels_[y].resize(width_target);
    }
    width_ = width_target;
}
