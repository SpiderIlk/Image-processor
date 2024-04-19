#pragma once

struct Color {
    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;

    Color();

    ~Color();

    Color& operator=(const Color& rgb);

    Color(float r, float g, float b);
};
