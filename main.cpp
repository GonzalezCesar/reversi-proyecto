#include "include/jugador.hpp"
#include "include/reversi.hpp"
#include <iostream>

using std::cout;
using std::endl;
using std::string;

coordenada x;

void automatic(coordenada &x) {
  if (x.x == 8) {
    x.y++;
    x.x = 1;
  } else
    x.x++;
}

void printCoordenada(coordenada p) {
  cout << "(" << p.x << ", " << p.y << ") => " << p.valor << endl;
}

int main() {
  Reversi game;
  Jugador player[2];
  coordenada input;
  x.x = 1;
  x.y = 1;
  player[0].setTurno(1);
  player[0].setNombre("Antoniel");

  player[1].setTurno(2);
  player[1].setNombre("Test");

  game.iniciarJuego();
  while (!game.gameOver()) {

    for (int i = 0; i < 2; i++) {
      system("cls");
      game.tablero.limpiarSugerencias();
      game.agregarPosicionesSugeridas(player[i].getTurno());
      while (true) {

        cout << "Fichas p1: " << game.tablero.getConteoDeFichas(1)
             << " | Fichas p2: " << game.tablero.getConteoDeFichas(2) << endl
             << endl;

        game.printTablero(player[i].getTurno());
        cout << endl
             << player[i].getNombre() << "(" << player[i].getTurno() << ")"
             << endl;
        cout << "\nLugares disponibles: " << game.tablero.getJugadasPosibles()
             << endl;
        if (game.realizarJugada(player[i].getTurno()))
          break;
      }
    }
  }

  game.anunciarGanador(player[0], player[1]);
  game.printTablero(player[0].getTurno());
  cout << "Game over." << endl;
}
