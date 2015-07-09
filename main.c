#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

#include "matcher.h"

void help() {
    printf("Usage:\n");
    printf("  matcher -d DIR -s PATTERN\n");
}


int main(int argc, char**argv) {
    char c;
    int i;
    char *dir = NULL;
    char *pattern = NULL;
    opterr = 0;

    while ((c = getopt(argc, argv, "s:d:")) != -1) {
        switch (c) {
        case 'd':
            dir = optarg;
            break;
        case 's':
            pattern = optarg;
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
    printf("Imported: %d\n", imported);

    // match_database_dump(db);
    
    if (pattern != NULL) {
        char **matched = malloc(10 * sizeof(char *));
        int result = match_database_match_files(db, pattern, matched, 10);
        printf("Matched %d results:\n", result);
        for (i = 0; i < result; i++) {
            printf(" - %s\n", matched[i]);
            free(matched[i]);
        }
    }

    return 0;
}
