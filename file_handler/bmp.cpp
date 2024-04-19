#include <fstream>
#include "bmp.h"

void CreateFileHeader(unsigned char *file_header, const int file_size) {
    file_header[0] = 'B';
    file_header[1] = 'M';
    file_header[2] = file_size;
    file_header[3] = file_size >> 8;   // NOLINT
    file_header[4] = file_size >> 16;  // NOLINT
    file_header[5] = file_size >> 24;  // NOLINT
    for (int i = 6; i < 14; ++i) {     // NOLINT
        if (i == 10) {                 // NOLINT
            file_header[i] = 54;       // NOLINT
            continue;
        }
        file_header[i] = 0;
    }
}

void CreateInfoHeader(unsigned char *info_header, const int file_size, int width, int height, int x_pixels,
                      int y_pixels) {
    info_header[0] = 40;  // NOLINT
    info_header[1] = 0;
    info_header[2] = 0;
    info_header[3] = 0;

    info_header[4] = width;
    info_header[5] = width >> 8;   // NOLINT
    info_header[6] = width >> 16;  // NOLINT
    info_header[7] = width >> 24;  // NOLINT

    info_header[8] = height;         // NOLINT
    info_header[9] = height >> 8;    // NOLINT
    info_header[10] = height >> 16;  // NOLINT
    info_header[11] = height >> 24;  // NOLINT

    info_header[12] = 1;  // NOLINT
    info_header[13] = 0;  // NOLINT

    info_header[14] = 24;            // NOLINT
    for (int i = 15; i < 21; ++i) {  // NOLINT
        info_header[i] = 0;
    }
    info_header[21] = file_size >> 8;   // NOLINT
    info_header[22] = file_size >> 16;  // NOLINT
    info_header[23] = file_size >> 24;  // NOLINT

    info_header[24] = x_pixels;        // NOLINT
    info_header[25] = x_pixels >> 8;   // NOLINT
    info_header[26] = x_pixels >> 16;  // NOLINT
    info_header[27] = x_pixels >> 24;  // NOLINT

    info_header[28] = y_pixels;        // NOLINT
    info_header[29] = y_pixels >> 8;   // NOLINT
    info_header[30] = y_pixels >> 16;  // NOLINT
    info_header[31] = y_pixels >> 24;  // NOLINT
    for (int i = 32; i < 40; ++i) {    // NOLINT
        info_header[i] = 0;
    }
}

Image BMP::Load(const std::string &path) {
    std::ifstream f;
    f.open(path, std::ios::in | std::ios::binary);
    if (!f.is_open()) {
        throw std::runtime_error("Can't open file: " + path);
    }
    unsigned char file_header[14];                      // NOLINT
    unsigned char info_header[40];                      // NOLINT
    f.read(reinterpret_cast<char *>(file_header), 14);  // NOLINT
    f.read(reinterpret_cast<char *>(info_header), 40);  // NOLINT
    if (file_header[0] != 'B' || file_header[1] != 'M') {
        throw std::runtime_error("Not a BMP file: " + path);
    }
    int width = (info_header[4]) + (info_header[5] << 8) + (info_header[6] << 16)    // NOLINT
                + (info_header[7] << 24);                                            // NOLINT
    int height = (info_header[8]) + (info_header[9] << 8) + (info_header[10] << 16)  // NOLINT
                 + (info_header[11] << 24);                                          // NOLINT
    int x_pixels_per_m =
            (info_header[24]) + (info_header[25] << 8) + (info_header[26] << 16) + (info_header[27] << 24);  // NOLINT
    int y_pixels_per_m =
            (info_header[28]) + (info_header[29] << 8) + (info_header[30] << 16) + (info_header[31] << 24);  // NOLINT
    Image image(width, height);
    image.SetXPixels(x_pixels_per_m);
    image.SetYPixels(y_pixels_per_m);
    const int padding = ((4 - (width * 3) % 4) % 4);
    Color rgb;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            unsigned char pixel_color[3];
            f.read(reinterpret_cast<char *>(pixel_color), 3);
            rgb.r = static_cast<float>(pixel_color[2]) / 255.0f;  // NOLINT
            rgb.g = static_cast<float>(pixel_color[1]) / 255.0f;  // NOLINT
            rgb.b = static_cast<float>(pixel_color[0]) / 255.0f;  // NOLINT
            image.SetColor(rgb, x, height - 1 - y);
        }
        f.ignore(padding);
    }
    f.close();
    return image;
}

void BMP::Save(const Image &image, const std::string &path) {
    std::ofstream f;
    f.open(path, std::ios::out | std::ios::binary);
    if (!f.is_open()) {
        throw std::runtime_error("Can't save file: " + path);
    }
    unsigned char trash_padding[3] = {0, 0, 0};
    const int padding = ((4 - (image.GetWidth() * 3) % 4) % 4);
    const int file_size = 54 + image.GetWidth() * image.GetHeight() * 3 + padding * image.GetHeight();  // NOLINT
    unsigned char file_header[14];                                                                      // NOLINT
    unsigned char info_header[40];                                                                      // NOLINT
    CreateFileHeader(file_header, file_size);
    CreateInfoHeader(info_header, file_size, image.GetWidth(), image.GetHeight(), image.GetXPixels(),
                     image.GetYPixels());
    f.write(reinterpret_cast<char *>(file_header), 14);  // NOLINT
    f.write(reinterpret_cast<char *>(info_header), 40);  // NOLINT
    Color temp;
    for (int y = image.GetHeight() - 1; y >= 0; --y) {
        for (int x = 0; x < image.GetWidth(); ++x) {
            temp = image.GetColor(x, y);
            unsigned char pixel_r = static_cast<unsigned char>(temp.r * 255.0f);  // NOLINT
            unsigned char pixel_g = static_cast<unsigned char>(temp.g * 255.0f);  // NOLINT
            unsigned char pixel_b = static_cast<unsigned char>(temp.b * 255.0f);  // NOLINT
            unsigned char pixel_color[3] = {pixel_b, pixel_g, pixel_r};
            f.write(reinterpret_cast<char *>(pixel_color), 3);
        }
        f.write(reinterpret_cast<char *>(trash_padding), padding);
    }
    f.close();
}
