# Commands to run

## Order of commands are:

./warp1.out "filename" "background filename" "folderName" scalePercent angleDegrees translateX translateY

./warp1.out "images/recaplaza_exer5.jpg" "images/recaplaza_exer5.jpg" "exer5_test" 200 45 40 60

./warp1.out "images/exer6_foreground.jpg" "images/exer6_background.jpg" "exer6_rotate" 200 45 40 60

Journal Questions:

1. The geometric transforms that I have applied are scaling, rotation, and translation/overlaying. They have their own effects to the image input. For scaling, it finds the closest color a pixel can be by finding it in the reference image. This ensures that the new image is as close as possible to the original. A caveat here is that the image may look blocky or pixelated because each pixel has only been enlarged, giving the illusion of scaling up. For rotation, the general idea is to find out what pixel value will land on a certain coordinate when the image is rotated. In the implementation, it loops through the output image and finds out what pixel does it correspond to the input image. Lastly, for translation or overlaying, all it needs is for the background image to be the current image and that is where the foreground image will be pasted on by swapping the values for each pixel an image will be. This gives the illusion that the image is above the background.

2. An example of transformation is by skewing. In an image processing, the image is skewed to create a new shape, usually a parallelogram. This will again use inverse mapping to find out what pixel will be on the output image.

3. Image transformation is widely used in different mediums. Scaling can be used in Web & Mobile Design to keep the elements responsive and fit on a certain container. It can also be used in printing and publishing mediums like newspaper and magazines where images can be adjusted to fit the paper size. For rotation, it can be used for image scanning to fix certain orientations or in the augmented reality world where it adjusts the image's orientation depending on the user's view angle. Lastly, overlaying images are used for graphic designing to combine certain elements and create something new.
