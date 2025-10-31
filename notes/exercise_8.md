# NOTES ON EXERCISE 8

## charseg1.cpp

#### Commands to run

### ./charseg1.out input threshold strucwidth

./charseg1.out "images/train1.jpg" 100 3

./charseg1.out "images/objects.jpg" 100 3

### Explanation to how it works:

Create the binary image of the image first which is based on the threshold input. Then with the strucWidth, create the strucElem which will be used for the binaryDilation function. The result of the binaryDilation should have filled out the random blank spaces in the object. Then, find the connected components using analyzeBinary using EIGHT_CONNECTED (diagonals are considered). Once the components have been found, display them with random colors to distinguish the separate components. Then to separate the components, iterate through each components and use getBoundary to find the boundary of each component and draw it in the charImage which has the binary image and actual image comparison.

#### Important variables:

threshold - this chooses which gray values get to join the binary image.
strucWidth - this is how large the strucElem will be on binary dilation. higher value = larger area of effect.

---

## count1.cpp

#### Commands to run

### ./count1.out input threshold strucWidth minimumArea maximumArea

./count1.out "images/coins1.jpg" 130 5 12000 13000

### Explanation to how it works:

In this program, the minimum and maximum area was declared. This is used to only include components that has a certain area. Similarly, the image undergoes binaryDilation and analyzeBinary with EIGHT_CONNECTED. Then for every component, get the boundary again but this time it only creates a boundary to the components that fit the minimum and maximum area. This ensures that certain components can be separated from the others.

#### Important variables:

threshold - this chooses which gray values get to join the binary image.
strucWidth - this is how large the strucElem will be on binary dilation. higher value = larger area of effect.
minimumArea - range of size of object to be boxed; minimum
maximumArea - range of size of object to be boxed; maximum

---

## boundary1.cpp

#### Commands to run

### ./boundary1.out input threshold strucwidth minimumArea maximumArea

./boundary1.out "images/hand7.jpg" 130 5 5 12000
./boundary1.out "images/hand7.jpg" 130 5 5 120000

### Explanation to how it works:

The same parameters were required but this time it solves for the perimeter. Create the binary image again and the components while also comparing if it fits the minimum and maximum area. This time, however, the object's boundary will be traced creating an outline. This is made using binaryFollowBoundary.

---

## page1.cpp

#### Commands to run

### ./page1.out input threshold

./page1.out "images/journal1.jpg" 130

### Explanation to how it works:

Still similar parameters except the maximum area is not needed, there is only a minimum area threshold. This time, there will be multiple runs of binary dilation. The strucWidth changes for each run, some fills very small gaps, groups characters into words, groups words into lines, or groups lines into paragraphs. This makes it so the result of binaryDilation will differ and some components will be connected or separated. The final process is the same which it draws the bounding box of each component to see which components are connected.

#### Important variables:

The strucElem will be applied on a journal page, thus the effects will be expected to these components.
strucWidth - higher means characters will be grouped making lines of words, smaller means characters can be isolated.
strucHeight - higher means characters stacked vertically will be detected more, smaller means it can stay within a line.
Combining both, to get a whole paragraph will need to have high strucWidth and strucHeight.

---

## measure1.cpp

#### Commands to run

### ./measure1.out input threshold ref_width_cm ref_length_cm

./measure1.out "images/hand7.jpg" 130 8.9 19.3

### Explanation to how it works:

Similar to previous programs, the threshold and strucWidth is needed with the same effects as other programs. Use binary dilation to get the component then the analyzeBinary to separate the components. Since we are focused on finding the dimensions of a certain subject, the component to analyze should be the one with the largest area. This is determined by using mCount for each detected component and compare each area to get the largest area.

Next, the farthest pair of points are determined to ensure that is where the length and width of the reference object will be computed. Then, take the area per pixel of the component. This will be used to compute the scale factor of the component which is length/width in real life divided by length/width based on pixels. To get the component's pixel area, we can use the binaryArea function. Then, use the functions binaryGetFirstPixel and binaryFollowBoundary to calculate for the perimeter.

Finally, computer for the area by multiplying the pixel area and scale factor. The perimeter is computed by the perimeter pixel and the scale factor. The length and width is the pixel length and width multiplied by the scale factor.

# Journal Questions

## 1. How does image resolution affect binary object features such as area and perimeter? What can be done to solve this problem?

If images are in low resolution, there are fewer pixels and loss of detail leading to inaccurate area and jagged edges that compute the parameter. The best way to solve this is to ensure a high resolution image is going to be used for a more accurate computation. If not possible, then measurements done can be calibrated better and perhaps use sub-pixel edge detection or smoothing to refine object boundaries.

## 2. Enumerate real-world problems

There are a lot of uses in object-detection, comparison, and computation of area and sizes. Some of which are used in autonomous vehicles where they are capable of detecting cars, pedestrian, and road signs. It is also used in object character recognition for document reading which is actually used in our PDF viewers. In engineering, it can also be used for land surveying, construction, electronics configuration and many more.
