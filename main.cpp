#include "include/jugador.hpp"
#include "include/reversi.hpp"
#include <iostream>

using std::cout;
using std::endl;
using std::string;

coordenada x;

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

  int i = 0;

  game.iniciarJuego();
  // game.tablero.testing();
  while (!game.gameOver() && !game.forzarGameOver()) {
    system("cls");
    game.tablero.limpiarSugerencias();
    game.agregarPosicionesSugeridas(player[i].getTurno());
    game.tablero.contarJugadasPosibles();

    while (!game.saltarTurno(i + 1)) {

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
    i = game.siguienteJugador(i + 1) - 1;
    cout << "out" << endl;
  }

  game.printTablero(player[0].getTurno());
  game.anunciarGanador(player[0], player[1]);
  cout << "Game over." << endl;
}

// - Al terminar partida cambia el turno innecesariamente a pesar de no haber
// Moivimientos disponibles (fixed creo)

// - Permitir movimientos acorde a las posiciones
// sugeridas
