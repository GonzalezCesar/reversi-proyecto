#include "include/jugador.hpp"
#include "include/reversi.hpp"
#include "Menu/UI.hpp"
#include <iostream>

using std::cout;
using std::endl;
using std::string;

int main() {
  UI ui;
  ui.showMenu();

}

// - Al terminar partida cambia el turno innecesariamente a pesar de no haber
// Moivimientos disponibles (fixed creo)

// - Permitir movimientos acorde a las posiciones
// sugeridas
