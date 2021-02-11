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
#include "print.h"

int main(int argc, char *args[]) {
	if (argc > 3) {
		struct Image *image = raw2Image(getRaw(args[1]));
		struct Image *resize = resizeImage(image, image->width / 2, image->height / 2);
		toAscii(args[2], resize, 255);
		toHtml(args[3], resize);
	} else {
		fprintf(stderr, "Missing argument...\n");
		fprintf(stderr, "./image2letter image.jpg result.txt result.html\n");
		exit(0);
	}

	return 0;
}
