EE569 Homework Assignment Prob2b
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
    g++ -o hw2_prob2b.exe hw2_prob2b.cpp
3. You should see the program executable named : hw2_prob2b.exe

4.The executable should be run with these arguments:
program_name = ./hw2_prob2b.exe 

hw2_prob2b <input_image.raw> <width> <height> <bytes_per_pixel>

where,
program_name: 	 				name of the .exe file generated
<input.raw>: 					name of the .raw input along with path to be taken as input for processing
width: 						width of the image
image_height: 					height of the image
bytes_per_pixel: 				bytes per pixel (for RGB = 3 and for GRAY = 1)
-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Example : ./hw2_prob2b.exe colorchecker.raw 512 512 1
