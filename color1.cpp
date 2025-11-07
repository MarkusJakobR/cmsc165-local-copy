
/*
   Finding specific colors using the HSI color space
*/

#define IMAGE_RANGE_CHECK

#include "color.h"
#include "image.h"
#include "jpegio.h"
#include "tools.h"

int main(int argc, char *argv[]) {

  double pi = 3.14159;

  // the following defines a range of colors in the Hue-Saturation-Intensity
  // color space
  double minHueDeg = atof(argv[2]);
  double maxHueDeg = atof(argv[3]);
  double minimumHue = (minHueDeg * pi) / 180.0; // range is 0.0 to 2 * pi
  double maximumHue = (maxHueDeg * pi) / 180.0; // range is 0.0 to 2 * pi
  double minimumSaturation = atof(argv[4]);     // range is 0.0 to 1.0
  double maximumSaturation = atof(argv[5]);     // range is 0.0 to 1.0

  int x, y, height, width, pixColor;
  double red, green, blue;
  double hue, saturation, intensity;
  RGBImage inputImage, outputImage;
  char filename[200];
  char extractedFilename[200];
  extractFilename(extractedFilename, argv[1]);

  readJpeg(inputImage, argv[1]);
  height = inputImage.height();
  width = inputImage.width();

  outputImage.resize(width, height); // set dimensions

  // for each pixel
  for (x = 0; x < width; x++) {
    for (y = 0; y < height; y++) {
      pixColor = inputImage(x, y);
      red = RED(pixColor);
      green = GREEN(pixColor);
      blue = BLUE(pixColor);

      // convert from RGB to HSI
      RGBtoHSI(red, green, blue, hue, saturation, intensity);

      // if the hue and saturation are within the search range
      // then retain the original pixel, otherwise it becomes white
      if (minimumHue <= hue && hue <= maximumHue &&
          minimumSaturation <= saturation && saturation <= maximumSaturation) {
        outputImage(x, y) = pixColor; // retain the color
      } else                          // color it white
        outputImage(x, y) = COLOR_RGB(255, 255, 255);
    }
  }

  sprintf(filename, "images/output/exer_10/%s_%.2f-%.2f_%.2f-%.2f_hsi-pick.jpg",
          extractedFilename, minHueDeg, maxHueDeg, minimumSaturation,
          maximumSaturation);
  writeJpeg(outputImage, filename, 70);
}
