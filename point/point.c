#include <stdint.h>
#include <math.h>

// Compile with: clang -dynamiclib -o point.dylib point.c

typedef struct {
    double x;
    double y;
} Point;

// Square a number
double square(double num) {
    return num * num;
}

// Adds two points
// add = ForeignFunctionLoad["point.dylib", "add", {{"Real64", "Real64"}, {"Real64", "Real64"}} -> {"Real64", "Real64"}]
extern Point add(Point p1, Point p2) {
    return (Point){p1.x + p2.x, p1.y + p2.y};
}

// Subtract two points
// subtract = ForeignFunctionLoad["point.dylib", "subtract", {{"Real64", "Real64"}, {"Real64", "Real64"}} -> {"Real64", "Real64"}]
extern Point subtract(Point p1, Point p2) {
    return (Point){p1.x - p2.x, p1.y - p2.y};
}

// Scale a point by a factor
// scale = ForeignFunctionLoad["point.dylib", "scale", {{"Real64", "Real64"}, "Real64"} -> {"Real64", "Real64"}]
extern Point scale(Point p, double s) {
    return (Point){p.x * s, p.y * s};
}

// Compute the distance between two points
// distance = ForeignFunctionLoad["point.dylib", "distance", {{"Real64", "Real64"}, {"Real64", "Real64"}} -> "Real64"]
extern double distance(Point p1, Point p2) {
    return sqrt(square(p1.x - p2.x) + square(p1.y - p2.y));
}

// Compute the norm of a point
// norm = ForeignFunctionLoad["point.dylib", "norm", {{"Real64", "Real64"}} -> "Real64"]
extern double norm(Point p) {
    return sqrt(square(p.x) + square(p.y));
}

// Compute the dot product of two points
// dot = ForeignFunctionLoad["point.dylib", "dot", {{"Real64", "Real64"}, {"Real64", "Real64"}} -> "Real64"]
extern double dot(Point p1, Point p2) {
    return p1.x * p2.x + p1.y * p2.y;
}

// Normalize a point
// normalize = ForeignFunctionLoad["point.dylib", "normalize", {{"Real64", "Real64"}} -> {"Real64", "Real64"}]
extern Point normalize(Point p) {
    return scale(p, 1.0 / norm(p));
}

// Rotate a point by an angle
// rotate = ForeignFunctionLoad["point.dylib", "rotate", {{"Real64", "Real64"}, "Real64"} -> {"Real64", "Real64"}]
extern Point rotate(Point p, double a) {
    return (Point){p.x * cos(a) - p.y * sin(a), p.x * sin(a) + p.y * cos(a)};
}

// Reflect a point about a normal
// reflect = ForeignFunctionLoad["point.dylib", "reflect", {{"Real64", "Real64"}, {"Real64", "Real64"}} -> {"Real64", "Real64"}]
extern Point reflect(Point p, Point n) {
    return subtract(p, scale(n, 2 * dot(p, n)));
}

// Project a point onto a normal
// project = ForeignFunctionLoad["point.dylib", "project", {{"Real64", "Real64"}, {"Real64", "Real64"}} -> {"Real64", "Real64"}]
extern Point project(Point p, Point n) {
    return scale(n, dot(p, n) / square(norm(n)));
}