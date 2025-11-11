# Exercise 12 Notes

## Files:

### change1.cpp

#### usage:

./change1.out <input_filename_1> <input_filename_2> <threshold>

#### example:

./change1.out "images/scene1.jpg" "images/change4.jpg" 40
./change1.out "images/scene1.jpg" "images/change4.jpg" 80

#### how it works:

It compares the two input images and checks for pixels having significant different values (determined by a threshold). If there is a change, keep the pixel from the change jpeg and the others with white. This isolates the changed object.

---

### mtrack1.cpp

#### usage:

./mtrack1.out <isFollowCar>

#### example:

./mtrack1.out 0

#### how it works:

In the code, the initial object being tracked is hardcoded (i.e., the initial position). The trajectory storage is initialized to store the tracked center coordinates of the object for every frame. The vicinity dictated by the vicinity margin defines the size of the search window around the object's predicted location. The code then iterates through the video frames, maintaining a buffer of the last four frames. For each frame, it compares the current frame with the frame three steps prior. It calculates the weight of change by comparing the absolute value of each RGB pixel. To determine the trajectory and tracking the motion, the weight acts as the mass and the center (centroid) changes depending on the new position of the weight. Lastly, it generates an output frame where the previous frames are compared and the overall motion of the object in gray dots.

---

### ctrack1.cpp

#### usage:

./ctrack1.out <isTrackBlue>

#### example:

./ctrack1.out 1

#### how it works:

Similar to how the object was tracked in motion track, it uses the trajectory and vicinity to check for changes in movement per frame. The difference is that it keeps track of what the color is so it knows which object to follow and it would not be confused. Unlike the previous function, there's two objects moving at the same time that are almost identical. Tracking the color helps the algorithm to not get confused on which object to follow.

---

### backsub1.cpp

#### usage:

./ctrack1.out

#### how it works:

Firstly, the code iterates through a subset of frames (usually depending on the frame interval) then the background is converted to grayscale to reduce complexity. For every pixel in each frame subset, the median pixel is taken since it is most robust against noise and motion especially little or insignificant ones. Next, the background will be subtracted from the foreground, ensuring that only the moving subjects will be kept. The difference value is compared to a certain threshold. The output is the original image of the certain frame and the resulting image where the background is subtracted and the foreground remains.

---

### corr1.cpp

#### usage:

./corr1.out

#### How does it work:

First, it creates a static image of the scene to use as a reference pattern or the template. The moving objects will be discarded leaving only the scene itself. This is done by having the gray median which will have the intensity values of the static background. Next, occlusion detection using normalized cross-correlation is done by having a region of interest for both the current frame and the static background template. If there is high correlation, then the ROI on the current frame is very similar to the background template thus there is no change. If the correlation is low, then the ROI on the current frame is very different to the background template thus there is an occlusion. This happens when a car enters the ROI. The history of display values and where an occlusion occurred is drawn to the image, and the ROI box also turns into a different color when a change is detected.

---

# Journal Questions

## 1. What are the possible situations that could confuse the motion tracker in mtrack1.cpp? In ctrack1.cpp?

- In mtrack1.cpp, a possible situation of confusion for the motion tracker is when there are multiple moving objects in the vicinity of the currently tracked object. It is possible for the tracker to jump to another object since it does not know which of the other objects is the one they are originally tracking. Another is when there is a large shadow casted over the object that will increase weight in the motion image. This weight may mislead the tracker, losing the actual object. There is also the problem of the object being fully stationary in a few frames which will make the tracker stop tracking the object or go to another object in the vicinity that has movement.

- In ctrack1.cpp, a most possible confusing situation is when a similarly colored object gets near the search vicinity. The tracker may jump to the other object since they have the same color and it satisfies the color set. Additionally, if the lighting and shadows of the image change significantly, it may affect the color of the object which can result to losing the tracked object.

## 2. How does corr1.cpp work?

- First, it creates a static image of the scene to use as a reference pattern or the template. The moving objects will be discarded leaving only the scene itself. This is done by having the gray median which will have the intensity values of the static background. Next, occlusion detection using normalized cross-correlation is done by having a region of interest for both the current frame and the static background template. If there is high correlation, then the ROI on the current frame is very similar to the background template thus there is no change. If the correlation is low, then the ROI on the current frame is very different to the background template thus there is an occlusion. This happens when a car enters the ROI. The history of display values and where an occlusion occurred is drawn to the image, and the ROI box also turns into a different color when a change is detected.

## 3. Enumerate real-world problems where you could apply these techniques.

- Some real-word problems that these techniques are applied to are traffic monitoring and flow analysis, just like those used in NCAP where they tracked the vehicles entering a certain lane while also taking note of their plate number. It can also be used for surveillance when it detects that something is moving when there shouldn't be, something like an intrusion detection. It can also be used in industry quality control situations where they can automate if something is missing from a certain product by comparing it to the correct one.

---

## Create video from multiple image frames using this command:

ffmpeg -framerate 25 -i <directory with the images> -c:v libx264 -crf 23 -pix_fmt yuv420p <output name/directory>

### input videos

#### student

ffmpeg -framerate 25 -i student%04d.jpg -c:v libx264 -crf 23 -pix_fmt yuv420p student_input.mp4

#### redblue

ffmpeg -framerate 25 -i redblue%04d.jpg -c:v libx264 -crf 23 -pix_fmt yuv420p redblue_input.mp4

#### kids

ffmpeg -framerate 25 -i %04d.jpeg -c:v libx264 -crf 23 -pix_fmt yuv420p kids_input.mp4

#### car1

ffmpeg -framerate 25 -i %04d.jpeg -c:v libx264 -crf 23 -pix_fmt yuv420p car1_input.mp4

### output videos

#### backsub student

ffmpeg -framerate 25 -i backsub%04d.jpg -c:v libx264 -crf 23 -pix_fmt yuv420p backsub_student_out.mp4

#### color track redblue

ffmpeg -framerate 25 -i %04d.jpg -c:v libx264 -crf 23 -pix_fmt yuv420p ctrack_redblue_out.mp4

#### motion track kids

ffmpeg -framerate 25 -i %04d.jpg -c:v libx264 -crf 23 -pix_fmt yuv420p mtrack_kids_out.mp4

#### motion track car

ffmpeg -framerate 25 -i %04d.jpg -c:v libx264 -crf 23 -pix_fmt yuv420p mtrack_car_out.mp4

#### correlation sixlanes

ffmpeg -framerate 25 -i %04d.jpg -c:v libx264 -crf 23 -pix_fmt yuv420p corr_sixlanes_out.mp4
