/*
 * print.h
 *
 *  Created on: Feb 11, 2021
 *      Author: doni
 */

#ifndef PRINT_H_
#define PRINT_H_

void toAscii(char *filename, struct Image *image, int whiteFactor);
void toHtml(char *filename, struct Image *image, char letter, int pixelSize, char* color);
void toTerminal(struct Image *image);
void toColoredTerminal(struct Image *image);

#endif /* PRINT_H_ */
