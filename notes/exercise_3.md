## Commands to run

### Filter for outdoor image

./filter1.out "images/selfie_outdoor_resized.jpg" "images/output/median_so.jpg" "images/output/mean_so.jpg"

### Filter for indoor image

./filter1.out "images/selfie_indoor_resized.jpg" "images/output/median_si.jpg" "images/output/mean_si.jpg"

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
