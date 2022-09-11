/*
 * print.c
 *
 *  Created on: Feb 11, 2021
 *      Author: doni
 */

#include <stdio.h>
#include <stdlib.h>

#include "data.h"
#include "transform.h"

void toHtml(char *filename, Image *image, char letter, int pixelSize, char* backgroundColor) {
	FILE *file;

	if ((file = fopen(filename, "w")) == NULL) {
		fprintf(stderr, "can't open %s\n", filename);
		exit(0);
	}

	fprintf(file, "<style> ");
	fprintf(file, "span { font-size: %dpx; width: %dpx; height: %dpx; align: center; display: inline-block; } ", pixelSize, pixelSize, pixelSize);
	fprintf(file, "body, html { background-color: %s; width: 100%%; height: 100%%; padding: 0; margin: 0; } ", backgroundColor);
	fprintf(file, "</style> ");
	fprintf(file, "<div style=\"align: center; overflow-x: scroll; width: 100%%; height: 100%%; \">");
	
	for (int i = 0; i < image->width * image->height; i++) {
		Pixel* pixel = image->pixels + i;
		fprintf(
			file,
			"<span style=\"color: rgb(%d, %d, %d)\">%c</span>",
			pixel->r, pixel->g, pixel->b, letter
		);
		if ((i + 1) % image->width == 0) {
			fprintf(file, "<br/>");
		}
	}
	fprintf(file, "</div>");
	fclose(file);
}

void toAscii(char* filename, Image* image, int whiteFactor) {
	FILE* file;

	if ((file = fopen(filename, "w")) == NULL) {
		fprintf(stderr, "can't open %s\n", filename);
		exit(0);
	}

	for (int i = 0; i < image->width * image->height; i++) {
		Pixel* pixel = image->pixels + i;

		int color = pixel->r + pixel->g + pixel->b;

		unsigned char symbol;
		int totalWhite = (whiteFactor * 3);

		if (color > .95 * totalWhite) {
			symbol = ' ';
		} else if (color > .85 * totalWhite) {
			symbol = '-';
		} else if (color > .75 * totalWhite) {
			symbol = '*';
		} else if (color > .65 * totalWhite) {
			symbol = '|';
		} else if (color > .55 * totalWhite) {
			symbol = '/';
		} else if (color > .45 * totalWhite) {
			symbol = 'L';
		} else if (color > .35 * totalWhite) {
			symbol = 'C';
		} else if (color > .25 * totalWhite) {
			symbol = '&';
		} else if (color > .15 * totalWhite) {
			symbol = '8';
		} else if (color > .5 * totalWhite) {
			symbol = '@';
		} else {
			symbol = '#';
		}
		fprintf(file, "%c_", symbol);

		if ((i + 1) % image->width == 0) {
			fprintf(file, "\n");
		}
	}

	fclose(file);
}
