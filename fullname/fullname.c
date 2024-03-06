#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* first;
    const char* last;
} Name;

extern const char* fullname(Name name) {
    static char full[1000];
    snprintf(full, sizeof(full), "%s %s", name.first, name.last);
    return full;
}