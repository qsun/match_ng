#include <stdio.h>

#include "matcher.h"


int main(int argc, char**argv) {
    char *filename = "/usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o";
    char *pattern = "/udrx86o";
    
    printf("match file [%s] with [%s]: %x", filename, pattern, match_filename(filename, pattern));
    return 0;
}
