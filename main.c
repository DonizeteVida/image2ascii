#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

#include "src/data.h"
#include "src/read.h"
#include "src/print.h"
#include "src/transform.h"

int main(int argc, char *args[]) {
    char* filename = "./example/ring.jpg";
    Image* image = scaleImage(raw2Image(getRaw(filename)), .5);
    toHtml("./ring.html", image, '@', 2, "black");
    toGrayHtml("./ring_gray.html", image, '@', 2, "black");
    toAscii("./ring.txt", image);
    free(image->pixels);
    free(image);
}