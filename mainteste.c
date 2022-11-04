#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
        char *r = strdup("Marco:Q:3F7PKC");
    // check for errors

    char *tok = r, *end = r;
    while (tok != NULL) {
        strsep(&end, ":");
        puts(tok);
        tok = end;
    }

    free(r);
    return 0;
}