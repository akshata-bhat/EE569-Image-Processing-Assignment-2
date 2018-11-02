EE569 Homework Assignment Prob3 abcd_part A
Date: March 4, 2018
Name : Akshata Bhat
USC ID : 9560895350
Email : akshatab@usc.edu

This program performs the shrinking of the input stars.raw image to count the number of stars, thinning and skeletonizing morphological operations and counts the total number of jigsaw puzzles.
-----------------------------------------------------------------------------------------------------------------------------------------------------------------
SYSTEM CONFIGURATION IN WHICH THIS CODE RAN:

OS: Linux Ubuntu 64-bit 16.04

Software: Terminal
-----------------------------------------------------------------------------------------------------------------------------------------------------------------
STEPS TO DEBUG CODE:


1. Open Terminal

2. Run this command in the project folder:
    g++ -o hw2_prob3abcd.exe hw2_prob3abcd.cpp
3. You should see the program executable named : hw2_prob3abcd.exe

4.The executable should be run with these arguments:
program_name = ./hw2_prob3abcd.exe 

<program_name> <input_shrink.raw> <width1> <height1> <input_thin.raw> <width2> <height2> <input_skeletonize.raw> <width3> <height3> <input_counting_game.raw> <width4> <height4>

where,
program_name: 	 		name of the .exe file generated
<input_shrink.raw>		input file to perform shrinking and count the stars
<width1>, <height1>		width and height of the image to be shrinked
<input_thin.raw> 		input file to perform thinning
<width2>, <height2>		 width and height of the image to be thinned
<input_skeletonize.raw> 	input file to perform skeletonizing
<width3>, <height3> 		width and height of the image to be skeletonized
<input_counting_game.raw> 	input file to perform the counting of total number of jigsaw puzzles
<width4>, <height4>		width and height of the corresponding image
-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Example : ./hw2_prob3abcd.exe stars.raw 640 480 jigsaw_1.raw 100 100 jigsaw_2.raw 100 100 board.raw 372 372
