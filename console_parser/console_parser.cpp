#include <map>
#include <stdexcept>
#include "../file_handler/bmp.h"
#include "../filters/grayscale.h"
#include "../filters/negative.h"
#include "../filters/sharpening.h"
#include "../filters/edge_detection.h"
#include "../filters/crop.h"
#include "../filters/blur.h"

inline void Parser(int argc, char** argv) {
    if (argc <= 2) {
        printf("Hi, stranger! If you want to use my precious filters, follow my precious instructions:\n");
        printf("Enter following in cmd:\n");
        printf("./image_processor {input file path} {output file path} {filters_1 [arguments]}...\n");
        printf("Available filters:\n");
        printf("-crop [int width, int height] - Crop\n");
        printf("-gs - Grayscale\n");
        printf("-neg - Negative\n");
        printf("-sharp - Sharpening\n");
        printf("-edge [float threshold] - Edge Detection\n");
        printf("-blur [sigma] - Gaussian Blur\n");
        printf("Example: ./image_processor input.bmp /tmp/output.bmp -crop 800 600 -gs -blur 0.5\n");
    } else {
        std::string path_input = argv[1];
        std::string path_output = argv[2];
        BMP bmp;
        Image image = bmp.Load(path_input);
        std::map<std::string, int> case_numbers = {{"-crop", 0},  {"-gs", 1},   {"-neg", 2},
                                                   {"-sharp", 3}, {"-edge", 4}, {"-blur", 5}};  // NOLINT
        for (int i = 3; i < argc; ++i) {
            switch (case_numbers[argv[i]]) {
                case 0: {
                    if (i >= argc - 2 || std::stol(argv[i + 1]) < 0 || std::stol(argv[i + 2]) < 0) {
                        throw std::runtime_error("Wrong parameters. They should be: -crop [int width, int height]");
                    }
                    Crop filter(std::atoi(argv[i + 1]), std::atoi(argv[i + 2]));
                    i += 2;
                    filter.Apply(image);
                    break;
                }
                case 1: {
                    Grayscale filter;
                    filter.Apply(image);
                    break;
                }
                case 2: {
                    Negative filter;
                    filter.Apply(image);
                    break;
                }
                case 3: {
                    Sharpening filter;
                    filter.Apply(image);
                    break;
                }
                case 4: {
                    if (i == argc - 1 || std::stod(argv[i + 1]) > 1.0f || std::stod(argv[i + 1]) < 0.0f) {
                        throw std::runtime_error("Wrong parameters. They should be: -edge [float threshold]");
                    }
                    Edge filter(std::stof(argv[i + 1]));
                    ++i;
                    filter.Apply(image);
                    break;
                }
                case 5: {  // NOLINT
                    if (i == argc - 1) {
                        throw std::runtime_error("Wrong parameters. They should be: -blur [float sigma]");
                    }
                    Blur filter(std::stod(argv[i + 1]));
                    ++i;
                    filter.Apply(image);
                    break;
                }
                default: {
                    throw std::runtime_error(
                            "Wrong parameters. Try like this: ./image_processor input.bmp /tmp/output.bmp -crop 800 600");
                }
            }
        }
        bmp.Save(image, path_output);
    }
}
