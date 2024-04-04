/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**							LCJD
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
	FILE *f = fopen(filename, "r");
	char type[20];
	int w, h, range;
	fscanf(f, "%s\n%d %d\n%d", type, &w, &h, &range);
	Image *image = (Image*)malloc(sizeof(Image));
	image->cols = w;
	image->rows = h;
	image->image = (Color**)malloc(h * sizeof(Color*));
	Color **colors = image->image;
	for (int i = 0 ; i < h; i++) {
		colors[i] = (Color*)malloc(w * sizeof(Color));
	}
	int r, g, b;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			fscanf(f, "%d %d %d", &r, &g, &b);
			colors[i][j].R = (uint8_t)r;
			colors[i][j].G = (uint8_t)g;
			colors[i][j].B = (uint8_t)b;
		}
	}
	fclose(f);
	return image;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	printf("P3\n");
	printf("%d %d\n", image->cols, image->rows);
	printf("255\n");
	Color **colors = image->image;
	int h = image->rows;
	int w = image->cols;
	Color *c;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			c = &colors[i][j];
			printf("%3d %3d %3d", c->R, c->G, c->B);
			if (j != w - 1) {
				printf("   ");
			} else {
				printf("\n");
			}
		}
	}
	
}

//Frees an image
void freeImage(Image *image)
{
	for (int i = 0 ; i < image->rows; i++) {
		free((image->image)[i]);
	}
	free(image->image);
	free(image);
}