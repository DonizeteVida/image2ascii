#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

#include "src/data.h"
#include "src/read.h"
#include "src/print.h"
#include "src/transform.h"

int main(int argc, char *args[]) {
    char* filename = "./example/book.jpeg";
    Image* image = raw2Image(getRaw(filename));
    toHtml("./teste.html", image, '@', 1, "black");
    image = scaleImage(image, .3);
    toHtml("./teste2.html", image, '@', 1, "black");
}