#include "definition.h"
#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>
#include <string.h>

unsigned char* transformRow(unsigned char *row, int size, int components,
		int whiteSensibility) {
	int column = 0;
	int width = (size / components);
	unsigned char *newRow = malloc(
			(sizeof(unsigned char) * width) + 1);

	do {
		int color = 0;
		for (int i = 0; i < components; i++) {
			int pixel = row[column * components + i];
			color += pixel;
		}
		newRow[column++] = (color > whiteSensibility * 3) ? '_' : '@';
		printf("%.3d ", color);
	} while (column < width);
	newRow[column] = '\0';
	puts("");
	return newRow;
}

void printLetters(char *filename, struct Image *image, int whiteSensibility) {
	FILE *outtext;

	if ((outtext = fopen(filename, "w")) == NULL) {
		fprintf(stderr, "can't open %s\n", filename);
		exit(0);
	}

	for (int r = 0; r < image->height; r++) {
		unsigned char *row = transformRow(image->image[r],
				image->width * image->components, image->components,
				whiteSensibility);
		for(int c = 0; c < image->width; c++) {
			fprintf(outtext, "%c_", row[c]);
		}
		fprintf(outtext, "\n");
	}
}

struct Image* loadImage(char *filename) {
	struct Image *image = malloc(sizeof(struct Image));

	FILE *inputfile;

	if ((inputfile = fopen(filename, "r")) == NULL) {
		fprintf(stderr, "can't open %s\n", filename);
		exit(0);
	}

	struct jpeg_decompress_struct cinfo;

	struct jpeg_error_mgr jerr;

	cinfo.err = jpeg_std_error(&jerr);

	jpeg_create_decompress(&cinfo);
	jpeg_stdio_src(&cinfo, inputfile);

	(void) jpeg_read_header(&cinfo, TRUE);
	(void) jpeg_start_decompress(&cinfo);

	int row_stride = cinfo.output_width * cinfo.output_components;

	JSAMPARRAY buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr) &cinfo,
	JPOOL_IMAGE, row_stride, 1);

	image->image = malloc(sizeof(unsigned char*) * cinfo.output_height);

	while (cinfo.output_scanline < cinfo.output_height) {
		(void) jpeg_read_scanlines(&cinfo, buffer, 1);
		unsigned char *line = malloc(sizeof(unsigned char) * row_stride);
		unsigned char *buff = buffer[0];

		for(int i = 0; i < row_stride; i++){
			line[i] = buff[i];
		}

		image->image[cinfo.output_scanline - 1] = line;
	}

	image->height = cinfo.output_height;
	image->width = cinfo.output_width;
	image->components = cinfo.output_components;

	(void) jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	fclose(inputfile);

	return image;
}
