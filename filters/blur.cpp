#include "blur.h"

void Blur::Apply(Image& image) {
    Image image_copy = image;

    int height = image.GetHeight();
    int width = image.GetWidth();

    double kernel[3][3] = {};
    double sum = 0;
    for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
            double exponent = pow(M_E, static_cast<double>(-(x * x + y * y)) / (2 * sigma * sigma));
            double val = (exponent / (2 * M_PI * sigma * sigma));
            kernel[x + 1][y + 1] = val;
            sum += val;
        }
    }
    for (int x = 0; x <= 2; ++x) {
        for (int y = 0; y <= 2; ++y) {
            kernel[x][y] /= sum;
        }
    }

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {

            Color cur_pixel = image_copy.GetColor(x, y);
            Color up = image_copy.GetColor(x, std::max(0, y - 1));
            Color down = image_copy.GetColor(x, std::min(height - 1, y + 1));
            Color left = image_copy.GetColor(std::max(0, x - 1), y);
            Color right = image_copy.GetColor(std::min(width - 1, x + 1), y);
            Color up_left = image_copy.GetColor(std::max(0, x - 1), std::max(0, y - 1));
            Color down_left = image_copy.GetColor(std::max(0, x - 1), std::min(height - 1, y + 1));
            Color up_right = image_copy.GetColor(std::min(width - 1, x + 1), std::max(0, y - 1));
            Color down_right = image_copy.GetColor(std::min(width - 1, x + 1), std::min(height - 1, y + 1));

            Color new_color;
            new_color.r =
                    std::min(1.0f, std::max(0.0f, static_cast<float>(kernel[0][0] * up_left.r + kernel[0][1] * up.r +
                                                                     kernel[0][2] * up_right.r + kernel[1][0] * left.r +
                                                                     kernel[1][1] * cur_pixel.r + kernel[1][2] * right.r +
                                                                     kernel[2][0] * down_left.r + kernel[2][1] * down.r +
                                                                     kernel[2][2] * down_right.r)));

            new_color.g =
                    std::min(1.0f, std::max(0.0f, static_cast<float>(kernel[0][0] * up_left.g + kernel[0][1] * up.g +
                                                                     kernel[0][2] * up_right.g + kernel[1][0] * left.g +
                                                                     kernel[1][1] * cur_pixel.g + kernel[1][2] * right.g +
                                                                     kernel[2][0] * down_left.g + kernel[2][1] * down.g +
                                                                     kernel[2][2] * down_right.g)));

            new_color.b =
                    std::min(1.0f, std::max(0.0f, static_cast<float>(kernel[0][0] * up_left.b + kernel[0][1] * up.b +
                                                                     kernel[0][2] * up_right.b + kernel[1][0] * left.b +
                                                                     kernel[1][1] * cur_pixel.b + kernel[1][2] * right.b +
                                                                     kernel[2][0] * down_left.b + kernel[2][1] * down.b +
                                                                     kernel[2][2] * down_right.b)));

            image.SetColor(new_color, x, y);
        }
    }
}
