#include <stdlib.h>

#include "data.h"
#include "transform.h"

Image* scaleImage(Image *from, float scale) {
	return resizeImage(from, from->width * scale, from->height * scale);
}

Image* resizeImage(Image *from, int width, int height) {
	Image *to = malloc(sizeof(Image));

	to->width = width;
	to->height = height;

	to->pixels = malloc(sizeof(Pixel) * width * height);

	for (int r = 0; r < height; r++) {
		for (int w = 0; w < width; w++) {
			float pr = (r + 1) / (float) height;
			float pw = (w + 1) / (float) width;
			Pixel* new = to->pixels + r * width + w;
			Pixel* old = from->pixels + (int) ((pr * from->width) + (pw * from->width));
			new->r = old->r;
			new->g = old->g;
			new->b = old->b;
		}
	}

	free(from->pixels);
	free(from);

	return to;
}
