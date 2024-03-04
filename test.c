#include <stdint.h>
#include <math.h>

// Compile with: clang -dynamiclib -o test.dylib test.c

typedef struct {
    double x;
    double y;
} Point;

// square = ForeignFunctionLoad["test.dylib", "square", {"Real64"} -> "Real64"]
extern double square(double x) { return x * x; }

// distance = ForeignFunctionLoad["test.dylib", "distance", {{"Real64", "Real64"}, {"Real64", "Real64"}} -> "Real64"]
extern double distance(Point p1, Point p2) {
    return sqrt(square(p1.x - p2.x) + square(p1.y - p2.y));
}

// norm = ForeignFunctionLoad["test.dylib", "norm", {{"Real64", "Real64"}} -> "Real64"]
extern double norm(Point p) {
    return sqrt(square(p.x) + square(p.y));
}

// dot = ForeignFunctionLoad["test.dylib", "dot", {{"Real64", "Real64"}, {"Real64", "Real64"}} -> "Real64"]
extern double dot(Point p1, Point p2) {
    return p1.x * p2.x + p1.y * p2.y;
}

// cross = ForeignFunctionLoad["test.dylib", "cross", {{"Real64", "Real64"}, {"Real64", "Real64"}} -> "Real64"]
extern double cross(Point p1, Point p2) {
    return p1.x * p2.y - p1.y * p2.x;
}

// add = ForeignFunctionLoad["test.dylib", "add", {{"Real64", "Real64"}, {"Real64", "Real64"}} -> {"Real64", "Real64"}]
extern Point add(Point p1, Point p2) {
    return (Point){p1.x + p2.x, p1.y + p2.y};
}

// subtract = ForeignFunctionLoad["test.dylib", "subtract", {{"Real64", "Real64"}, {"Real64", "Real64"}} -> {"Real64", "Real64"}]
extern Point subtract(Point p1, Point p2) {
    return (Point){p1.x - p2.x, p1.y - p2.y};
}

// scale = ForeignFunctionLoad["test.dylib", "scale", {{"Real64", "Real64"}, "Real64"} -> {"Real64", "Real64"}]
extern Point scale(Point p, double s) {
    return (Point){p.x * s, p.y * s};
}

// normalize = ForeignFunctionLoad["test.dylib", "normalize", {{"Real64", "Real64"}} -> {"Real64", "Real64"}]
extern Point normalize(Point p) {
    return scale(p, 1.0 / norm(p));
}

// angle = ForeignFunctionLoad["test.dylib", "angle", {{"Real64", "Real64"}, {"Real64", "Real64"}} -> "Real64"]
extern double angle(Point p1, Point p2) {
    return atan2(cross(p1, p2), dot(p1, p2));
}

// rotate = ForeignFunctionLoad["test.dylib", "rotate", {{"Real64", "Real64"}, "Real64"} -> {"Real64", "Real64"}]
extern Point rotate(Point p, double a) {
    return (Point){p.x * cos(a) - p.y * sin(a), p.x * sin(a) + p.y * cos(a)};
}

// reflect = ForeignFunctionLoad["test.dylib", "reflect", {{"Real64", "Real64"}, {"Real64", "Real64"}} -> {"Real64", "Real64"}]
extern Point reflect(Point p, Point n) {
    return subtract(p, scale(n, 2 * dot(p, n)));
}

// project = ForeignFunctionLoad["test.dylib", "project", {{"Real64", "Real64"}, {"Real64", "Real64"}} -> {"Real64", "Real64"}]
extern Point project(Point p, Point n) {
    return scale(n, dot(p, n) / square(norm(n)));
}

// reject = ForeignFunctionLoad["test.dylib", "reject", {{"Real64", "Real64"}, {"Real64", "Real64"}} -> {"Real64", "Real64"}]
extern Point reject(Point p, Point n) {
    return subtract(p, project(p, n));
}
