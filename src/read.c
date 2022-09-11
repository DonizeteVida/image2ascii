#include <stdio.h>
#include <stdlib.h>

#include "data/definition.h"
#include "read.h"

#include <jpeglib.h>

Image* raw2Image(Raw *raw) {
	Image *image = malloc(sizeof(Image));
	image->height = raw->height;
	image->width = raw->width;

	image->pixels = malloc(sizeof(Pixel*) * image->height);

	for (int r = 0; r < raw->height; r++) {
		unsigned char *row = raw->data[r];

		Pixel *horizontalPixels = malloc(sizeof(Pixel) * raw->width);

		int index = 0;

		do {
			Pixel *pixel = horizontalPixels + index;
			int resolvedIndex = index * raw->components;
			pixel->r = row[resolvedIndex + 0];
			pixel->g = row[resolvedIndex + 1];
			pixel->b = row[resolvedIndex + 2];
		} while (++index < raw->width);
		free(row);
		image->pixels[r] = horizontalPixels;
	}
	free(raw->data);
	free(raw);

	return image;
}

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

	int row_stride = cinfo.output_width * cinfo.output_components;

	JSAMPARRAY buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr) & cinfo,
			JPOOL_IMAGE, row_stride, 1);

	raw->data = malloc(sizeof(unsigned char*) * cinfo.output_height);

	while (cinfo.output_scanline < cinfo.output_height) {
		(void) jpeg_read_scanlines(&cinfo, buffer, /*max_lines*/ 1);
		unsigned char* line = malloc(sizeof(unsigned char) * row_stride);
		unsigned char* buff = buffer[0];

		for (int i = 0; i < row_stride; i++) {
			line[i] = buff[i];
		}

		raw->data[cinfo.output_scanline - 1] = line;
	}

	raw->height = cinfo.output_height;
	raw->width = cinfo.output_width;
	raw->components = cinfo.output_components;

	(void) jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	fclose(file);

	return raw;
}
