
/*
    Sharpening using the unsharp mask
*/

#define IMAGE_RANGE_CHECK

#include "filter.h"
#include "image.h"
#include "jpegio.h"
#include "stdio.h"

void unsharpMask(Image<unsigned char> &sharp, const Image<unsigned char> &gray,
                 int filterWidth, int contrast, int blackThreshold) {
  Image<double> grayImage, meanFilterMask, grayMean;
  Image<unsigned char> histeq;
  Image<int> diff;
  int width = gray.width();
  int height = gray.height();
  int x, y;
  // make an increased-contrast version of gray
  histogramEqualize(histeq, gray, 0, 0, width - 1, height - 1, contrast);

  grayImage.resize(width, height);
  for (x = 0; x < width; x++)
    for (y = 0; y < height; y++)
      grayImage(x, y) = gray(x, y);
  // create the mask for the mean filter and convolve with the gray image
  meanFilterMask.resize(filterWidth, filterWidth);
  meanFilterMask.setAll(1.0 /
                        (filterWidth * filterWidth)); // creates the filter mask
  convolveDouble(grayMean, grayImage,
                 meanFilterMask); // filter grayImage, output is grayMean

  diff.resize(width, height);
  sharp.resize(width, height);
  for (x = 0; x < width; x++) {
    for (y = 0; y < height; y++) {
      diff(x, y) = abs(gray(x, y) - (int)grayMean(x, y));
      if (diff(x, y) < blackThreshold)
        sharp(x, y) = gray(x, y);
      else
        sharp(x, y) = histeq(x, y);
    }
  }
}

int main(int argc, char *argv[]) {
  int x, y, height, width;
  unsigned char gray;
  int pix;
  Image<unsigned char> grayImage, sharp;
  RGBImage inputImage, outputImage;
  int filterWidth = atoi(argv[2]);
  int contrast = atoi(argv[3]);
  int blackThreshold = atoi(argv[4]);
  char outputFilename[100];

  // read the JPEG file
  readJpeg(inputImage, argv[1]);
  height = inputImage.height();
  width = inputImage.width();

  // set the dimensions of the output image
  grayImage.resize(width, height);

  // compute the gray scale of the colored picture
  for (y = 0; y < height; y++)
    for (x = 0; x < width; x++) {
      pix = inputImage(x, y);
      gray = (RED(pix) + GREEN(pix) + BLUE(pix)) / 3;
      grayImage(x, y) = gray;
    }

  // default: filterWidth = 3; contrast = 25; blackThreshold = 5;
  unsharpMask(sharp, grayImage, filterWidth, contrast, blackThreshold);

  outputImage.resize(width, height);
  for (y = 0; y < height; y++) {
    for (x = 0; x < width; x++) {
      outputImage.setPix(x, y, sharp(x, y), sharp(x, y), sharp(x, y));
    }
  }

  sprintf(outputFilename, "images/output/exer_4/sharp%03d_%03d_%03d.jpg",
          filterWidth, contrast, blackThreshold);
  // write the mean-filtered output to a JPEG file
  writeJpeg(outputImage, outputFilename, 100);
  // the last parameter is quality (1..100 = best)
}
