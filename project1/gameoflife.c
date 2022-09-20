/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
//Note that you will need to read the eight neighbors of the cell in question. The grid "wraps", so we treat the top row as adjacent to the bottom row
//and the left column as adjacent to the right column.
Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule)
{
	//YOUR CODE HERE
	uint32_t dead_rule = rule & ((1 << 9) - 1);
	uint32_t active_rule = rule >> 9;
	uint32_t rows = image->rows, cols = image->cols;
	uint32_t active_count = 0, dead_count = 0;
	Color *color;
	int dx[4] = {-1, 0, 1, 0, -1, -1, 1, 1};
	int dy[4] = {0, -1, 0, 1, 1, -1, -1, 1};

	if((color = malloc(sizeof(Color)) == NULL))
		return (Color *)-1;

	for(int i = 0; i < 8; i++) {
		int a = (row + dx[i] + rows) % rows;
		int b = (col + dy[i] + cols) % cols;
		
		if(image->image[a * cols + b]->R)
			active_count++;
		else 
			dead_count++;
	}

	color->R = 0;
	color->G = 0;
	color->B = 0;

	if(image->image[row * cols + col]->R && active_rule >> active_count & 1) {
		color->R = 255;
		color->G = 255;
		color->B = 255;
	}

	return color;
}

//The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
//You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule)
{
	//YOUR CODE HERE
	Image *nextImage; 

	// malloc error check
	if((nextImage = malloc(sizeof(Image))) == NULL) 
		return (Image *)-1;
	if((nextImage->image = malloc(sizeof(Color *) * image->cols * image->rows)) == NULL)
		return (Image *)-1;

	for(int i = 0; i < image->rows; i++) {
		for(int j = 0; j < image->cols; j++) {
			Color *color = nextImage->image[i * image->cols + j];
			if((color = evaluateOneCell(image, i, j, rule)) == (Color *)-1)
				return (Image *)-1;
		}
	}
	
	return nextImage;
}

/*
Loads a .ppm from a file, computes the next iteration of the game of life, then prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this will be a string.
You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
	if(argc != 3) {
		printf("usage: ./gameOfLife filename rule\n\
    			filename is an ASCII PPM file (type P3) with maximum value 255.\n\
    			rule is a hex number beginning with 0x; Life is 0x1808.\n");
		exit(-1);
	}

	char *filename = argv[1];
	uint32_t rule = strtol(argv[2], NULL, 16);
	Image *image;
	Image *nextImage;

	if((image = readData(filename)) == (Image *)-1) {
		printf("readData from file error");
		exit(-1);
	}

	if((nextImage = life(image, rule)) == (Image *)-1) {
		printf("iteration of image error");
		exit(-1);
	}

	free(image);
	free(nextImage);

	return 0;
}
