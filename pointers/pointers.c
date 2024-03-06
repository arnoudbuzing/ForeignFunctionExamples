#include <stdlib.h>

// addone = ForeignFunctionLoad["./pointers.dylib", "addone", {"RawPointer"::["CInt"]} -> "CInt"]
extern int addone(int* ptr) {
    (*ptr)++;  // Increment the value pointed to by ptr by 1
    return 0; // Return 0 to indicate success
}