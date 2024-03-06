#include <stdio.h>
extern const char* hello(const char* name) {
    static char greeting[1000];
    snprintf(greeting, sizeof(greeting), "Hello %s", name);
    return greeting;
}