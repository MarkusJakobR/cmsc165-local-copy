#define IMAGE_RANGE_CHECK

#include "image.h"
#include "jpegio.h"
#include "stdio.h"
#include "tools.h"
#include <string>

int main() {
  int x, y, height1, height2, width1, width2, cycles, max_cycles = 10, start_x,
                                                      end_x;
  double t, Rn, Gn, Bn;
  RGBImage inputColorImage1, inputColorImage2, outputColorImage;
  Image<unsigned char> grayImage;
  unsigned char grayValue, R, G, B;

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

  // cycle through the required images
  for (cycles = 1; cycles <= max_cycles; cycles++) {

    // compute the grayscale percentage for this cycle
    t = static_cast<double>(cycles) / max_cycles;

    // iterate only through the right half of the image
    for (x = width2 / 2; x < width2; x++) {
      for (y = 0; y < height2; y++) {

        // take the values of RGB for the current pixel
        R = RED(inputColorImage2(x, y));
        G = GREEN(inputColorImage2(x, y));
        B = BLUE(inputColorImage2(x, y));

        // take the grayvalue from the complete gray image map
        grayValue = grayImage(x, y);

        // compute for the new value of the RGB of the pixel using the formula
        // for linear interpolation
        // e.g. R' = (1 - t) R + t * gray
        Rn = (1.0 - t) * R + t * grayValue;
        Gn = (1.0 - t) * G + t * grayValue;
        Bn = (1.0 - t) * B + t * grayValue;

        // change the pixel in the output image with the new value
        outputColorImage(x, y) =
            COLOR_RGB(static_cast<unsigned char>(std::round(Rn)),
                      static_cast<unsigned char>(std::round(Gn)),
                      static_cast<unsigned char>(std::round(Bn)));
      }
    }

    // create custom filename for each image, changing the number based on the
    // cycle
    std::string filename =
        "images/output/recaplaza_half_lerp_" + std::to_string(cycles) + ".jpg";
    writeJpeg(outputColorImage, (char *)filename.c_str(), 90);
  }
}
