
/*
  Creating a binary image using an intensity threshold
*/

#define IMAGE_RANGE_CHECK

#include "binary.h"
#include "image.h"
#include "jpegio.h"
#include "stdio.h"
#include <string.h>

int main(int argc, char *argv[]) {
  RGBImage inputImage, outputImage;
  Image<unsigned char> binary;
  char fileName[200];

  // default: 150
  int intensityThreshold = atoi(argv[2]);

  readJpeg(inputImage, argv[1]);
  int height = inputImage.height();
  int width = inputImage.width();
  int x, y, gray;

  // create a binary image using thresholding
  binary.resize(width, height);
  binary.setAll(0); // set all to background

  // create an RGB visualization of the binary image
  outputImage.resize(width, height);
  outputImage.setAll(COLOR_RGB(255, 255, 255)); // set all to white

  for (x = 0; x < width; x++) {
    for (y = 0; y < height; y++) {
      gray = (RED(inputImage(x, y)) + GREEN(inputImage(x, y)) +
              BLUE(inputImage(x, y))) /
             3;
      if (gray < intensityThreshold) { // if the pixel is dark
        binary(x, y) = 1;              // this pixel is part of the object
        outputImage(x, y) = COLOR_RGB(
            0, 0, 0); // in the visualization, it will be colored black
      }
    }
  }

  // find the name of the jpg file for better naming
  char baseName[200];
  strcpy(baseName, argv[1]);

  // find the dot and remove the extension of the image
  char *dot = strrchr(baseName, '.');
  if (dot)
    *dot = '\0';

  // remove the slashes and find the rightmost name which is the name of the
  // image
  char *slash = strrchr(baseName, '/');
  char *filename = slash ? slash + 1 : baseName;

  // write the output to a JPEG file
  // system("mkdir images/output");
  sprintf(fileName, "images/output/exer_7/binary/%s_binary_%03d.jpg", filename,
          intensityThreshold);
  writeJpeg(outputImage, fileName, 100);
}
