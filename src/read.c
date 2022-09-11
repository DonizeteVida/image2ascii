#include <stdio.h>
#include <stdlib.h>

#include <jpeglib.h>

#include "data.h"
#include "read.h"

Raw* getRaw(char *filename) {

	FILE *file;

	if ((file = fopen(filename, "r")) == NULL) {
		fprintf(stderr, "can't open %s\n", filename);
		exit(0);
	}

	Raw *raw = malloc(sizeof(Raw));

	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;

	cinfo.err = jpeg_std_error(&jerr);

	jpeg_create_decompress(&cinfo);
	jpeg_stdio_src(&cinfo, file);

	(void) jpeg_read_header(&cinfo, TRUE);
	(void) jpeg_start_decompress(&cinfo);

	const int spread_row = cinfo.output_width * cinfo.output_components;

	JSAMPARRAY buffer = cinfo.mem->alloc_sarray(
		(j_common_ptr) &cinfo, 
		JPOOL_IMAGE, 
		spread_row, 
		1
	);

	raw->data = malloc(cinfo.output_width * cinfo.output_height * cinfo.output_components * sizeof(unsigned char));

	while (cinfo.output_scanline < cinfo.output_height) {
		(void) jpeg_read_scanlines(&cinfo, buffer, /*max_lines*/ 1);

		const int index = cinfo.output_scanline * spread_row;

		for (int i = 0; i < spread_row; i++) {
			raw->data[index + i] = buffer[0][i];
		}
	}

	raw->height = cinfo.output_height;
	raw->width = cinfo.output_width;
	raw->components = cinfo.output_components;

	(void) jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	fclose(file);

	return raw;
}

Image* raw2Image(Raw *raw) {
	Image *image = malloc(sizeof(Image));

	image->height = raw->height;
	image->width = raw->width;

	const int size = raw->width * raw->height;
	const int components = raw->components;

	image->pixels = malloc(sizeof(Pixel) * size);

	for (int i = 0; i < size; i++) {
		Pixel* pixel = image->pixels + i;

		int index = i * components;

		pixel->r = raw->data[index];
		pixel->g = raw->data[index + 1];
		pixel->b = raw->data[index + 2];
	}

	free(raw->data);
	free(raw);

	return image;
}