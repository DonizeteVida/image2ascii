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

int main(int argc, char *args[]) {
	if (argc > 2) {
		struct Image *image = loadImage(args[1]);
		printLetters(args[2], image, 255);
	} else {
		fprintf(stderr, "Missing argument...\n");
		fprintf(stderr, "./image2letter image.jpg result.txt\n");
		exit(0);
	}

	return 0;
}
