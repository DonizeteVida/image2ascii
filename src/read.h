/*
 * read.h
 *
 *  Created on: Feb 10, 2021
 *      Author: doni
 */

#ifndef READ_H_
#define READ_H_

struct Raw* getRaw(char *filename);
struct Image* raw2Image(struct Raw *raw);
struct Image* resizeImage(struct Image* image, int width, int height);

#endif /* READ_H_ */
