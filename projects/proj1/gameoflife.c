/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				LCJD
**
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

// range [low, up)
int isInRange(int low, int up, int x) {
	return low <= x && x < up;
}

int isLiveInRule(int state, int neighbor, uint32_t rule) {
	rule = rule >> ((state&1) * 9);
	int ans = (rule >> neighbor) & 1; 
	return ans;
}

//Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
//Note that you will need to read the eight neighbors of the cell in question. The grid "wraps", so we treat the top row as adjacent to the bottom row
//and the left column as adjacent to the right column.
Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule)
{
	Color **c = image->image;
	int cntR = 0;
	int cntG = 0;
	int cntB = 0;
	int rs[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
	int cs[8] = {-1, 0, 1, -1, 1, -1, 0 ,1};
	for(int i = 0; i < 8; i++) {
		if (isInRange(0, image->rows, row + rs[i]) && isInRange(0, image->cols, col + cs[i])) {
			if (c[row + rs[i]][col + cs[i]].R) {
				cntR++;
			}
			if (c[row + rs[i]][col + cs[i]].G) {
				cntG++;
			}
			if (c[row + rs[i]][col + cs[i]].B) {
				cntB++;
			}
		}
	}

	Color *color = (Color *)malloc(sizeof(Color));
	color->R = isLiveInRule(c[row][col].R, cntR, rule) * 255;
	color->G = isLiveInRule(c[row][col].G, cntG, rule) * 255;
	color->B = isLiveInRule(c[row][col].B, cntB, rule) * 255;
	return color;
}

//The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
//You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule)
{
	Image *newImg = (Image *)malloc(sizeof(Image));
	newImg->cols = image->cols;
	newImg->rows = image->rows;
	newImg->image = (Color **)malloc(image->rows * sizeof(Color *));
	Color **rawColors = image->image;
	Color **newColors = newImg->image;
	int h = newImg->rows;
	int w = newImg->cols;
	for (int i = 0; i < h; i++)
	{
		newColors[i] = (Color *)malloc(w * sizeof(Color));
	}
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			Color *c = evaluateOneCell(image, i, j, rule);
			newColors[i][j].R = c->R;
			newColors[i][j].G = c->G;
			newColors[i][j].B = c->B;
			free(c);
		}
	}
	return newImg;
}


void processCLI(int argc, char **argv, char **filename, uint32_t *rule) 
{
	if (argc != 3) {
		printf("usage: %s filename rule\n",argv[0]);
		printf("filename is an ASCII PPM file (type P3) with maximum value 255.\n");
		printf("rule is a hex number beginning with 0x; Life is 0x1808.\n");
		exit(-1);
	}
	*filename = argv[1];
	sscanf(argv[2], "0x%x", rule);
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
	char *filename;
	uint32_t rule;
	processCLI(argc, argv, &filename, &rule);
	Image *img = readData(filename);
	Image *newImg = life(img, rule);
	writeData(newImg);
	freeImage(img);
	freeImage(newImg);
}
