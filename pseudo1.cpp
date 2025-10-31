
/*
   Psuedo-coloring a gray scale image

*/

#define IMAGE_RANGE_CHECK

#include "image.h"
#include "jpegio.h"
#include "string.h"
#include "tools.h"

// creates a color map to the image based on the input type
int colorFromGray(const char *colorMap, double gray) {
  if (strcmp(colorMap, "summer") == 0) {
    if (gray > 0.95)
      return COLOR_RGB(0, 132, 99);
    else if (gray > 0.85)
      return COLOR_RGB(17, 140, 99);
    else if (gray > 0.75)
      return COLOR_RGB(49, 156, 99);
    else if (gray > 0.65)
      return COLOR_RGB(82, 173, 98);
    else if (gray > 0.55)
      return COLOR_RGB(115, 189, 99);
    else if (gray > 0.45)
      return COLOR_RGB(169, 214, 99);
    else if (gray > 0.35)
      return COLOR_RGB(188, 222, 99);
    else if (gray > 0.25)
      return COLOR_RGB(201, 231, 99);
    else if (gray > 0.15)
      return COLOR_RGB(238, 247, 99);
    else if (gray > 0.05)
      return COLOR_RGB(255, 255, 98);
    else
      return COLOR_RGB(255, 255, 255);
  } else if (strcmp(colorMap, "cool") == 0) {
    if (gray > 0.95)
      return COLOR_RGB(3, 255, 255);
    else if (gray > 0.85)
      return COLOR_RGB(22, 239, 255);
    else if (gray > 0.75)
      return COLOR_RGB(50, 206, 255);
    else if (gray > 0.65)
      return COLOR_RGB(83, 166, 255);
    else if (gray > 0.55)
      return COLOR_RGB(115, 140, 255);
    else if (gray > 0.45)
      return COLOR_RGB(173, 82, 255);
    else if (gray > 0.35)
      return COLOR_RGB(203, 52, 255);
    else if (gray > 0.25)
      return COLOR_RGB(222, 34, 255);
    else if (gray > 0.15)
      return COLOR_RGB(239, 15, 255);
    else if (gray > 0.05)
      return COLOR_RGB(255, 0, 255);
    else
      return COLOR_RGB(255, 255, 255);
  } else if (strcmp(colorMap, "hot") == 0) {
    if (gray > 0.95)
      return COLOR_RGB(42, 0, 0);
    else if (gray > 0.85)
      return COLOR_RGB(87, 0, 0);
    else if (gray > 0.75)
      return COLOR_RGB(173, 0, 0);
    else if (gray > 0.65)
      return COLOR_RGB(214, 0, 1);
    else if (gray > 0.55)
      return COLOR_RGB(255, 0, 0);
    else if (gray > 0.45)
      return COLOR_RGB(255, 82, 0);
    else if (gray > 0.35)
      return COLOR_RGB(255, 160, 0);
    else if (gray > 0.25)
      return COLOR_RGB(255, 255, 0);
    else if (gray > 0.15)
      return COLOR_RGB(255, 255, 132);
    else if (gray > 0.05)
      return COLOR_RGB(255, 255, 189);
    else
      return COLOR_RGB(255, 255, 255);
  } else {
    if (gray > 0.95)
      return COLOR_RGB(255, 255, 255); // white
    else if (gray > 0.90)
      return COLOR_RGB(255, 128, 128); // light red
    else if (gray > 0.85)
      return COLOR_RGB(255, 0, 0); // red
    else if (gray > 0.80)
      return COLOR_RGB(255, 128, 0); // orange
    else if (gray > 0.75)
      return COLOR_RGB(0, 255, 0); // green
    else if (gray > 0.70)
      return COLOR_RGB(0, 128, 128); //
    else if (gray > 0.65)
      return COLOR_RGB(0, 0, 255); // blue
    else if (gray > 0.60)
      return COLOR_RGB(0, 0, 128); // dark blue
    else
      return COLOR_RGB((int)(gray * 255), (int)(gray * 255),
                       (int)(gray * 255)); // gray
  }
};

int main(int argc, char *argv[]) {
  int x, y, height, width;
  double gray;
  int pix, color;
  RGBImage inputimage, outputimage;
  char filename[200];
  char extractedFilename[200];
  extractFilename(extractedFilename, argv[1]);

  // read the JPEG file
  readJpeg(inputimage, argv[1]);
  height = inputimage.height();
  width = inputimage.width();

  // set the dimensions of the output image
  outputimage.resize(width, height);

  // compute the gray scale of the colored picture
  // and assign a color to each range of the gray scale
  for (y = 0; y < height; y++)
    for (x = 0; x < width; x++) {
      pix = inputimage(x, y);
      gray = (RED(pix) + GREEN(pix) + BLUE(pix)) / 3.0;
      gray = gray / 255.0; // scale it to 0..1
      color = colorFromGray(argv[2], gray);
      outputimage(x, y) = color;
    }

  // write the output pseudo-color image to a JPEG file
  sprintf(filename, "images/output/exer_9/%s_%s_pseudo.jpg", extractedFilename,
          argv[2]);
  writeJpeg(outputimage, filename, 70);
}
