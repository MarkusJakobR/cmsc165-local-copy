#define IMAGE_RANGE_CHECK

#include "image.h"
#include "jpegio.h"
#include "stdio.h"
#include "tools.h"
#include <string>

int main() {
  int x, y, height1, height2, width1, width2, cycles, max_cycles = 10, start_x,
                                                      end_x;
  double gray_percent, curr_gray_percent;
  RGBImage inputColorImage1, inputColorImage2, outputColorImage;
  Image<unsigned char> grayImage;
  unsigned char grayValue;

  // read the two images to get their size
  readJpeg(inputColorImage1, "images/recaplaza1_happy_resized.jpg");
  height1 = inputColorImage1.height();
  width1 = inputColorImage1.width();
  printf("The left image width is %d and height is %d \n", width1, height1);

  readJpeg(inputColorImage2, "images/recaplaza1_sad_resized.jpg");
  height2 = inputColorImage2.height();
  width2 = inputColorImage2.width();
  printf("The right image width is %d and height is %d \n", width2, height2);

  // call the function for taking the half of the image and placing them left to
  // right
  overlayHalfImage(outputColorImage, inputColorImage1, inputColorImage2);

  // get the gray values for the right image
  makeGrayFromRGB(grayImage, inputColorImage2);

  // compute for the percentage of the gray, to know how much gray must be in 1
  // picture out of the max cycles (10)
  gray_percent = static_cast<double>(width2 - width2 / 2) / max_cycles;
  curr_gray_percent = 0.0;

  // cycle through the required images
  for (cycles = 0; cycles < max_cycles; cycles++) {

    // compute for the starting x and ending x, where the ending x is between
    // the minimum of width2 or the starting x (half) + current gray percentage
    // and the constant gray percentage
    start_x = width2 / 2;
    end_x = std::min(width2, start_x + static_cast<int>(std::ceil(
                                           curr_gray_percent + gray_percent)));

    // with the values for the start_x and end_x, convert them to grayscale
    for (x = start_x; x < end_x; x++) {
      for (y = 0; y < height2; y++) {
        grayValue = grayImage(x, y);
        outputColorImage(x, y) = COLOR_RGB(grayValue, grayValue, grayValue);
      }
    }

    // create custom filename for each image, changing the number based on the
    // cycle
    std::string filename =
        "images/output/recaplaza_half_" + std::to_string(cycles) + ".jpg";
    writeJpeg(outputColorImage, (char *)filename.c_str(), 90);
    curr_gray_percent = curr_gray_percent + gray_percent;
  }
}
