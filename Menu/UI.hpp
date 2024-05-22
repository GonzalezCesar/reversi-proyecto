#include "pdcurs36/curses.h" // Incluir la biblioteca pdcurses en lugar de ncurses

#include <string> // Incluir el encabezado para std::string
#include <vector> // Incluir el encabezado para std::vector

struct Coord {
  int fila;
  int columna;
};

#ifndef UI_HPP
#define UI_HPP

enum Color {
    RED = 1,
    GREEN,
    CYAN,
    YELLOW,
    WHITE,
    MAGENTA,
    BLUE,
};


class UI {
public:
    UI();
    void showMenu();
    void clearScreen();

    private: 
        void handleOption(int option);
};

#endif // UI_HPP
