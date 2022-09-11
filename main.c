#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

#include "src/data.h"
#include "src/read.h"
#include "src/print.h"
#include "src/transform.h"

int main(int argc, char *args[]) {
    char* filename = "./example/colored.jpg";
    Image* image = scaleImage(raw2Image(getRaw(filename)), 2);
    toHtml("example/colored.html", image, '@', 2, "black");
    toGrayHtml("example/colored_gray.html", image, '@', 2, "black");
    toAscii("example/colored.txt", image);
    free(image->pixels);
    free(image);
}