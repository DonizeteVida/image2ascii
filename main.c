#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

#include "src/data.h"
#include "src/read.h"
#include "src/print.h"
#include "src/transform.h"

int main(int argc, char *args[]) {
    char* filename = "./demo/afro.jpg";
    Image* image = scaleImage(raw2Image(getRaw(filename)), .3);
    toHtml("demo/afro.html", image, '@', 1, "black");
    toGrayHtml("demo/afro_gray.html", image, '@', 1, "black");
    toAscii("demo/afro.txt", image);
    free(image->pixels);
    free(image);
}