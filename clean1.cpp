
/*
    Cleaning binary images
*/

#define IMAGE_RANGE_CHECK

#include "binary.h"
#include "image.h"
#include "jpegio.h"
#include "stdio.h"

void binaryOutline(Image<unsigned char> &outline,
                   const Image<unsigned char> &dilation,
                   const Image<unsigned char> &erosion) {
  int width = dilation.width();
  int height = dilation.height();
  outline.resize(width, height);
  outline.setAll(0);

  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      if (dilation(x, y) != erosion(x, y)) {
        outline(x, y) = 1;
      }
    }
  }
}

int main(int argc, char *argv[]) {

  // default: 130
  int intensityThreshold = atoi(argv[2]);

  // default = 7
  int strucWidth = atoi(argv[3]); // width of the SQUARE structuring element

  RGBImage inputImage, outputImage1, outputImage2, outputOutline;
  Image<unsigned char> binary1, binary2, binary3, strucElem, outline;
  char outputFilename1[200];
  char outputFilename2[200];
  char outputFilename3[200];

  readJpeg(inputImage, argv[1]);
  int height = inputImage.height();
  int width = inputImage.width();
  int x, y, startX, startY, gray, c;

  // create a binary image from the image using thresholding
  binary1.resize(width, height);
  binary1.setAll(0);

  outputImage1.resize(width, height);
  outputImage1.setAll(COLOR_RGB(255, 255, 255)); // set all to white
  outputImage2 = outputImage1;
  outputOutline.resize(width, height);
  outputOutline.setAll(COLOR_RGB(255, 255, 255));

  // separate the object pixels from the background using a simple intensity
  // threshold this assumes the background has a much lighter intensity than the
  // objects
  for (x = 0; x < width; x++) {
    for (y = 0; y < height; y++) {
      gray = (RED(inputImage(x, y)) + GREEN(inputImage(x, y)) +
              BLUE(inputImage(x, y))) /
             3;
      if (gray < intensityThreshold) {
        binary1(x, y) = 1;                       // object  pixel
        outputImage1(x, y) = COLOR_RGB(0, 0, 0); // color black
      }
    }
  }

  strucElem.resize(strucWidth, strucWidth); // A square structuring element
  strucElem.setAll(1);

  // dilation fills in gaps
  //  strucWidth/2,strucWidth/2   specifies the center of the structuring
  //  element
  binaryDilation(binary2, binary1, strucElem, strucWidth / 2, strucWidth / 2);
  // erosion is effective in reducing noise
  binaryErosion(binary3, binary2, strucElem, strucWidth / 2, strucWidth / 2);

  binaryOutline(outline, binary2, binary3);

  // visualize the resulting binary image in a color image
  for (x = 0; x < width; x++) {
    for (y = 0; y < height; y++) {
      if (binary3(x, y)) {
        outputImage2(x, y) = COLOR_RGB(0, 0, 0);
      }
    }
  }

  for (x = 0; x < width; x++) {
    for (y = 0; y < height; y++) {
      if (outline(x, y)) {
        outputOutline(x, y) = COLOR_RGB(0, 0, 0);
      }
    }
  }

  // write the output to a JPEG file
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

  sprintf(outputFilename1, "images/output/exer_7/clean/%s_binary_%03d.jpg",
          filename, intensityThreshold);
  sprintf(outputFilename2, "images/output/exer_7/clean/%s_cleaned_%03d.jpg",
          filename, strucWidth);
  sprintf(outputFilename3, "images/output/exer_7/clean/%s_outline.jpg",
          filename);

  writeJpeg(outputImage1, outputFilename1, 70);
  writeJpeg(outputImage2, outputFilename2, 70);
  writeJpeg(outputOutline, outputFilename3, 70);
}
