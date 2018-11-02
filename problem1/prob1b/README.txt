EE569 Homework Assignment Prob1a
Date: March 4, 2018
Name : Akshata Bhat
USC ID : 9560895350
Email : akshatab@usc.edu
-----------------------------------------------------------------------------------------------------------------------------------------------------------------
SYSTEM CONFIGURATION IN WHICH THIS CODE RAN:

OS: Linux Ubuntu 64-bit 16.04

Software: Terminal
-----------------------------------------------------------------------------------------------------------------------------------------------------------------
STEPS TO DEBUG CODE:


1. Open Terminal

2. Run this command in the project folder:
    g++ -o hw2_prob1b.exe hw2_prob1b.cpp
3. You should see the program executable named : hw2_prob1b.exe

4.The executable should be run with these arguments:
program_name = ./hw2_prob1b.exe 

<program_name>  hw2_prob1b <left.raw> <middle.raw> <right.raw> <width> <height> <bytes_per_pixel>

where,
program_name: 	 				name of the .exe file generated
<left.raw>, <middle.raw>, <right.raw>: 		names of the .raw input files along with path to be taken as input for the image stitching
width: 						width of the image
image_height: 					height of the image
bytes_per_pixel: 				bytes per pixel (for RGB = 3 and for GRAY = 1)
-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Example : ./prob1b.exe left.raw middle.raw right.raw 480 640 3
