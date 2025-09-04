# EXERCISE 1 NOTES

## Exercise 1-1: Converting image to grayscale

### How a color JPEG image is read?

A JPEG image is first read using the jpegio.c with its readJpeg() function, checking if the image can be read. If it can be read, it loads the data such as the image's width, height, and pixel color information. This is stored in an object named inputColorImage passed from the gray1.cpp file.

### How a color image is created/duplicated?

The color image is created by first creating a gray value map for the read image using the function makeGrayFromRGB(). Then, it assigns the certain grayValue to its respective pixel in the image. Once it has iterated over all the pixels, the gray image is pretty much created. Lastly, to still be able to get the colored strip effect in the image, the initial inputColorImage(x,y) is copied to the outputColorImage only on certain pixels.

### How pixels are accessed and modified?

In the function makeGrayFromRGB(), the pixels are accessed using the built-in RED(), GREEN(), and BLUE() functions that is able to get the values for their respective color. For instance, a pixel may have these values (255, 100, 75). Once this value is read, the gray value would then be calculated with the formula (red + green + blue) / 3. The result would then be appended to the grayOutput[] array which would be used later.

Now that the grayImage() has the gray values for each pixel, it can now be used to append to the outputColorImage which is a counterpart of the inputColorImage where the pixels will now have gray values of its color. Once the double for-loop finishes, the image data should now be all in grayscale. To restore the color of a "strip", just copy the initial inputColorImage (with the untouched RGB values) to the outputColorImage (with the gray values).

### How to write the output to a color JPEG image?

The output is made by passing the outputColorImage data to the writeJpeg() function alongside the quality that we want the image to have. Inside the writeJpeg() function, it calls the write_JPEG_file() function which consists of multiple steps of creating an output. First, it allocates and initializes a JPEG compression object. Then, it specifies the data destination or where it will be saved. It then sets the parameters for compression such as the width, height, color components per pixel, and the color space (which is RGB in our case). Next, it starts the compressor and the scan lines are written. The scanlines are a row of pixels that are being compressed and written to the final image file. Once done, the image buffer (used for each scanline) will be deleted to clear memory.

## Exercise 1-2: Converting a rectangular PART of a color image to grayscale

### Changes in the code and values used

1. Instead of creating a gray image first, we first create the RGB version first for the outputColorImage for all the pixels. Then, loop around a part of the image using hardcoded pixels to position the rectangle and then change the value of the outputColorImage to the gray value one.
2. For the rectangle, the values used are startX = 135, endX = 300, startY = 200, endY = 400.

## Exercise 1-3: Drawing a box on an image canvas

### Changes in the code and values used

1. Change the image to be read with my selfie in the images/ folder.
2. Change the starting and ending coordinates for X and Y.
3. startX = 135, endX = 300, startY = 135, endY = 350
4. The output image creates a line by looping on the pixels in a vertical or horizontal fashion. It then appends a certain color to the certain pixel coordinate, creating a "line".

# Journal Output

### 1. Retain the original values found in the sample codes. Then, compare the outputs generated using the sample image and your new selfie image. What have you observed?
