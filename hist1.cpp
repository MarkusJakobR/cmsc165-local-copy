
/*
    Draw the intensity histogram of an image
*/

#define IMAGE_RANGE_CHECK

#include "color.h"
#include "image.h"
#include "jpegio.h"
#include "stdio.h"
#include "tools.h"

int main(int argc, char *argv[]) {
  int x, y, height, width;
  int g, gMax;
  RGBImage inputColorImage;
  // the following is an image whose pixel's type is unsigned char
  Image<unsigned char> grayImage; // each pixel has type   unsigned char
                                  // unsigned char is  8 bits   and the range of
                                  // values  is  0 "black" . . 255  "white"
  Image<int>
      hist; // not really an image, but it uses Image<int> a table of numbers
  RGBImage histImage;

  // read the JPEG file
  readJpeg(inputColorImage, argv[1]);
  height = inputColorImage.height();
  width = inputColorImage.width();
  printf("The image width is %d and height is %d \n", width, height);

  // make a gray image from the RGB image
  // input image is    inputColorImage
  // the output will be stored in    grayImage    which was declared earlier
  makeGrayFromRGB(grayImage, inputColorImage);

  // compute the intensity histogram
  hist.resize(256, 1);
  hist.setAll(0);
  gMax = 0;
  for (x = 0; x < width; x++) {
    for (y = 0; y < height; y++) {
      g = grayImage(x, y); // checks the gray value of a pixel
      hist(g, 0)++; // goes to the table of frequencies where the index is g =
                    // something and increment
      if (hist(g, 0) >
          hist(gMax, 0)) // checks if current frequency is higher than gmax
        gMax = g; // used to find the highest frequency which will be used later
                  // in drawing the histogram
    }
  }
  // draw the histogram onto the image histImage
  histImage.resize(256, 256);
  histImage.setAll(COLOR_RGB(255, 255, 255)); // set all pixels to "white"
  for (x = 0; x < 256; x++)
    // basically the percentage by (x / gMax) * 255
    for (y = 0; y < min(255 * hist(x, 0) / hist(gMax, 0), 255);
         y++) // the frequencies are scaled down so the bar will fit in the
              // image
      histImage(x, 255 - y) =
          COLOR_RGB(0, 0, 0); // draws black bars depending on the value of y
                              // (height of the bar)

  writeJpeg(histImage, argv[2], 90); // write as a JPEG file
}
