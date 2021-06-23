#include "iodot.h"

const char *color[]={
    "red","green","blue","yellow","purple",
    "orange","aqua","bisque","darkolivegreen1","gray50","maroon","wheat3",
    "blueviolet", "chocolate", "cyan", "darkgreen", "darkorange", "firebrick",
    "lawngreen", "gold", "darkkhaki", "salmon"
};
const int MAX_COLOR = sizeof(color) / sizeof(*color);

FILE* open_file(const char* n, const char* mode) {
    FILE* fp = fopen(n, mode);
    if(fp == NULL){
        printf("Error opening file with designation \"%s\" in local directory.\n", n);
        exit(1);
    }
    return fp;
}

void dot_to_pdf(const char* dot, const char* pdf) {;
    extern const char* layout;
    char command[100];
    sprintf(command, "%s -Tpdf %s -o %s", layout, dot, pdf);
    printf("Running: %s...\n", command);
    system(command);
    system("pause");
}