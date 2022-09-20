/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename) 
{
	int rows, cols, R, G, B, i;
	Image *image = (Image *)malloc(sizeof(Image));
	FILE *file = fopen(filename, "r");
	
	if(file == NULL) {
		printf("open file error\n");
		return (Image *)-1;
	}

	fscanf(file, "%*s %d %d %*d", &cols, &rows);
	// printf("success scanf = %d\n", error);
	// printf("rows = %d, cols = %d\n", rows, cols);
	image->image = malloc(sizeof(Color *) * rows * cols);
	image->rows = rows;
	image->cols = cols;

	for(i = 0; i < rows * cols; i++) {
		if(fscanf(file, "%d %d %d", &R, &G, &B) == EOF) 
			return (Image *)-1;
		image->image[i] = malloc(sizeof(Color));
		image->image[i]->R = R;
		image->image[i]->G = G;
		image->image[i]->B = B;
	}
	fclose(file);
	return image;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	//YOUR CODE HERE
	printf("P3\n");
	printf("%d %d\n", image->cols, image->rows);
	printf("255\n");

	for(int i = 0; i < image->rows; i++) {
		for(int j = 0; j < image->cols; j++) {
			Color *color = image->image[i * image->cols + j];
			if(j < image->cols - 1) 
				printf("%3d %3d %3d   ", color->R, color->G,color->B);
			else 
				printf("%3d %3d %3d", color->R, color->G,color->B);
			
		}
		printf("\n");
	}
}

//Frees an image
void freeImage(Image *image)
{
	//YOUR CODE HERE
	for(int i = 0; i < image->rows; i++) {
		for(int j = 0; j < image->cols; j++) {
			Color *color = image->image[i * image->cols + j];
			free(color);
		}
	}
	free(image->image);
	free(image);
}