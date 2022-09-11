#ifndef DATA_H_
#define DATA_H_

//data size is width * height
typedef struct {
	int width;
	int height;
	int components;
	unsigned char* data;
} Raw;

typedef struct {
	unsigned char r;
	unsigned char g;
	unsigned char b;
} Pixel;

//pixels size are width * height
typedef struct {
	int width;
	int height;
	Pixel* pixels;
} Image;

#endif
