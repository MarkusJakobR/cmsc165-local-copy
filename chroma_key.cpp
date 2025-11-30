
/* 
 Chroma keying simple example
 Study the program well and modify it for this works only with my choir singing video in the lecture
 and i hardcoded many of the values like number of frames in the video etc
You may modify this to include binary cleaning --> green-screen pixels vs non-green-screen pixels 
*/


#define IMAGE_RANGE_CHECK

#include "image.h"
#include "jpegio.h"
#include "color.h"
#include <stdlib.h>


int main (int argc, char *argv[]) {
   int x,y, height,width, pixColor,max_green,min_green;
   double red, green, blue;
   double hue, saturation, intensity, satNew, intNew;
   RGBImage inputImage, outputImage, backgroundImage;
 
   char image_seq[150], outputFileFormat[100];
   char inputImageFile[100],outputImageFile[100];
	int hue_index;

   if (argc!=4) {
		printf("Usage: chroma_key <background image> <folder_with_image_sequence> <output_folder>\n");
		return 0;
   }

   //read image background
   readJpeg( backgroundImage, argv[1] );
   height = backgroundImage.height();
   width  = backgroundImage.width();

   //read folder source
   strcpy(image_seq, argv[2]);
   printf("Root folder is %s\n", image_seq);

   //append file name string format of image sequence
   strcat(image_seq,"\\%04d.jpg");
   printf("File format string of image sequence: %s\n", image_seq);
	
    //read folder source
   strcpy(outputFileFormat, argv[3]);
   printf("Root folder is %s\n", outputFileFormat);

   //append file name string format of image sequence
   strcat(outputFileFormat,"\\%04d.jpg");
   printf("File format string of image sequence: %s\n", outputFileFormat);
	
    outputImage.resize( width,height );  // set dimensions


    printf("Enter min of green hue to filter: ");
	scanf("%i", &min_green);
	printf("Enter max of green hue to filter: ");
	scanf("%i", &max_green);

	for (int frame = 0 ; frame < 2591; frame++) {
		sprintf(inputImageFile, image_seq, frame);
		readJpeg(inputImage, inputImageFile);
		
	 for (x = 0; x < width;  x++) {
     for (y = 0; y < height; y++) {
		 //read each pixel in input image
       pixColor = inputImage(x,y);
       // get the red, green, and blue components
       red = RED(pixColor);
       green = GREEN(pixColor);
       blue = BLUE(pixColor);
       // convert from RGB to HSI 
       RGBtoHSI( red, green, blue, hue, saturation, intensity );  // hus is in radians saturation is between 0..1
	   //get index in an array of degrees
		hue_index = (int)hue*180/3.14159; //convert hue angles from radians so check only colors between 0 to 360 degrees
		//if it is "Green" set to background image --> you may modify this to include checking of saturation values 
		if (hue_index >= min_green && hue_index <= max_green && intensity>0.3)
			outputImage(x,y) = backgroundImage(x,y);
		else
			outputImage(x,y) = pixColor;
       
     }
   }
   sprintf(outputImageFile, outputFileFormat, frame);
   writeJpeg(outputImage, outputImageFile, 85);

	}//go to next image in the folder
}




