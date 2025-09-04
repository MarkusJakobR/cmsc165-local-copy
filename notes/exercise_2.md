# EXERCISE 2: Histogram

## EXER 2-1: hist1.cpp

### How does it work?

1. Reads the JPEG file as usual
2. Creates an instance of the image where it has turned its values into gray
3. Create a table of values where it would be like an array with the index as the gray value
4. Check the gray value of a pixel and increment 1 to the certain index (gray value) to count the frequency of that gray value. Take note of the value with the highest frequency, this will be used later for creating the histogram
5. Create a histImage with a size 256x256. For every gray value, draw a height y with its value based on the formula 255 \* (hist(x) / hist(gmax)). This ensures that it would scale on the limit of the histogram and won't get past the 256 height limit.
6. Write the jpeg of the histogram.

## EXER 2-2: bright1.cpp

### How does it work?

1. First, you pick a brightness adjustment parameter. It must be within -1 to 1. If < 0, it will darken, > 0 will brighten
2. Read the jpeg you want by changing the file name.
3. Resize the output image based on the height and width of the input
4. Iterate using a nested for loop where it accesses per pixel. Check the RGB value for each pixel then adjust it depending on if it will brighten or darken. The values will be scaled down to 0..1 by dividing with 255.
5. Brighten: RGB _ (1.0 - brightAdjust) + brightAdjust;
   Darken: RGB _ (1.0 - fabs(brightdjust));
6. Scale the value back to 255 by multiplying with 255.
7. Write the created jpeg to a specified directory and file name.

## EXER 2-3: gamma1.cpp

### How does it work?

1. Pick a gamma value, values within 0..1 get the dark intensities stretched up (dark ^^, light ^), while values within 1..5 get the high intensities stretched down (light gets darker faster than the already dark ones)
2. Read the jpeg file again
3. Set an output image with the same dimensions
4. Nested for loop similar to the brightness one.
5. Adjust the RGB values for each pixel with the formula pow(RGB, gamma).
6. Scale the value back to 255 and set the new pixel value to the output image
7. Write the new jpeg
