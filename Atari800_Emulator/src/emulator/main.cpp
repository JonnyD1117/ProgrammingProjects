
// std
#include <iostream>

// local 
#include "NCursesWrapper.hpp"

int main() {

    NcursesApp app;

    int x = 10, y = 5;
    app.drawText(y, x, "@", 1);
    app.refreshScreen();

    int ch;
    while ((ch = app.getInput()) != 'q') { // Press 'q' to quit
        app.drawText(y, x, " "); // Clear old position

        switch (ch) {
            case KEY_UP:    y--; break;
            case KEY_DOWN:  y++; break;
            case KEY_LEFT:  x--; break;
            case KEY_RIGHT: x++; break;
        }

        app.drawText(y, x, "@", 2); // Draw new position in red
        app.refreshScreen();
    }

    return 0;
}