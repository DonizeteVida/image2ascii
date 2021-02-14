/*
 * transform.h
 *
 *  Created on: Feb 13, 2021
 *      Author: doni
 */

#include "data/definition.h"

#ifndef TRANSFORM_H_
#define TRANSFORM_H_

struct Image* scaleImage(struct Image *image, float scale);
struct Image* resizeImage(struct Image *image, int width, int height);

#endif /* TRANSFORM_H_ */
