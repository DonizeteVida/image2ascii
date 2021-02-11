/*
 * definition.h
 *
 *  Created on: Feb 10, 2021
 *      Author: doni
 */

#ifndef DEFINITION_H_
#define DEFINITION_H_

struct Image {
	int width;
	int height;
	int components;
	unsigned char **image;
};

#endif /* DEFINITION_H_ */
