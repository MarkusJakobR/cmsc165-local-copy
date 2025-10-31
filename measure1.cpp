/*
  A program to measure the area, perimeter, width, and length of objects in an
  image.
*/

#define IMAGE_RANGE_CHECK

#include "binary.h"
#include "image.h"
#include "jpegio.h"
#include "stdio.h"
#include "stdlib.h"
#include "tools.h"

int main(int argc, char *argv[]) {

  if (argc < 5) {
    printf("Usage: %s <input_image.jpg> <threshold> <ref_width_cm> "
           "<ref_length_cm>\n",
           argv[0]);
    return 1;
  }

  RGBImage inputImage, outputImage, boundaryRGB;
  Image<unsigned char> binary, binary2, strucElem, componentImage;

  ConnectedComponents cc;

  char extractedFilename[200];
  extractFilename(extractedFilename, argv[1]);

  int intensityThreshold = atoi(argv[2]);
  float ref_width_cm = atof(argv[3]);
  float ref_length_cm = atof(argv[4]);
  int strucWidth = 3; // Structuring element width for cleaning

  readJpeg(inputImage, argv[1]);
  int height = inputImage.height();
  int width = inputImage.width();
  int x, y, gray, c;

  // Binarize the image
  binary.resize(width, height);
  binary.setAll(0);
  for (x = 0; x < width; x++) {
    for (y = 0; y < height; y++) {
      gray = (RED(inputImage(x, y)) + GREEN(inputImage(x, y)) +
              BLUE(inputImage(x, y))) /
             3;
      if (gray < intensityThreshold)
        binary(x, y) = 1;
    }
  }

  // Clean the binary image
  strucElem.resize(strucWidth, strucWidth);
  strucElem.setAll(1);
  binaryDilation(binary2, binary, strucElem, strucWidth / 2, strucWidth / 2);

  // Find connected components
  cc.analyzeBinary(binary2, EIGHT_CONNECTED);

  if (cc.getNumComponents() == 0) {
    printf("No objects detected in the image.\n");
    return 0;
  }

  // --- Reference Object Measurement ---
  // Assume the largest object is the reference object
  int largest_area = 0;
  int ref_obj_index = -1;
  for (c = 0; c < cc.getNumComponents(); c++) {
    int area = cc.mCount(c, 1);
    if (area > largest_area) {
      largest_area = area;
      ref_obj_index = c;
    }
  }

  if (ref_obj_index == -1) {
    printf("Could not identify a reference object.\n");
    return 1;
  }

  componentImage = cc.getComponentBinary(ref_obj_index);

  int ref_x1, ref_y1, ref_x2, ref_y2, ref_length_px;
  farthestPairOfPoints(ref_x1, ref_y1, ref_x2, ref_y2, ref_length_px,
                       componentImage);

  int ref_area_px = binaryArea(componentImage);
  float ref_width_px =
      (ref_length_px > 0) ? (float)ref_area_px / ref_length_px : 0;

  if (ref_length_px == 0 || ref_width_px == 0) {
    printf("Error: Measured size of reference object is zero. Cannot calculate "
           "scale factor.\n");
    return 1;
  }

  // --- Scale Factor Calculation ---
  float scale_factor_length = ref_length_cm / ref_length_px;
  float scale_factor_width = ref_width_cm / ref_width_px;
  float scale_factor_area = scale_factor_length * scale_factor_width;

  printf("\n\n--- Reference Object (Object %d) ---\n", ref_obj_index);
  printf("  Measured Length: %d px\n", ref_length_px);
  printf("  Measured Width:  %.2f px\n", ref_width_px);
  printf("  Scale Factor (Length): %f cm/px\n", scale_factor_length);
  printf("  Scale Factor (Width):  %f cm/px\n", scale_factor_width);
  printf("------------------------------------\n\n");

  // --- Process and Measure All Objects ---
  printf("Found %d objects. Measurements:\n", cc.getNumComponents());
  for (c = 0; c < cc.getNumComponents(); c++) {
    componentImage = cc.getComponentBinary(c);

    // --- Pixel Measurements ---
    int area_px = binaryArea(componentImage);

    float perimeter_px;
    int boundStartX = 0, boundStartY = 0;
    // Find first pixel to start boundary tracing
    binaryGetFirstPixel(boundStartX, boundStartY, componentImage);
    binaryFollowBoundary(boundaryRGB, perimeter_px, componentImage, boundStartX,
                         boundStartY);

    int x1, y1, x2, y2, length_px;
    farthestPairOfPoints(x1, y1, x2, y2, length_px, componentImage);

    float width_px = (length_px > 0) ? (float)area_px / length_px : 0;

    // --- Centimeter Measurements ---
    float area_cm2 = area_px * scale_factor_area;
    float perimeter_cm = perimeter_px * scale_factor_length; // Approximation
    float length_cm = length_px * scale_factor_length;
    float width_cm = width_px * scale_factor_width;

    // --- Output ---
    printf("--- Object %d ---\n", c);
    printf("  Area:      %d px^2  =>  %.2f cm^2\n", area_px, area_cm2);
    printf("  Perimeter: %.2f px   =>  %.2f cm\n", perimeter_px, perimeter_cm);
    printf("  Length:    %d px   =>  %.2f cm\n", length_px, length_cm);
    printf("  Width:     %.2f px   =>  %.2f cm\n", width_px, width_cm);
  }

  return 0;
}
