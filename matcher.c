#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

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


/* Return how many file entries are imported */
int match_database_add_dir(FileDatabase *db, char *dir) {
    // printf("Processing: %s\n", dir);
    DIR *root;
    int n = 0;
    char* fullpath = malloc(sizeof(char) * 255);

    root = opendir(dir);
    if (NULL == root) {
        perror("Can't open dir");
        return -1;
    }

    struct dirent *entry;
    while (NULL != (entry = readdir(root))) {
        if (entry->d_type == DT_REG) {
            n++;
            snprintf(fullpath, 255, "%s/%s", dir, entry->d_name);
            match_database_add_file(db, fullpath);
        }

        if (entry->d_type == DT_DIR) {
            if ((0 == strcmp(entry->d_name, ".")) || (0 == strcmp(entry->d_name, ".."))) {
                // pass
            } else {
                snprintf(fullpath, 255, "%s/%s", dir, entry->d_name);
                int result = match_database_add_dir(db, fullpath);
                if (result > 0) {
                    n = n + result;
                }
            }
        }
    }

    closedir(root);

    return n;
}

void match_database_dump(FileDatabase *db) {
    FileDatabaseEntry *node;

    printf("\nStart dumping:\n");

    for (node = db->entry; node != NULL; node = node->next) {
        printf("* File: %s\n", node->filename);
    }
}


void match_database_destroy_entry(FileDatabaseEntry *entry) {
    free(entry->filename);
    free(entry);
}


void match_database_remove_file(FileDatabase *db, char *filename) {
    FileDatabaseEntry *node;
    FileDatabaseEntry *match;

    node = db->entry;
    while (node != NULL) {
        if ((node->next != NULL) && (strcmp(node->next->filename, filename) == 0)) {
            match = node->next;
            node->next = match->next;

            match_database_destroy_entry(match);
            continue;
        }

        node = node->next;
    }

    /* first node can also be a match */
    if (db->entry != NULL) {
        if (strcmp(db->entry->filename, filename) == 0) {
            match = db->entry;
            db->entry = db->entry->next;
            match_database_destroy_entry(match);
        }
    }
}


FileDatabase *match_database_init() {
    return malloc(sizeof(struct FileDatabase));
}
