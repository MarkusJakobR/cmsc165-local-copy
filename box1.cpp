
/*
   Draw a box on an image canvass

*/

#define IMAGE_RANGE_CHECK

#include "image.h"
#include "jpegio.h"

int main() {
  int x, y, height, width;

  int pixColor = COLOR_RGB(57, 255, 20); // color of the box
  int startX = 135;                      // bounding box of the gray part
  int endX = 300;
  int startY = 135;
  int endY = 350;

  RGBImage inputimage, outputimage;

  // read the JPEG file
  readJpeg(inputimage, "images/recaplaza1_resized.jpg");
  height = inputimage.height();
  width = inputimage.width();

  // copy the output image to input image
  outputimage = inputimage;

  // draw the left and right boundaries
  for (y = startY; y <= endY; y++) {
    outputimage(startX, y) = pixColor;
    outputimage(endX, y) = pixColor;
  }

  // draw the top and bottom boundaries
  for (x = startX; x <= endX; x++) {
    outputimage(x, startY) = pixColor;
    outputimage(x, endY) = pixColor;
  }

  // write the output to a JPEG file
  writeJpeg(outputimage, "images/output/recaplaza1_box.jpg", 70);
  // the last parameter is quality (1..100 = best)
}
