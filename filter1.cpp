
/*
   Mean and median filtering
*/

#define IMAGE_RANGE_CHECK

#include "filter.h"
#include "image.h"
#include "jpegio.h"
#include "stdio.h"

int main(int argc, char *argv[]) {
  int x, y;
  int height, width;
  unsigned char gray;
  int pix;
  Image<double> grayImage, grayMean, grayMedian, meanFilterMask;

  RGBImage inputImage, outputImage;

  int filterWidth = atoi(argv[4]); // the width of the filter, use odd numbers
                                   // to have single median

  // read the JPEG file
  readJpeg(inputImage, argv[1]);
  height = inputImage.height();
  width = inputImage.width();

  printf("The width of the averaged neighborhood is %d.\n", filterWidth);

  // set the dimensions of the output image
  grayImage.resize(width, height);

  // compute the gray scale of the colored picture
  for (y = 0; y < height; y++)
    for (x = 0; x < width; x++) {
      pix = inputImage(x, y);
      gray = (RED(pix) + GREEN(pix) + BLUE(pix)) / 3;
      grayImage(x, y) = gray;
    }

  // in the following statement, the filterWidth x filterWidth neighborhood
  // of each pixel (x,y) in grayImage is taken and the median
  // or the 50th percentile is assigned to (x,y) of grayMedian
  grayMedian = orderStatFilter(grayImage, filterWidth, 50);

  outputImage.resize(width, height);
  for (y = 0; y < height; y++) {
    for (x = 0; x < width; x++) {
      outputImage.setPix(x, y, grayMedian(x, y), grayMedian(x, y),
                         grayMedian(x, y));
    }
  }

  // write the median-filtered output to a JPEG file
  writeJpeg(outputImage, argv[2], 70);

  // create the mask for the mean filter and convolve with the gray image
  meanFilterMask.resize(filterWidth, filterWidth);
  meanFilterMask.setAll(1.0 /
                        (filterWidth * filterWidth)); // creates the filter mask
  convolveDouble(grayMean, grayImage,
                 meanFilterMask); // filter grayImage, output is grayMean

  outputImage.resize(width, height);
  for (y = 0; y < height; y++) {
    for (x = 0; x < width; x++) {
      outputImage.setPix(x, y, grayMean(x, y), grayMean(x, y), grayMean(x, y));
    }
  }

  // write the mean-filtered output to a JPEG file
  writeJpeg(outputImage, argv[3], 70);
  // the last parameter is quality (1..100 = best)
}
