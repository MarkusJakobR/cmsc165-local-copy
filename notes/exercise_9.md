# NOTES ON EXER 9

## Commands to run

### ./pseudo1.out filename

./pseudo1.out "images/lily1.jpg" "summer"

./pseudo1.out "images/lily1.jpg" "cool"
./pseudo1.out "images/lily1.jpg" "hot"
./pseudo1.out "images/lily1.jpg" "summer"
./pseudo1.out "images/lily1.jpg" "default"

./pseudo1.out "images/corals1.jpg" "cool"
./pseudo1.out "images/corals1.jpg" "hot"
./pseudo1.out "images/corals1.jpg" "summer"
./pseudo1.out "images/corals1.jpg" "default"

./pseudo1.out "images/isidore1.jpg" "cool"
./pseudo1.out "images/isidore1.jpg" "hot"
./pseudo1.out "images/isidore1.jpg" "summer"
./pseudo1.out "images/isidore1.jpg" "default"

./pseudo1.out "images/isidore2.jpg" "cool"
./pseudo1.out "images/isidore2.jpg" "hot"
./pseudo1.out "images/isidore2.jpg" "summer"
./pseudo1.out "images/isidore2.jpg" "default"

./pseudo1.out "images/infra_es.jpg" "cool"
./pseudo1.out "images/infra_es.jpg" "hot"
./pseudo1.out "images/infra_es.jpg" "summer"
./pseudo1.out "images/infra_es.jpg" "default"

./pseudo1.out "images/infra_us.jpg" "cool"
./pseudo1.out "images/infra_us.jpg" "hot"
./pseudo1.out "images/infra_us.jpg" "summer"
./pseudo1.out "images/infra_us.jpg" "default"

./pseudo1.out "images/star1.jpg" "cool"
./pseudo1.out "images/star1.jpg" "hot"
./pseudo1.out "images/star1.jpg" "summer"
./pseudo1.out "images/star1.jpg" "default"

## Journal Question Answers

1. How does a pseudo-colored image compare to the original gray image

- The represented values for each pixel will be converted from gray to a color converted from RGB values. This makes it so a pseudo-colored image will have variations on their pixel values compared to the average value computed to get the gray intensity. Unfortunately, without the data of the original colored image, we will not be able to fully convert a gray image to its original color, only to colors that we specify for each gray intensity value.

2. Enumerate real world problems where you could apply these techniques

- Similar to the sample images, these techniques can be used in satellite images (which are originally grayscale) to represent some details and information such as the strength and wind speed of a typhoon or the heat index in a certain area. In graphic designing, I sometimes use these gradient maps as a design style because it isolates the image into a certain spectrum of colors.
