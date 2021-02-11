/*
 * print.c
 *
 *  Created on: Feb 11, 2021
 *      Author: doni
 */

#include "definition.h"
#include <stdio.h>
#include <stdlib.h>

void toHtml(char *filename, struct Image *image) {
	FILE *outtext;

	if ((outtext = fopen(filename, "w")) == NULL) {
		fprintf(stderr, "can't open %s\n", filename);
		exit(0);
	}

	fprintf(outtext, "<style> span { font-size: 1px; width: 1px; height: 1px; align: center; display: inline-block; } </style>");

	for (int r = 0; r < image->height; r++) {

		struct Pixel *row = image->pixels[r];

		for (int c = 0; c < image->width; c++) {

			struct Pixel pixel = row[c];

			fprintf(outtext,
					"<span style=\"color: rgb(%d, %d, %d)\">%c</span>",
					pixel.r, pixel.g, pixel.b, '@');
			printf("%d, %d, %d - ", pixel.r, pixel.g, pixel.b);
		}
		fprintf(outtext, "<br/>");
		puts("");
	}
}

void toAscii(char *filename, struct Image *image, int whiteFactor) {
	FILE *outtext;

	if ((outtext = fopen(filename, "w")) == NULL) {
		fprintf(stderr, "can't open %s\n", filename);
		exit(0);
	}

	for (int r = 0; r < image->height; r++) {

		struct Pixel *row = image->pixels[r];

		for (int c = 0; c < image->width; c++) {

			struct Pixel column = row[c];

			int color = column.r + column.g + column.b;

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
			fprintf(outtext, "%c_", symbol);
		}
		fprintf(outtext, "\n");
	}
}
