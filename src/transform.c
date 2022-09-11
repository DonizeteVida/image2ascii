/*
 * transform.c
 *
 *  Created on: Feb 13, 2021
 *      Author: doni
 */
#include <stdlib.h>

#include "data.h"
#include "transform.h"

Image* scaleImage(Image *image, float scale) {
	return resizeImage(image, (float) image->width * scale, (float) image->height * scale);
}

Image* resizeImage(Image *from, int width, int height) {
	Image *to = malloc(sizeof( Image));
	// to->width = width;
	// to->height = height;
	// to->pixels = malloc(sizeof( Pixel*) * height);

	// for (int r = 0; r < height; r++) {
	// 	float verticalPercentage = (r + 1) / (float) height;

	// 	to->pixels[r] = malloc(sizeof( Pixel) * width);

	// 	for (int c = 0; c < width; c++) {
	// 		float horizontalPercentage = (c + 1) / (float) width;

	// 		int fromVerticalCoordinate = verticalPercentage * (from->height - 1);
	// 		int fromHorizontalCoordinate = horizontalPercentage * (from->width - 1);

	// 		Pixel* fromPixel = &from->pixels[fromVerticalCoordinate][fromHorizontalCoordinate];
	// 		Pixel* toPixel = &to->pixels[r][c];

	// 		toPixel->r = fromPixel->r;
	// 		toPixel->g = fromPixel->g;
	// 		toPixel->b = fromPixel->b;
	// 	}
	// }

	return to;
}
