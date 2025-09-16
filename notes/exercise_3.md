## Commands to run

### Filter for outdoor image

#### filter width = 15

./filter1.out "images/selfie_outdoor_resized.jpg" "images/output/exer_3/median15_so.jpg" "images/output/exer_3/mean15_so.jpg" 15

#### filter width = 25

./filter1.out "images/selfie_outdoor_resized.jpg" "images/output/exer_3/median25_so.jpg" "images/output/exer_3/mean25_so.jpg" 25

#### filter width = 7

./filter1.out "images/selfie_outdoor_resized.jpg" "images/output/exer_3/median7_so.jpg" "images/output/exer_3/mean7_so.jpg" 7

### Filter for indoor image

#### filter width = 15

./filter1.out "images/selfie_indoor_resized.jpg" "images/output/exer_3/median15_si.jpg" "images/output/exer_3/mean15_si.jpg" 15

#### filter width = 25

./filter1.out "images/selfie_indoor_resized.jpg" "images/output/exer_3/median25_si.jpg" "images/output/exer_3/mean25_si.jpg" 25

#### filter width = 7

./filter1.out "images/selfie_indoor_resized.jpg" "images/output/exer_3/median7_si.jpg" "images/output/exer_3/mean7_si.jpg" 7

### Extreme Filter Width

#### filter width = 100

./filter1.out "images/selfie_indoor_resized.jpg" "images/output/exer_3/median100_si.jpg" "images/output/exer_3/mean100_si.jpg" 100

./filter1.out "images/selfie_outdoor_resized.jpg" "images/output/exer_3/median100_so.jpg" "images/output/exer_3/mean100_so.jpg" 100

# EXERCISE 3

## Filter

### How does it work?

#### Median Filter

1. Convert image to grayscale, getting the gray values for each pixel.
2. Call the orderStatFilter function, passing the image, mask width, and the percent (where if 50% is the median)
3. In the orderStatFilter function, iterate through all pixels then check their neighbors with a size dependent on the filter width.
4. Put the neighborhood on a list which will be sorted using quickSort
5. After sorting, get the median and store it on an image object.
6. Once all pixels are done, return the image object containing the new pixels of the input image.
7. Create the new output image with the new pixels.

#### Mean Filter

1. Convert image to grayscale to get the gray values.
2. Create a mask for the mean filter.
3. Call the convolveDouble function which computes for the average of pixels on the neighborhood of the target pixel.
4. Change the value of the target pixel with the new one.
