#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "matcher.h"


/* return 1 on match */
int match_filename(char* filename, char* pattern) {
    char *remaining = filename;
    int i = 0;
    
    for (i = 0; i <= strlen(pattern) - 1; i++) {
        remaining = strchr(remaining, pattern[i]);
        if (remaining == NULL) {
            return MATCH_MISS;
        }
    }

    return MATCH_HIT;
}


void match_database_add_file(FileDatabase *db, char *filename) {
    FileDatabaseEntry *node;

    node = malloc(sizeof(struct FileDatabaseEntry));
    node->filename = strdup(filename);
    
    node->next = db->entry;
    db->entry = node;
}

void match_database_dump(FileDatabase *db) {
    FileDatabaseEntry *node;

    printf("\nStart dumping:\n");

    for (node = db->entry; node != NULL; node = node->next) {
        printf("* File: %s\n", node->filename);
    }
}


void match_database_remove_file(FileDatabase *db, char *filename) {
    FileDatabaseEntry *node;

    node = db->entry;
    while (node != NULL) {
        if ((node->next != NULL) && (strcmp(node->next->filename, filename) == 0)) {
            node->next = node->next->next;
            continue;
        }

        node = node->next;
    }

    /* first node can also be a match */
    if (db->entry != NULL) {
        if (strcmp(db->entry->filename, filename) == 0) {
            db->entry = db->entry->next;
        }
    }
}


FileDatabase *match_database_init() {
    return malloc(sizeof(struct FileDatabase));
}
