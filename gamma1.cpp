
/*
 Changing the image contrast using gamma adjustment

*/

#define IMAGE_RANGE_CHECK

#include "image.h"
#include "jpegio.h"
#include "math.h"
#include "stdio.h"

int main() {

  int x, y, height, width;
  double red, green, blue;
  double redAdjusted, greenAdjusted, blueAdjusted;
  int pix;
  RGBImage inputimage, outputimage;
  char outputImageFilename[100];

  // if gamma is 0..1 , the dark intensities are stretched up
  // if gamma is 1..5 , the high intensities are stretched down
  double gamma = 3.0;

  // read the JPEG file
  readJpeg(inputimage, "images/against_the_light.jpg");
  height = inputimage.height();
  width = inputimage.width();

  printf("\nContrast adjustment parameter (gamma) = %3.2f \n", gamma);

  // set the dimensions of the output image
  outputimage.resize(width, height);

  // commented out to use another kind of implementation
  // adjust the contrast of each pixel
  for (y = 0; y < height; y++) {
    for (x = 0; x < width; x++) {
      pix = inputimage(x, y);
      red = RED(pix) / 255.0; // scale the r,g,b from 0..255 to 0..1
      green = GREEN(pix) / 255.0;
      blue = BLUE(pix) / 255.0;

      // gamma adjustment applied on the R,G and B components
      redAdjusted = pow(red, gamma);
      greenAdjusted = pow(green, gamma);
      blueAdjusted = pow(blue, gamma);

      // scale it back from 0..1 to 0..255
      outputimage.setPix(x, y, (int)(redAdjusted * 255),
                         (int)(greenAdjusted * 255), (int)(blueAdjusted * 255));
    }
  }

  // creating a part of the image to be affected
  // in this implementation, half of the image is affected with gamma while the
  // other is not
  // for (y = 0; y < height; y++) {
  //   for (x = 0; x < width; x++) {
  //     pix = inputimage(x, y);
  //     red = RED(pix) / 255.0; // scale the r,g,b from 0..255 to 0..1
  //     green = GREEN(pix) / 255.0;
  //     blue = BLUE(pix) / 255.0;
  //
  //     // gamma adjustment applied on the R,G and B components
  //     redAdjusted = pow(red, gamma);
  //     greenAdjusted = pow(green, gamma);
  //     blueAdjusted = pow(blue, gamma);
  //
  //     // if current pixel is currently on the top half, apply gamma
  //     if (y < height / 2) {
  //       outputimage.setPix(x, y, (int)(redAdjusted * 255),
  //                          (int)(greenAdjusted * 255),
  //                          (int)(blueAdjusted * 255));
  //     } else { // if not, reapply the original value
  //       outputimage.setPix(x, y, (int)(red * 255), (int)(green * 255),
  //                          (int)(blue * 255));
  //     }
  //   }
  // }
  // write the output to a JPEG file
  sprintf(outputImageFilename,
          "images/output/exer_2/gamma%03d_againstthelight.jpg",
          (int)(100 * gamma));
  writeJpeg(outputimage, outputImageFilename, 70);
  // the last parameter is quality (1..100 = best)
}
