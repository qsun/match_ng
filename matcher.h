#ifndef MATCHER_H
#define MATCHER_H

#define MATCH_HIT 1
#define MATCH_MISS 0



typedef struct FileDatabaseEntry {
    char *filename;
    struct FileDatabaseEntry *next;
} FileDatabaseEntry;


typedef struct FileDatabase {
    struct FileDatabaseEntry *entry;
} FileDatabase;


FileDatabase *match_database_init();
void match_database_add_file(FileDatabase *db, char *filename);
void match_database_remove_file(FileDatabase *db, char *filename);
void match_database_dump(FileDatabase *db);


/* match filename with pattern, return 1 on success, and return 0 on failure */
int match_filename(char* filename, char* pattern);

#endif