#include <iostream>
#include <string>
#include <emscripten/bind.h>

using namespace emscripten;

// Simple C++ function
int add(int a, int b) {
    return a + b;
}


class Point {
public:
    int x, y;
    Point(int x_, int y_) : x(x_), y(y_) {}
    int sum() { return x + y; }
};

// Bind functions and classes to JS
EMSCRIPTEN_BINDINGS(my_module) {
    function("add", &add);
    class_<Point>("Point")
        .constructor<int,int>()
        .function("sum", &Point::sum);
}