#include "matcher.h"
#include "assert.h"
#include <stdio.h>


void performance_test() {
    char *filename = "/usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o";
    char *pattern = "/usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o";
    
    match_filename(filename, pattern);
}


void matcher_test() {
    char *filename = "/usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o";
    char *pattern = "/udrx86o";

    assert(match_filename(filename, pattern) == MATCH_HIT);

    pattern = "/usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o";
    assert(match_filename(filename, pattern) == MATCH_HIT);

    pattern = "/usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.oa";
    assert(match_filename(filename, pattern) == MATCH_MISS);
}


int main(int argc, char **argv) {
    int i = 0;

    matcher_test();

    for (i = 0; i < 1000000; i++) {
        performance_test();
    }

    printf("\n=====\nStart database test\n");
    FileDatabase *db = match_database_init();
    match_database_dump(db);

    match_database_add_file(db, "/usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.oa");
    printf("Add");
    match_database_dump(db); 

    match_database_add_file(db, "/usr/lib/debug/usr/lib/x86_64-linux-gnu/test.c");
    printf("Add");
    match_database_dump(db); 

    match_database_remove_file(db, "/usr/lib/debug/usr/lib/x86_64-linux-gnu/test.c");
    printf("Removed");
    match_database_dump(db); 

    match_database_remove_file(db, "/usr/lib/debug/usr/lib/x86_64-linux-gnu/test.casdf");
    printf("Non Removed");
    match_database_dump(db); 

    return 0;
}
