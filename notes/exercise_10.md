# Exercise 10 Notes

## Commands to run

### ./hsi1.out filename saturation intensity /hue/

./hsi1.out "images/kristen.jpg" 0.5 0
./hsi1.out "images/kristen.jpg" 0.25 0
./hsi1.out "images/kristen.jpg" 0 0
./hsi1.out "images/happy1.jpg" 0.5 0
./hsi1.out "images/happy1.jpg" 0.25 0
./hsi1.out "images/happy1.jpg" 0 0
./hsi1.out "images/happy1.jpg" -0.5 0

### ./color1.out filename minHueDeg maxHueDeg minSat maxSat

./color1.out "images/scene1.jpg" -45 45 0.3 1
./color1.out "images/scene1.jpg" 60 75 0 0.1
./color1.out "images/skin-color.jpg" 0 50 0.2 0.7
./color1.out "images/skin-color.jpg" 0 50 0.1 0.8
./color1.out "images/skin-color.jpg" 13 34 0.1 0.8
./color1.out "images/skin-color.jpg" 10 40 0.1 0.8

./color1.out "images/pikachu.jpg" 40 80 0 1

# Journal Questions Answers

1. How does the saturation value affect output images?
   Saturation controls the vividness or purity of color. Increasing the saturation makes the colors more vibrant and powerful while decreasing it makes the colors duller as if its approaching gray. In the HSI double cone model, saturation are the values from the center of the inner circle to its edge. It affects how 'colorful' the image looks but not its brightness or hue.

2. What is the range of hue and saturation values that represent human skin tones?
   By testing out various values for hue and saturation, I arrived at the minimum and maximum hue value of 10 deg to 40 deg and a minimum and maximum saturation value of 0.1 to 0.8. The reason for the hue values is that skin color is reddish in nature due to the color of our blood. For the saturation values, it included the pale colors up to the highly pigmented colors.

3. Using what we have learned so far, what is a good algorithm to detect a face in an image?
   In order to detect a face in an image, we can use the function in color1.cpp to check if a pixel falls under the recommended skin-tone ranges. Once its found and the background has been removed, we can use binary dilation and erosion to fill out the holes and clean the noise. This makes it so the eyes, mouth, and other parts of the face that has some other value gets filled out and we get the whole face, not just the skin.

4. Enumerate real-world problems where you could apply these techniques
   As mentioned in the previous samples, this can be used in face detection like the ones we use in our phones (albeit its much more advanced). It can also be used in gesture detection since we detect the skin as well not just the face. It can also be used for color detection especially for certain objects like traffic lights or clothes. It can also be used for human tracking as humans can be distinguished from the background because of their skin-tone.
