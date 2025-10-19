
/*
    Warping an image using simple 2-D transformations:   Translation, Rotation
   and Scaling
*/

#define IMAGE_RANGE_CHECK

#include "image.h"
#include "jpegio.h"
#include "stdio.h"
#include "stdlib.h"
#include "string"
#include "tools.h"

// order of run command arguments are ./warp1.out "filename" "folderName"
// scalePercent angleDegrees translateX translateY
int main(int argc, char *argv[]) {
  int scalePercent = atoi(argv[4]);
  double angleDegrees = atoi(argv[5]);
  double angleRadians = angleDegrees * 3.14159 / 180.0;
  int translateX = atoi(argv[6]);
  int translateY = atoi(argv[7]);

  int x, y, height, width, frame;
  RGBImage img1, img2, img3, img4, img5;
  char fileName[200];

  std::string command = "mkdir images/output/" + std::string(argv[3]);

  readJpeg(img1, argv[1]);
  readJpeg(img4, argv[2]);
  height = img1.height(); // get the image's height in pixels
  width = img1.width();   // get the image's width in pixels

  system(command.c_str());
  for (int frame = 0; frame < 100; frame++) {
    scaleImageRGB(img2, img1, width * (scalePercent - frame * 1.25) / 100,
                  height * (scalePercent - frame * 1.25) / 100);
    scaleImageRGB(img5, img4, width * (scalePercent - frame * 1.25) / 100,
                  height * (scalePercent - frame * 1.25) / 100);

    // rotate the image by an angle angleRadians, around a specified center of
    // rotation
    rotateRGB(img5, img2, angleRadians + frame * 0.05, img2.width() / 2,
              img2.height() / 2); // rotate around the center
    //    translateRGB( img4, img3, translateX,translateY);
    // overlayImageRGB(img5, img3, 0, 0);
    sprintf(fileName, "images/output/exer6_rotate/warp-%03d.jpg", frame);
    writeJpeg(img5, fileName, 100);
  }
}
