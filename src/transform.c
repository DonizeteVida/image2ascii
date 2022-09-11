#include <stdlib.h>
#include <stdio.h>

#include "data.h"
#include "transform.h"

Image* scaleImage(Image* from, float scale) {
	return resizeImage(from, from->width * scale, from->height * scale);
}

Image* resizeImage(Image* from, int width, int height) {
	Image *to = malloc(sizeof(Image));

	to->width = width;
	to->height = height;

	to->pixels = malloc(sizeof(Pixel) * width * height);

	for (int r = 0; r < height; r++) {
		for (int c = 0; c < width; c++) {
			float rp = r / (float) height;
			float cp = c / (float) width;

			int row = rp * from->height;
			int column = cp * from->width;

			Pixel* new = to->pixels + r * width + c;
			Pixel* old = from->pixels + row * from->width + column;

			new->r = old->r;
			new->g = old->g;
			new->b = old->b;
		}
	}

	free(from->pixels);
	free(from);

	return to;
}
