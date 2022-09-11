#ifndef PRINT_H_
#define PRINT_H_

void toAscii(char *filename, Image *image);
void toHtml(char *filename, Image *image, char letter, int pixelSize, char* color);
void toGrayHtml(char *filename, Image *image, char letter, int pixelSize, char* color);

#endif
