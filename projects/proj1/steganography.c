/************************************************************************
**
** NAME:        steganography.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**				Justin Yokota - Starter Code
**				LCJD 
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
	Color *color = (Color *)malloc(sizeof(Color));
	Color *c = &image->image[row][col];
	uint8_t val = c->B & 1 ? 255 : 0;
	color->R = val;
	color->G = val;
	color->B = val;
	return color;
}

//Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image)
{
	Image *newImg= (Image*)malloc(sizeof(Image));
	newImg->cols = image->cols;
	newImg->rows = image->rows;
	newImg->image = (Color**)malloc(image->rows * sizeof(Color*));
	Color **rawColors = image->image;
	Color **newColors = newImg->image;
	int h = newImg->rows;
	int w = newImg->cols;
	for (int i = 0 ; i < h; i++) {
		newColors[i] = (Color*)malloc(w * sizeof(Color));
	}
	for (int i = 0 ; i < h; i++) {
		for (int j = 0 ; j < w; j++) {
			Color *c = evaluateOnePixel(image, i, j);
			newColors[i][j].R = c->R;
			newColors[i][j].G = c->G;
			newColors[i][j].B = c->B;
			free(c);
		}
	}
	return newImg;
}

void processCLI(int argc, char **argv, char **filename) 
{
	if (argc != 2) {
		printf("usage: %s filename\n",argv[0]);
		printf("filename is an ASCII PPM file (type P3) with maximum value 255.\n");
		exit(-1);
	}
	*filename = argv[1];
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
	char *filename;
	processCLI(argc, argv, &filename);
	Image *img = readData(filename);
	Image *newImg = steganography(img);
	writeData(newImg);
	freeImage(img);
	freeImage(newImg);
}
