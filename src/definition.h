/*
 * definition.h
 *
 *  Created on: Feb 10, 2021
 *      Author: doni
 */

#ifndef DEFINITION_H_
#define DEFINITION_H_

//width will be horizontal size of image * components;
//180 * 180 image becomes (180 * 3) * 180, as an example
struct Raw {
	int width;
	int height;
	int components;
	unsigned char **data;
};

//Image is a better representation for manipulation approaches
struct Image {
	int width;
	int height;
	struct Pixel **pixels;
};

struct Pixel {
	int r;
	int g;
	int b;
};

#endif /* DEFINITION_H_ */
