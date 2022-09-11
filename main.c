#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

#include "src/data.h"
#include "src/read.h"
#include "src/print.h"
#include "src/transform.h"

int main(int argc, char *args[]) {
    char* filename = "./example/colored.jpg";
    Image* image = scaleImage(raw2Image(getRaw(filename)), 1);
    toHtml("./colored.html", image, '@', 2, "black");
    toGrayHtml("./colored_gray.html", image, '@', 2, "black");
    toAscii("./colored.txt", image);
    free(image->pixels);
    free(image);
}