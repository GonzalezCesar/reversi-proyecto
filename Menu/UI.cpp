#include "UI.hpp"
#include <cstdio>
#include <iostream>
#include "pdcurs36/curses.h" // Cambiar la inclusión de la biblioteca ncurses por pdcurses
#include <string>

using namespace std;

UI::UI() {
  initscr();
    start_color(); // Habilitar el uso de colores
    keypad(stdscr, TRUE); // Habilitar el teclado numérico
    init_pair(1, COLOR_GREEN, COLOR_BLACK); 
    init_pair(2, COLOR_RED, COLOR_BLACK);



};

void UI::clearScreen() {
    clear();
    refresh();
}

void UI::showMenu() {
    int max_y, max_x;
    int current_option = 1;
    getmaxyx(stdscr, max_y, max_x); // Obtener el tamaño de la terminal

    std::vector<std::string> ascii_art = {
        " _____   ______ __      __ ______  _____    _____  _____ ",
        "|  __ \\ |  ____|\\ \\    / /|  ____||  __ \\  / ____||_   _|",
        "| |__) || |__    \\ \\  / / | |__   | |__) || (___    | |  ",
        "|  _  / |  __|    \\ \\/ /  |  __|  |  _  /  \\___ \\   | |  ",
        "| | \\ \\ | |____    \\  /   | |____ | | \\ \\  ____) | _| |_ ",
        "|_|  \\_\\|______|    \\/    |______||_|  \\_\\|_____/ |_____|",
        "                                                         ",
        "                                                         "
    };

    do {
        clearScreen();
        // Calcular las coordenadas para centrar el menú
        int menu_y = (max_y - 11) / 2; 
        int menu_x = (max_x - 40) / 2;

        attron(COLOR_PAIR(1));
        // Imprimir el arte ASCII
        for (size_t i = 0; i < ascii_art.size(); ++i) {
            mvprintw(menu_y - 7 + i, menu_x - 5, ascii_art[i].c_str());
        }
        attroff(COLOR_PAIR(1));

        attron(COLOR_PAIR(1));
        mvprintw(menu_y - 1, menu_x - 1, "+----------------------------------------+");
        mvprintw(menu_y + 10, menu_x - 1, "+----------------------------------------+");
        for (int i = 0; i < 11; ++i) {
            mvprintw(menu_y + i, menu_x - 1, "|");
            mvprintw(menu_y + i, menu_x + 40, "|");
        }
        attroff(COLOR_PAIR(1));

        // Imprimir el menú
        attron(COLOR_PAIR(1));
        mvprintw(menu_y + 1, menu_x, "1. NUEVA PARTIDA");
        mvprintw(menu_y + 2, menu_x, "2. CPU VS CPU");
        mvprintw(menu_y + 3, menu_x, "3. CPU VS HUMANO");
        mvprintw(menu_y + 4, menu_x, "4. HUMANO VS HUMANO");
        mvprintw(menu_y + 5, menu_x, "5. SALIR");
        attroff(COLOR_PAIR(1));

        // Pintar opción actual
        attron(COLOR_PAIR(2));
        switch (current_option) {
            case 1:
                mvprintw(menu_y + 1, menu_x, "1. NUEVA PARTIDA");
                break;
            case 2:
                mvprintw(menu_y + 2, menu_x, "2. CPU VS CPU");
                break;
            case 3:
                mvprintw(menu_y + 3, menu_x, "3. CPU VS HUMANO");
                break;
            case 4:
                mvprintw(menu_y + 4, menu_x, "4. HUMANO VS HUMANO");
                break;
            case 5:
                mvprintw(menu_y + 5, menu_x, "5. SALIR");
                break;
        }
        attroff(COLOR_PAIR(2));

        mvprintw(menu_y + 6, menu_x, "Seleccione una opción (w/s/enter) ");
        refresh();
 
        int ch = getch();
        if (ch == 'w' || ch == KEY_UP) {
            if (current_option > 1) {
                current_option--;
            }
        } else if (ch == 's' || ch == KEY_DOWN) {
            if (current_option < 5) {
                current_option++;
            }
        } else if (ch == '\n') {
            if (current_option >= 1 && current_option <= 5) {
                if (current_option == 5) {
                  endwin();
                  return;
                } 
                handleOption(current_option); 
            }

        }
    } while (true);
}

void UI::handleOption(int option) {
    // SubMenu subMenu;

    // switch (option) {
    //     case 1:
    //         subMenu.tagsHtml(parser.getTagCounts());
    //         break;
    //     case 2:
    //         subMenu.buscarUnTag(parser);
    //         break;
    //     case 3:
    //         subMenu.enlacesHtml(parser.getLinks());
    //         break;
    //     case 4:
    //         subMenu.imagenesHtml(parser.getImages());
    //         break;

    //     case 5: {
    //         GestorDeArchivos gestorDeArchivos;
    //         gestorDeArchivos.guardarAnalisis(parser, "./reporte/reporte_analisis.txt");
    //         mvprintw(LINES - 5, COLS / 2 - 15, "<< Reporte guardado con exito >>");
    //         refresh();
    //         getchar();
    //         break;
    //     }
    // }
}



