#pragma once
#include <ncurses.h>
#include <string>

class NcursesApp {
public:
    NcursesApp() {
        initscr();            // Start Ncurses mode
        cbreak();             // Disable line buffering
        noecho();             // Don't echo typed chars
        keypad(stdscr, TRUE); // Enable arrow keys
        curs_set(0);          // Hide cursor

        if (has_colors()) {
            start_color();
            init_pair(1, COLOR_GREEN, COLOR_BLACK);
            init_pair(2, COLOR_RED, COLOR_BLACK);
            init_pair(3, COLOR_YELLOW, COLOR_BLUE);
        }
    }

    ~NcursesApp() {
        endwin(); // Cleanup Ncurses
    }

    void clearScreen() {
        clear();
    }

    void refreshScreen() {
        refresh();
    }

    void drawText(int y, int x, const std::string& text, int colorPair = 0) {
        if (colorPair != 0) {
            attron(COLOR_PAIR(colorPair));
        }
        mvprintw(y, x, "%s", text.c_str());
        if (colorPair != 0) {
            attroff(COLOR_PAIR(colorPair));
        }
    }

    int getInput() {
        return getch();
    }

    void hideCursor() { curs_set(0); }
    void showCursor() { curs_set(1); }
};