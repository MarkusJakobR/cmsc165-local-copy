/*
 * Draw a triangle on each eye and a circle on the head
 */

#define IMAGE_RANGE_CHECK

#include "image.h"
#include "jpegio.h"

int main() {
  int x, y, height, width, triadjacentX1, triadjacentX2;

  int triColor = COLOR_RGB(255, 153, 51);
  int circColor = COLOR_RGB(255, 192, 203);

  int tristartX1 = 145;
  int tristartY1 = 215;
  int triendY1 = 265;

  int tristartX2 = 260;
  int tristartY2 = 215;
  int triendY2 = 265;

  RGBImage inputimage, outputimage;

  readJpeg(inputimage, "images/recaplaza1_happy_resized.jpg");
  height = inputimage.height();
  width = inputimage.width();

  outputimage = inputimage;

  // left triangle
  triadjacentX1 = tristartX1;
  for (y = tristartY1; y < triendY1; y++) {
    outputimage(tristartX1, y) = triColor;
    outputimage(triadjacentX1, y) = triColor;
    triadjacentX1++;
  }
  for (x = tristartX1; x < triadjacentX1; x++) {
    outputimage(x, triendY1) = triColor;
  }

  // right triangle
  triadjacentX2 = tristartX2;
  for (y = tristartY2; y < triendY2; y++) {
    outputimage(tristartX2, y) = triColor;
    outputimage(triadjacentX2, y) = triColor;
    triadjacentX2--;
  }
  for (x = triadjacentX2; x < tristartX2; x++) {
    outputimage(x, triendY2) = triColor;
  }

  // circle in the head

  writeJpeg(outputimage, "images/output/recaplaza1_draw.jpg", 70);
}
