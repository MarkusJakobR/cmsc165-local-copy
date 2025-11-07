# Notes on Exer 11 K-Means Clustering

## Commands to run

## Usage:

./kmeans1.out <input_image> <number of clusters>

## Example:

./kmeans1.out "images/kristen.jpg" 5
./kmeans1.out "images/corals1.jpg" 5

## How it works:

K-means clustering is a way to segment the image based on certain clusters. In its simplest form, each cluster has an initial point and each point is calculated to find which cluster is it closest to. It is then grouped based on their current closest clusters. After that, it calculates the new mean based on the current clusters and that new mean will be the new centroid for each cluster. This iterates for 15 iterations to ensure that the centroids are as closest and as accurate to their color groups.

Once the pixels are grouped in the best clusters, the image is created for each cluster. It checks if a pixel in the label matrix is part of the current cluster then adds the pixel to the output image. If not, it remains gray.

# Journal Questions Answers

1. Assuming that K is not initially known, how would you modify the program to automatically find the best value of K?

- A way to do this is using the Elbow Method which finds the best cluster by using the Within-Cluster Sum of Squares (WCSS) which measures the total squared distance between each point and the centroid of its assigned cluster. The graph of these values dictate will show an "elbow" in the curve which is the point on the plot where the rate of decrease in WCSS significantly slows down.
- There is also the Silhouette method where it measures how well each data point fits within its assigned cluster. Each cluster will have its point where the cluster with the highest points will be considered the optimal K.
- It is important to understand that there is no one true approach in finding the best K and using your best judgement will sometimes be the better choice.

2. Enumerate real world problems where you could apply these techniques.

- In medical imaging, segmentation of images can be used to find regions of interest especially on scans like tumor and lesion detection, tissue segmentation, and certain x-rays.
- In computer vision, this can be used in object recognition based on color zones. It is also used for image compression by limiting the number of unique colors in an image, usually from millions to some small K. It is also used in surveillance detection where it can detect changes like a moving object which can automatically send alerts.
