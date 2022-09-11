#ifndef DATA_H_
#define DATA_H_

//data size is width * height * components (aka pixels, or whatever)
typedef struct {
	unsigned int width;
	unsigned int height;
	unsigned int components;
	unsigned char* data;
} Raw;

typedef struct {
	unsigned char r;
	unsigned char g;
	unsigned char b;
} Pixel;

//pixels size are width * height
typedef struct {
	unsigned int width;
	unsigned int height;
	Pixel* pixels;
} Image;

#endif
