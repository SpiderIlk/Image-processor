# Image-processor
Console application to apply some filters for BMP files

#
## Supported image format

Input and output files must be in 24-bit BMP format without compression and a color table

#
## Filters

#### Crop (-crop width height)
Crops an image to the specified width and height, leaving the upper left corner

#### Grayscale (-gs)
Converts an image to grayscale

#### Negative (-neg)
Converts an image to negative

#### Sharpening (-sharp)
Sharpening

#### Edge Detection (-edge threshold)
Edge selection. The output image is black and white

#### Blur (-blur sigma)
Gaussian blur, parametr - sigma

#
## Console query example

`./image_processor input.bmp output.bmp -crop 800 600 -gs -sharp`

In this example:
1. The image is loaded from the file `input.bmp`
2. Cropped to an image starting in the upper left corner and 800x600 pixels in size
3. Converted to grayscale
4. Sharpening is applied
5. The resulting image is saved to the file `output.bmp`
