
/*
  Exercise:  Counting objects and measuring object areas
*/

#define IMAGE_RANGE_CHECK

#include "binary.h"
#include "image.h"
#include "jpegio.h"
#include "stdio.h"
#include "tools.h"

int main(int argc, char *argv[]) {
  int pixColor = COLOR_RGB(255, 128, 0); // orange
  RGBImage inputImage, outputImage;
  Image<unsigned char> binary, binary2, strucElem, componentImage;

  ConnectedComponents
      cc; // in binary.h, a class for connected component labelling
  char countFilename[200];
  char outputFilename[200];
  char extractedFilename[200];

  extractFilename(extractedFilename, argv[1]);

  int intensityThreshold = atoi(argv[2]); // threshold for binarizing; def: 130
  int strucWidth =
      atoi(argv[3]); // width of structuring element for cleaning; def: 5
  int minimumArea =
      atoi(argv[4]); // range of size of objects to be boxed   700; def: 12000
  int maximumArea = atoi(argv[5]); // 6000; def: 13000

  readJpeg(inputImage, argv[1]); // def: coins1.jpg
  int height = inputImage.height();
  int width = inputImage.width();
  int x, y, startX, startY, gray, c;

  // create a binary image from the gray scale image using thresholding
  binary.resize(width, height);
  binary.setAll(0);
  for (x = 0; x < width; x++)
    for (y = 0; y < height; y++) {
      gray = (RED(inputImage(x, y)) + GREEN(inputImage(x, y)) +
              BLUE(inputImage(x, y))) /
             3;
      if (gray < intensityThreshold)
        binary(x, y) = 1;
    }

  // clean the binary imaage
  strucElem.resize(strucWidth, strucWidth); // A square structuring element
  strucElem.setAll(1);
  // dilate in order to fill gaps
  binaryDilation(binary2, binary, strucElem, strucWidth / 2, strucWidth / 2);

  // find all connected components.  Connectedness can be specified
  // by FOUR_CONNECTED or EIGHT_CONNECTED
  cc.analyzeBinary(binary2, EIGHT_CONNECTED);

  outputImage = cc.randomColors(); // show each component with a different color

  sprintf(outputFilename,
          "images/output/exer_8/count/%s_%03d_%03d_%03d_%03d_object-pieces.jpg",
          extractedFilename, intensityThreshold, strucWidth, minimumArea,
          maximumArea);
  writeJpeg(outputImage, outputFilename, 90);
  outputImage = inputImage;

  printf("\n Here is the object area of each component:  ");
  for (c = 0; c < cc.getNumComponents(); c++) {
    // get the binary image of component c
    componentImage = cc.getComponentBinary(c);

    int ch = componentImage.height(); // height of bounding box
    int cw = componentImage.width();  // width of bounding box
    int m, n, numPix;
    numPix = 0;

    // count the number of pixels of the component
    // numPix = number of 1-pixels of component c
    for (m = 0; m < cw; m++)
      for (n = 0; n < ch; n++)
        numPix += componentImage(m, n);

    printf("  %d", numPix);

    // if the size of the object is within the specified range
    if (minimumArea <= numPix && numPix <= maximumArea) {
      cc.getBoundary(c, startX, startY, cw, ch);

      // draw the bounding box for that component
      drawBoxRGB(outputImage, startX, startY, startX + cw, startY + ch,
                 pixColor, 2);
    }
  }

  // write the output to a JPEG file, where the selected objects are boxed
  sprintf(
      countFilename,
      "images/output/exer_8/count/%s_%03d_%03d_%03d_%03d_objects-selected.jpg",
      extractedFilename, intensityThreshold, strucWidth, minimumArea,
      maximumArea);
  writeJpeg(outputImage, countFilename, 70);

  printf("\nThere are %d components in the binary image. \n",
         cc.getNumComponents());
  printf("See the image  object-pieces.jpg  for a visualization of the "
         "components.\n");
}
