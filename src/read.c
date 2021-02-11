#include "definition.h"
#include "read.h"

#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>

struct Image* resizeImage(struct Image *from, int width, int height) {
	struct Image *to = malloc(sizeof(struct Image));
	to->width = width;
	to->height = height;
	to->pixels = malloc(sizeof(struct Pixel*) * height);

	for (int r = 0; r < height; r++) {
		float vFactor = (r + 1) / (float) height;
		to->pixels[r] = malloc(sizeof(struct Pixel) * width);

		for (int c = 0; c < width; c++) {
			float hFactor = (c + 1) / (float) width;
			int fromV = vFactor * (from->height - 1);
			int fromH = hFactor * (from->width - 1);
			struct Pixel p = from->pixels[fromV][fromH];

			to->pixels[r][c].r = p.r;
			to->pixels[r][c].g = p.g;
			to->pixels[r][c].b = p.b;
		}
	}

	return to;
}

struct Image* raw2Image(struct Raw *raw) {
	struct Image *image = malloc(sizeof(struct Image));
	image->height = raw->height;
	image->width = raw->width;

	image->pixels = malloc(sizeof(struct Pixel*) * image->height);

	for (int r = 0; r < raw->height; r++) {
		unsigned char *row = raw->data[r];
		struct Pixel *nRow = malloc(sizeof(struct Pixel) * raw->width);

		int index = 0;

		do {
			nRow[index].r = row[index * raw->components + 0];
			nRow[index].g = row[index * raw->components + 1];
			nRow[index].b = row[index * raw->components + 2];
		} while (++index < raw->width);
		free(row);
		image->pixels[r] = nRow;
	}
	free(raw->data);
	free(raw);

	return image;
}

struct Raw* getRaw(char *filename) {

	FILE *inputfile;

	if ((inputfile = fopen(filename, "r")) == NULL) {
		fprintf(stderr, "can't open %s\n", filename);
		exit(0);
	}

	struct Raw *raw = malloc(sizeof(struct Raw));

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

	raw->data = malloc(sizeof(unsigned char*) * cinfo.output_height);

	while (cinfo.output_scanline < cinfo.output_height) {
		(void) jpeg_read_scanlines(&cinfo, buffer, 1);
		unsigned char *line = malloc(sizeof(unsigned char) * row_stride);
		unsigned char *buff = buffer[0];

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
	fclose(inputfile);

	return raw;
}
