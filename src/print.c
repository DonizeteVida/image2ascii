#include <stdio.h>
#include <stdlib.h>

#include "data.h"
#include "transform.h"

void toGrayHtml(char *filename, Image *image, char letter, int pixelSize, char* backgroundColor) {
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

	for (int r = 0; r < image->height; r++) {
		for (int c = 0; c < image->width; c++) {
			Pixel* pixel = image->pixels + r * image->width + c;
			int grayscale = 0.3 * pixel->r + 0.59 * pixel->g + 0.11 * pixel->b;
			fprintf(
				file,
				"<span style=\"color: rgb(%d, %d, %d)\">%c</span>",
				grayscale, grayscale, grayscale, letter
			);
		}
		fprintf(file, "<br/>");
	}
	fprintf(file, "</div>");
	fclose(file);
}

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

	for (int r = 0; r < image->height; r++) {
		for (int c = 0; c < image->width; c++) {
			Pixel* pixel = image->pixels + r * image->width + c;
			fprintf(
				file,
				"<span style=\"color: rgb(%d, %d, %d)\">%c</span>",
				pixel->r, pixel->g, pixel->b, letter
			);
		}
		fprintf(file, "<br/>");
	}

	fprintf(file, "</div>");
	fclose(file);
}

void toAscii(char* filename, Image* image) {
	FILE* file;

	if ((file = fopen(filename, "w")) == NULL) {
		fprintf(stderr, "can't open %s\n", filename);
		exit(0);
	}

	for (int r = 0; r < image->height; r++) {
		for (int c = 0; c < image->width; c++) {
			Pixel* pixel = image->pixels + r * image->width + c;

			float grayscale = (0.3 * pixel->r + 0.59 * pixel->g + 0.11 * pixel->b) / 255;

			unsigned char symbol;

			if (grayscale > .95) {
				symbol = '#';
			} else if (grayscale > .85) {
				symbol = '@';
			} else if (grayscale > .75) {
				symbol = '8';
			} else if (grayscale > .65) {
				symbol = '&';
			} else if (grayscale > .55) {
				symbol = 'C';
			} else if (grayscale > .45) {
				symbol = 'L';
			} else if (grayscale > .35) {
				symbol = '/';
			} else if (grayscale > .25) {
				symbol = '|';
			} else if (grayscale > .15) {
				symbol = '*';
			} else if (grayscale > .5) {
				symbol = '-';
			} else {
				symbol = ' ';
			}
			fprintf(file, "%c_", symbol);
		}
		fprintf(file, "\n");
	}

	fclose(file);
}
