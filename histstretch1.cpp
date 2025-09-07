
/*
  Exer:  Adjust the contrast of a gray scale image using histogram equalization
*/

#define IMAGE_RANGE_CHECK

#include "filter.h"
#include "image.h"
#include "jpegio.h"
#include "stdio.h"

int main() {
  int x, y, pix;
  RGBImage inputImage, outputImage;
  Image<unsigned char> gray, stretch;
  char outputFileName[100];

  float lowerPercentile = 0.01;
  float upperPercentile = 0.99;
  // read the JPEG file
  readJpeg(inputImage, "images/low_light.jpg");

  int height = inputImage.height();
  int width = inputImage.width();

  // select the region that you want to enhance
  int startX = 0;
  int startY = 0;
  int endX = width - 1;
  int endY = height - 1;

  gray.resize(width, height);
  // compute the gray scale of the sub-image
  for (y = startY; y < endY; y++) {
    for (x = startX; x < endX; x++) {
      pix = inputImage(x, y);
      gray(x, y) = (RED(pix) + GREEN(pix) + BLUE(pix)) / 3;
    }
  }

  stretchGrayHistogram(stretch, gray, lowerPercentile, upperPercentile);

  outputImage.resize(width, height);
  for (y = startY; y < endY; y++) {
    for (x = startX; x < endX; x++) {
      outputImage(x, y) =
          COLOR_RGB(stretch(x, y), stretch(x, y), stretch(x, y));
    }
  }
  // write the output image to a JPEG file
  sprintf(outputFileName, "images/output/exer_2/stretch-%02d-%02d_lowlight.jpg",
          (int)(100 * lowerPercentile), (int)(100 * upperPercentile));
  writeJpeg(outputImage, outputFileName, 100);
  // the last parameter is JPEG quality (1..100 = best)
}
