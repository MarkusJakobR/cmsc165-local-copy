
/*
    Sharpening using the unsharp mask
*/

#define IMAGE_RANGE_CHECK

#include "filter.h"
#include "image.h"
#include "jpegio.h"
#include "stdio.h"

// function for sharpening the edges
void unsharpMask(Image<unsigned char> &sharp, const Image<unsigned char> &gray,
                 int filterWidth, int contrast, int blackThreshold) {
  Image<double> grayImage, meanFilterMask, grayMean;
  Image<unsigned char> histeq;
  Image<int> diff;
  int width = gray.width();
  int height = gray.height();
  int x, y;
  // make an increased-contrast version of gray
  // this will be used later to swap with the possible edges of the image
  histogramEqualize(histeq, gray, 0, 0, width - 1, height - 1, contrast);

  grayImage.resize(width, height);
  for (x = 0; x < width; x++)
    for (y = 0; y < height; y++)
      grayImage(x, y) = gray(x, y);
  // create the mask for the mean filter and convolve with the gray image
  // creates the "blurry" effect from the previous exer
  meanFilterMask.resize(filterWidth, filterWidth);
  meanFilterMask.setAll(1.0 /
                        (filterWidth * filterWidth)); // creates the filter mask
  convolveDouble(grayMean, grayImage,
                 meanFilterMask); // filter grayImage, output is grayMean

  diff.resize(width, height);
  sharp.resize(width, height);
  for (x = 0; x < width; x++) {
    for (y = 0; y < height; y++) {
      // find the absolute value diff between the original gray image to the
      // blurred one
      diff(x, y) = abs(gray(x, y) - (int)grayMean(x, y));
      // if less than the threshold, use the original one since its probably not
      // an edge
      if (diff(x, y) < blackThreshold)
        sharp(x, y) = gray(x, y);
      // if greater, then use the higher contrast one since it is most likely an
      // edge
      else
        sharp(x, y) = histeq(x, y);
    }
  }
}

// function for sharpening the image using laplacian edge detection
void laplacianSharpen(Image<unsigned char> &lapSharp,
                      const Image<unsigned char> &gray, double strength) {
  Image<double> laplacianKernel(3, 3), laplacianOutput, grayDouble;
  double originalPixel, laplacianValue, sharpenedValue;
  int width = gray.width();
  int height = gray.height();
  int x, y;
  // laplacian kernel using the below 3x3 grid
  // |  0 | -1 |  0 |
  // | -1 |  4 | -1 |
  // |  0 | -1 |  0 |
  laplacianKernel(0, 0) = 0;
  laplacianKernel(1, 0) = -1;
  laplacianKernel(2, 0) = 0;
  laplacianKernel(0, 1) = -1;
  laplacianKernel(1, 1) = 4;
  laplacianKernel(2, 1) = -1;
  laplacianKernel(0, 2) = 0;
  laplacianKernel(1, 2) = -1;
  laplacianKernel(2, 2) = 0;

  grayDouble.resize(width, height);
  for (y = 0; y < height; y++)
    for (x = 0; x < width; x++)
      grayDouble(x, y) = gray(x, y);

  // convolve using the laplacian kernel
  convolveDouble(laplacianOutput, grayDouble, laplacianKernel);

  lapSharp.resize(width, height);

  for (y = 0; y < height; y++)
    for (x = 0; x < width; x++) {
      // subtract the original pix value to the laplacian value and use it as
      // the new value
      originalPixel = gray(x, y);
      laplacianValue = laplacianOutput(x, y);
      // this makes the dark edge of pixels darker and light edge of pixels
      // lighter
      sharpenedValue = originalPixel - (strength * laplacianValue);

      // constraint to keep the values within 0-255
      if (sharpenedValue > 255)
        sharpenedValue = 255;
      if (sharpenedValue < 0)
        sharpenedValue = 0;

      lapSharp(x, y) = (unsigned char)sharpenedValue;
    }
}

int main(int argc, char *argv[]) {
  int x, y, height, width;
  unsigned char gray;
  int pix;
  Image<unsigned char> grayImage, sharp, laplace;
  RGBImage inputImage, unsharpOutputImage, laplaceOutputImage;
  char unsharpOutputFilename[100];
  char laplaceOutputFilename[100];

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

  if (argc == 5) {

    int filterWidth = atoi(argv[2]);
    int contrast = atoi(argv[3]);
    int blackThreshold = atoi(argv[4]);

    // default: filterWidth = 3; contrast = 25; blackThreshold = 5;
    unsharpMask(sharp, grayImage, filterWidth, contrast, blackThreshold);

    unsharpOutputImage.resize(width, height);
    for (y = 0; y < height; y++) {
      for (x = 0; x < width; x++) {
        unsharpOutputImage.setPix(x, y, sharp(x, y), sharp(x, y), sharp(x, y));
      }
    }

    sprintf(unsharpOutputFilename,
            "images/output/exer_4/sharp%03d_%03d_%03d.jpg", filterWidth,
            contrast, blackThreshold);

    // write the mean-filtered output to a JPEG file
    writeJpeg(unsharpOutputImage, unsharpOutputFilename, 100);
    // the last parameter is quality (1..100 = best)

  } else if (argc == 3) {

    double strength = atof(argv[2]);

    laplacianSharpen(laplace, grayImage, strength);

    laplaceOutputImage.resize(width, height);
    for (y = 0; y < height; y++) {
      for (x = 0; x < width; x++) {
        laplaceOutputImage.setPix(x, y, laplace(x, y), laplace(x, y),
                                  laplace(x, y));
      }
    }

    sprintf(laplaceOutputFilename, "images/output/exer_4/laplace%.2f.jpg",
            strength);
    writeJpeg(laplaceOutputImage, laplaceOutputFilename, 100);
  }
}
