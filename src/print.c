/*
 * print.c
 *
 *  Created on: Feb 11, 2021
 *      Author: doni
 */

#include <stdio.h>
#include <stdlib.h>

#include "data/definition.h"
#include "platform/terminal.h"
#include "transform.h"

void toTerminal(Image *image) {
	struct TerminalInfo terminalInfo;
	getTerminalInfo(&terminalInfo);

	// we print 2 char per print, this why we divide per 2
	float factor = terminalInfo.width / (float) image->width / 2;
	Image *newImage = scaleImage(image, factor);

	for (int r = 0; r < newImage->height; r++) {

		Pixel *row = newImage->pixels[r];

		for (int c = 0; c < newImage->width; c++) {

			Pixel *pixel = &row[c];

			int color = pixel->r + pixel->g + pixel->b;

			unsigned char symbol;
			int totalWhite = (255 * 3);

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
			printf("%c_", symbol);
		}
		puts("");
	}
}

void toColoredTerminal(Image *image) {

}

void toHtml(char *filename, Image *image, char letter, int pixelSize, char* color) {
	FILE *outtext;

	if ((outtext = fopen(filename, "w")) == NULL) {
		fprintf(stderr, "can't open %s\n", filename);
		exit(0);
	}

	fprintf(outtext, "<style> ");
	fprintf(outtext, "span { font-size: %dpx; width: %dpx; height: %dpx; align: center; display: inline-block; } ", pixelSize, pixelSize, pixelSize);
	fprintf(outtext, "body, html { background-color: %s; width: 100%%; height: 100%%; padding: 0; margin: 0; } ", color);
	fprintf(outtext, "</style> ");
	fprintf(outtext, "<div style=\"align: center; overflow-x: scroll; width: 100%%; height: 100%%; \">");
	for (int r = 0; r < image->height; r++) {

		Pixel *row = image->pixels[r];

		for (int c = 0; c < image->width; c++) {

			Pixel* pixel = &row[c];
			{
				fprintf(
					outtext,
					"<span style=\"color: rgb(%d, %d, %d)\">%c</span>",
					pixel->r, pixel->g, pixel->b, letter
				);
			}
		}
		fprintf(outtext, "<br/>");
		puts("");
	}
	fprintf(outtext, "</div>");
}

void toAscii(char* filename, Image* image, int whiteFactor) {
	FILE* file;

	if ((file = fopen(filename, "w")) == NULL) {
		fprintf(stderr, "can't open %s\n", filename);
		exit(0);
	}

	for (int r = 0; r < image->height; r++) {

		Pixel *row = image->pixels[r];

		for (int c = 0; c < image->width; c++) {

			Pixel* pixel = row + c;

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
		}
		fprintf(file, "\n");
	}

	fclose(file);
}
