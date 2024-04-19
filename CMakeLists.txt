cmake_minimum_required(VERSION 3.16)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

add_executable(
        image_processor
        image_processor.cpp
        filters/grayscale.h
        filters/crop.h
        filters/grayscale.cpp
        filters/crop.cpp
        filters/negative.h
        filters/negative.cpp
        filters/sharpening.h
        filters/sharpening.cpp
        filters/edge_detection.h
        filters/edge_detection.cpp
        filters/blur.h
        filters/blur.cpp
        utility/image.h
        utility/image.cpp
        console_parser/console_parser.cpp
        utility/color.h
        utility/color.cpp
        pipeline/pipeline.h
        pipeline/pipeline.cpp
        utility/image_format.h
        filters/filter.h
        filters/filter.h
        file_handler/bmp.h
        file_handler/bmp.cpp
)
