/*
 * definition.h
 *
 *  Created on: Feb 10, 2021
 *      Author: doni
 */

#ifndef DEFINITION_H_
#define DEFINITION_H_

typedef unsigned char byte;

//data size is width * height
typedef struct {
	int width;
	int height;
	int components;
	byte** data;
} Raw;

typedef struct {
	byte r;
	byte g;
	byte b;
} Pixel;

typedef struct {
	int width;
	int height;
	Pixel** pixels;
} Image;

#endif /* DEFINITION_H_ */
