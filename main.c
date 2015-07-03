#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

#include "matcher.h"

void help() {
    printf("Usage:\n");
    printf("  matcher -d DIR\n");
}


int main(int argc, char**argv) {
    char c;
    char *dir = NULL;
    opterr = 0;

    while ((c = getopt(argc, argv, "d:")) != -1) {
        switch (c) {
        case 'd':
            dir = optarg;
            break;
        }
    }

    if (dir == NULL) {
        help();
        return -1;
    }

    printf("Monitoring: %s\n", dir);

    FileDatabase *db = match_database_init();
    int imported = match_database_add_dir(db, dir);
    printf("Imported: %d", imported);

    return 0;
}
