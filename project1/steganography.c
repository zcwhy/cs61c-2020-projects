/************************************************************************
**
** NAME:        steganography.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**				Justin Yokota - Starter Code
**				YOUR NAME HERE
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This should not affect Image, and should allocate space for a new Color.
Color *evaluateOnePixel(Image *image, int row, int col)
{
	//YOUR CODE HERE
	Color *secert = malloc(sizeof(Color));

	if(secert == NULL) 
		return NULL;

	Color *color = image->image[row * image->cols + col];
	uint8_t B = color->B;

	if(B & 1) {
		secert->R = 255;
		secert->G = 255;
		secert->B = 255;
	} else {
		// printf("row = %d, col = %d, B = %d\n", row, col, B);
		secert->R = 0;
		secert->G = 0;
		secert->B = 0;
	}
	return secert;
}

//Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image)
{
	//YOUR CODE HERE
	int rows = image->rows;
	int cols = image->cols;
	Image *secert = malloc(sizeof(Image));
	secert->image = malloc(sizeof(Color *) * rows * cols);

	secert->rows = image->rows;
	secert->cols = image->cols;
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			secert->image[i * cols + j] = evaluateOnePixel(image, i, j);
			if(secert->image[i * cols + j] == NULL)
				return (Image *)-1;
		}
	}
	return secert;
}	

/*
Loads a file of ppm P3 format from a file, and prints to stdout (e.g. with printf) a new image, 
where each pixel is black if the LSB of the B channel is 0, 
and white if the LSB of the B channel is 1.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a file of ppm P3 format (not necessarily with .ppm file extension).
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!
*/
int main(int argc, char **argv)
{
	
	//YOUR CODE HERE
	if(argc != 2) {
		printf("need a file name\n");
		exit(-1);
	}
	

	char *filename = argv[1];
	Image *image, *secretimage;

	image = readData(filename);
	secretimage = steganography(image);

	if(secretimage == (void *)-1 && image == (void *)-1) {
		free(image);
		free(secretimage);
		exit(-1);
	}

	writeData(secretimage);

	free(image);
	free(secretimage);
	return 0;
}
