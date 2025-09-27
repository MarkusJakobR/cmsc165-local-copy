# Exercise 4: Sharpening

### Commands in Terminal

#### Argument order:

##### executable file, directory of input image, filterWidth, contrast, blackThreshold

./sharp1.out "images/recaplaza_exer4.jpg" 15 25 5

./sharp1.out "images/recaplaza_exer4.jpg" 1

## Algorithm Explanation

### Unsharp Mask Function

1. First, take the gray equivalent of an image made in the main function.
2. To create a contrasted version of the image, use histogram equalize while also taking a contrast value depending on the needs of the user. Contrast can be within 1-100 with a higher contrast value means the image is more contrasted.
3. Create a copy of the gray image then undergo mean filtering to make it blurry. This will clean the edges of the original image, reducing the visible edges.
4. Create an image variable for the difference and sharpness.
5. For all pixels, take the absolute value of the difference between its gray value and the value after applying mean filter.
6. If the difference is greater than the threshold, it means that it is most likely an edge and apply the histeq pixel value. If the difference is less than the threshold, then it is most likely NOT an edge and just apply the original. This makes the edges appear sharper.
7. Return the sharp image and create the output image.

### Laplacian Mask Function

1. Here, we need the laplacian kernel which makes it so we can find the zero crossing of a pixel. The grid is in the code.
2. Again, create a copy of the gray image. Then this will be passed to be convolved with the laplacian kernel as the mask.
3. To get the new sharpened value, subtract the original pixel value which is the gray value and the laplacian value which is acquired after doing the convolution. There is a strength parameter that can be between 0-1 where 1 is the most powerful and 0 has no effect.
4. The sharpened value then kept between 0-255 if they went past the range.
5. Assign the new sharpened value to the image pixel and return that image.
6. Create the output image in main.

### Main Function

1. In this function, there are two major if else conditions. If the number of arguments in the command is equal to 3, it will do the laplacian filter since it only needs three arguments. If the number of arguments is equal to 5, it will do the unsharp mask filter since it needs five arguments.
2. The implementation is the same for both, and it also alters the file name to note what are the values used.

## Answers in the Journal Questions

1. Image sharpening works by finding the edges of an image then converts those edges into its contrasted version (either by increasing if its high or decreasing if its low), creating the illusion of the image being "sharper".
2. For unsharpen mask:

- contrast: if contrast is higher, the sharpened pixels are more dominant and the noises are more seen in the image. It also looks like the edges are less visible because if the non-edges are being applied with contrast.
- black threshold: if the threshold is higher, less pixels and edges are sharpened because they must have a really high difference to be considered an edge. A lower threshold means more pixels with more noticeable difference from its mean mask one is considered.
- filter width: a higher value means the image to be compared with the original is more blurrier thus more pixels are considered an edge because of the condition.

For laplacian mask:

- strength: this just multiplies the strength of the laplacian value. For instance, if it is 0.5 then the strength of the laplacian is only half. If 1, then the full laplacian value is used, and if 0 then no laplacian value is used.

3. Image sharpening is used for correcting image blurring especially from camera equipments resulting to a more clearer and sharper image. It is also used to improve legibility which is exceptionally useful in character recognition for text that are possibly blurry. It can also be used for increasing readability in printed materials like posters or digital media like in movies or ads.
