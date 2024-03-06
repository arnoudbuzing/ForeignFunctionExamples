# Exploring the Foreign Function Interface in the Wolfram Language

## Introduction

The [Foreign Function Interface](https://reference.wolfram.com/language/guide/ForeignFunctionInterface.html) (or FFI for short) is a powerful feature that allows the Wolfram Language to interact with external C libraries. This capability opens up a wide range of possibilities for extending the functionality of the Wolfram Language and integrating it with existing codebases.

The FFI is different from [LibraryLink](https://reference.wolfram.com/language/guide/LibraryLink.html), which is a more direct and low-level interface for integrating C code with the Wolfram Language. While LibraryLink provides a way to create and call C functions from within the Wolfram Language, the FFI allows you to call existing C functions from external libraries directly from the Wolfram Language.

In this post, I will explore the concept of the foreign function interface and its benefits. I will also provide a step-by-step guide on how to use the FFI in the Wolfram Language, including importing external libraries and calling functions.

## What is the Foreign Function Interface?

The FFI was introduced in version 14 of the Wolfram Language and is designed to provide a high-level, user-friendly interface for calling external C functions. It allows you to import and call functions from shared libraries, DLLs, and other external code without having to write low-level C code or use LibraryLink.

The FFI is particularly useful for tasks such as: 
- Interfacing with existing C libraries and codebases
- Accessing system-level functionality that is not directly available in the Wolfram Language
- Calling performance-critical functions that are implemented in C

The FFI provides a way to seamlessly integrate C code with the Wolfram Language, allowing you to take advantage of the rich set of built-in functions and data types in the Wolfram Language while still being able to call external code when needed.

## Supported Platforms and Languages

The FFI is supported on all desktop platforms that the Wolfram Language runs on, including Windows, macOS, and Linux. It is expected to work in the Wolfram Cloud in the future. You do not need to install any additional software or tools to use the FFI, as it is built into the Wolfram Language itself. All you need is the dynamic library that contains the C functions you want to call.

In this post however, I will show how to create a simple dynamic libraries using C and then call it from the Wolfram Language. This way you can see how to use the FFI in a simple and controlled environment. At the end of this post, I will link to some more complex real-world examples that use the FFI to call external libraries.

## Getting Started with FFI in the Wolfram Language

As is customary, let's start by creating a simple dynamic library using C. We will then import this library into the Wolfram Language and call the functions it contains using the FFI.

The following code is a simple C program that defines a function called `hello` which takes a string as an argument and returns `Hello <string>` back to the Wolfram Language:

```c
#include <stdio.h>
extern const char* hello(const char* name) {
    static char greeting[1000];
    snprintf(greeting, sizeof(greeting), "Hello %s", name);
    return greeting;
}
```

You can compile this code into a dynamic library in a terminal using the following command:

```bash
clang --dynamiclib -o hello.dylib hello.c
```

Or, perhaps more simply, you can use the following Wolfram Language commands to compile the code and create the dynamic library:

```mathematica
Needs["CCompilerDriver`"]
CreateLibrary[File["hello.c"],"hello.dylib"]
```

This will create a dynamic library called `hello.dylib` that contains the `hello` function. We can now import this library into the Wolfram Language and call the `hello` function using the FFI.

```mathematica
STRING = "RawPointer"::["UnsignedInteger8"];
hello = ForeignFunctionLoad[
    "hello.dylib", 
    "hello", 
    {STRING} -> STRING
    ]
```

Here, the first argument to `ForeignFunctionLoad` is the name of the dynamic library, the second argument is the name of the function we want to call, and the third argument is a list of argument types and return types for the function. In this case, the `hello` function takes a string as an argument and returns a string, so we use the `RawPointer::["CUnsignedChar"]` type to represent the string data.

Now that we have loaded the `hello` function, we can call it from the Wolfram Language like this:

```mathematica
ptr = hello["world"]
```
This will return a RawPointer to the string `"Hello world"`. We can use RawMemoryImport to convert this RawPointer to a string:

```mathematica
RawMemoryImport[ptr, "String"]
```

That's it for the first example! We have successfully imported a dynamic library into the Wolfram Language and called a function from it using the FFI.

Since we are working directly with C pointers, we can also modify the string in place. For example, we can change a string to uppercase with the following C code:

```c
#include <ctype.h>
extern void toupper(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = toupper(str[i]);
    }
}
```

To create the dynamic library in the Wolfram Language, run this code:

```mathematica
CreateLibrary[
 File["/Users/arnoudb/ForeignFunctionExamples/touppercase/touppercase.c"],
 "touppercase.dylib"
 ]
 ```

And then import the function into the Wolfram Language:

```mathematica
touppercase = ForeignFunctionLoad[
    "touppercase.dylib", 
    "touppercase", 
    {STRING} -> "Void"
]
```

Now we can call the `touppercase` function to change a string to uppercase:

```mathematica
ptr = RawMemoryExport["hello"];
touppercase[ptr];
RawMemoryImport[ptr, "String"]
```

The last line will return the string `"HELLO"`. It is important to note that the string is modified in place, so the original string pointed to by `ptr` is changed.

Next, let's look at how to work with more complex data types and structures using the FFI. We will create a dynamic library that defines a struct containing a first name and a last name, and a function that returns the full name as a string.

Here is the C code for the dynamic library:

```c
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
```

Again, we can compile this code into a dynamic library using the Wolfram Language:

```mathematica
CreateLibrary[File["fullname.c"],"fullname.dylib"]
 ```

And load it into the Wolfram Language:

```mathematica
NAME = {STRING, STRING};
fullname = ForeignFunctionLoad["fullname.dylib", "fullname", {NAME} -> STRING]
 ```

And call the `fullname` function:

```mathematica
first = RawMemoryExport["Arnoud"];
last = RawMemoryExport["Buzing"];
full = fullname[{first, last}];
RawMemoryImport[full, "String"]
```

This will return the string `"Arnoud Buzing"`. We have successfully called a function that takes a struct as an argument and returns a string using the FFI.

## Conclusion

The Foreign Function Interface in the Wolfram Language provides a powerful and user-friendly way to call external C functions from within the Wolfram Language. It allows you to seamlessly integrate C code with the Wolfram Language, opening up a wide range of possibilities for extending the functionality of the Wolfram Language and integrating it with existing codebases.

In this post, we explored the concept of the FFI and its benefits, and provided a step-by-step guide on how to use the FFI in the Wolfram Language. We created a simple dynamic library using C and then imported it into the Wolfram Language, and called the functions it contains using the FFI. We also looked at how to work with more complex data types and structures using the FFI.

## References

For more information on the Foreign Function Interface and accessing C libraries in the Wolfram Language, see the following resources:

- [Foreign Function Interface Documentation](https://reference.wolfram.com/language/guide/ForeignFunctionInterface.html) - The official documentation for the FFI in the Wolfram Language
- [Foreign Function Interface](https://www.youtube.com/watch?v=C82NHpy7D6k) - An in-depth video tutorial on the FFI in the Wolfram Language
- [LibraryLink Documentation](https://reference.wolfram.com/language/guide/LibraryLink.html) - The official documentation for LibraryLink in the Wolfram Language