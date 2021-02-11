/*
 ============================================================================
 Name        : image2letter.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>
#include "definition.h"
#include "read.h"

int main(void) {
	struct Image *image = loadImage("./image.jpg");
	printLetters("./result.txt", image, 255);
}
