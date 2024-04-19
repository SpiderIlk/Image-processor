#include "color.h"

Color::Color() : r(0.0f), g(0.0f), b(0.0f) {
}

Color::~Color() = default;

Color& Color::operator=(const Color& rgb) = default;

Color::Color(float r, float g, float b) : r(r), g(g), b(b) {
}
