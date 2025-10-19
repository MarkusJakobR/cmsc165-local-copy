# NOTES

## Commands to run for binary1.cpp

./binary1.out "images/objects.jpg" 150

./binary1.out "images/marbles.jpg" 150

./binary1.out "images/pikachu.jpg" 150

./binary1.out "images/selfie_indoor_resized.jpg" 150

## Commands to run for clean1.cpp

./clean1.out "images/objects.jpg" 130 7

./clean1.out "images/marbles.jpg" 200 7

./clean1.out "images/pikachu.jpg" 255 7

./clean1.out "images/pikachu.jpg" 150 7

## Explanation for Intensity Threshold

In the code, it compares the gray intensity value to the intensity threshold. If gray is less than the threshold, it is part of the object. So, a higher IT means more pixels gets detected as part of the object especially the non-black or higher pixel values. For instance, a black outline has a lower pixel value, so it can be detected with a lower intensity threshold. A yellow color has higher intensity value so it gets detected only when the IT is higher. If the IT is 256, then the whole image will turn black because every intensity value is less than the threshold (including white).

# Answer to Journal Questions

### 1. How does the structuring element size affect the image output?

The structuring element affects the image output in clean1.cpp by increasing the size it affects during binary dilation and erosion. For instance, in dilation, if the center of the strucElem is a 1 or a part of the "object", it stamps the whole area of the strucElem, filling out the neighboring pixels. If the strucElem is bigger, then that means it would affect a larger area. If its too large, it may end up making the result inaccurate, which is why it is important to adjust the values as needed.

### 2. Discuss how you have produced the outline of the object through morphological operations.

I produced it by "subtracting" the results of the dilation and erosion in clean1.cpp. Since we know that dilation makes the binary image "inflate" and the erosion to "deflate", I tried to find the values in between, creating a n outline of the object. In the code, for every pixel in the binary image of dilation and erosion, compare if they are not equal. If they are not equal, then that means it is the subtracted part, which is the outline of the object.

### 3. If the background is not of a single plain color, what would be a good strategy for separating the background from the foreground objects?

A simple way to do this is by using an adaptive threshold. This is done by computing for the mean of the neighborhood of a pixel (within a certain filter width) then compare the center pixel's intensity value to it. This way, the threshold changes for every pixel, accounting the changes in its background.

### 4. Enumerate real-world problems where you could apply these techniques.

Binary image techniques have a lot of use cases in the real world. One major example is object detection as it can isolate objects from the background. It can be used to count these objects, measure, and identify based on its shape. Another example is with optical character recognition where it can isolate the text from a certain medium. These are used by some software to copy text from a photo or a pdf. In computer vision, this can also be used to study changes in a static view. For instance in a street view, it can separate objects like cars and pedestrians to detect their movement, analyze their plate numbers, etc.
