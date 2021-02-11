/*
 * read.h
 *
 *  Created on: Feb 10, 2021
 *      Author: doni
 */

#ifndef READ_H_
#define READ_H_

struct Image* loadImage(char* name);
void printLetters(char *filename, struct Image *image, int whiteSensibility);

#endif /* READ_H_ */
