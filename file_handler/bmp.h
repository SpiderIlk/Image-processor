#pragma once
#include <cstdint>
#include "../utility/image_format.h"

class BMP : public ImageFormat {
public:
    Image Load(const std::string& path) override;
    void Save(const Image& image, const std::string& path) override;

private:
    struct FileHeader {
        unsigned char header_field[2] = {'B', 'M'};
        uint32_t file_size = 0;
        uint16_t reserved[2] = {0, 0};
        uint32_t offset = 54;  // NOLINT
    };

    struct BitmapInfoHeader {
        uint32_t header_size = 40;  // NOLINT

        int32_t width = 0;
        int32_t height = 0;

        uint16_t color_planes = 1;
        uint16_t bits_per_pixel = 24;  // NOLINT
        uint32_t compression_method = 0;
        uint32_t bitmap_data_size = 0;

        int32_t resolution_horizontal = 11811;  // NOLINT
        int32_t resolution_vertical = 11811;    // NOLINT

        uint32_t colors_total = 0;
        uint32_t colors_important = 0;
    };
};
