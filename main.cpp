#include "include/jugador.hpp"
#include "include/reversi.hpp"
#include <iostream>

using std::cout;
using std::endl;
using std::string;

void printCoordenada(coordenada p) {
  cout << "(" << p.x << ", " << p.y << ") => " << p.valor << endl;
}

int main() {
  Reversi game;
  Jugador player[2];
  coordenada input;

  player[0].setTurno(1);
  player[0].setNombre("Antoniel");

  player[1].setTurno(2);
  player[1].setNombre("Test");

  game.iniciarJuego();
  while (!game.gameOver()) {

    for (int i = 0; i < 2; i++) {
      system("clear");
      while (true) {
        game.printTablero(player[i].getTurno());
        cout << endl
             << player[i].getNombre() << "(" << player[i].getTurno() << ")"
             << endl;
        // cout << "c: " << game.tablero.getCapacidad() << endl;
        // cout << "p1 pieces: " << game.getFichasEnTablero(1) << endl;
        // cout << "p2 pieces: " << game.getFichasEnTablero(2) << endl;
      }
    }
  }

  game.anunciarGanador(player[0], player[1]);
  game.printTablero(player[0].getTurno());
  cout << "Game over." << endl;
}
