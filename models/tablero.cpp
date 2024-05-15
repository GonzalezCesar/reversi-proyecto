#include "../include/tablero.hpp"
#include "../include/coordenada.hpp"
#include <iostream>
using std::cout;
using std::endl;

bool Tablero::tableroLleno() {
  if (capacidad == 0)
    return true;
  return false;
}

Tablero::Tablero() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      tablero[i][j] = 0;
    }
  }
}

void Tablero::agregarFicha(coordenada p) {

  if (tablero[p.y - 1][p.x - 1] == 0) {

    tablero[p.y - 1][p.x - 1] = p.valor;
    capacidad--;
  } else
    tablero[p.y - 1][p.x - 1] = p.valor;
}

int (*(Tablero::getTablero)())[8] { return tablero; }

void Tablero::mostrarTablero(int jugador) {
  cout << "    1  2  3  4  5  6  7  8" << endl;
  cout << "    |  |  |  |  |  |  |  |" << endl;

  for (int i = 0; i < 8; i++) {
    cout << i + 1 << "|  ";

    for (int j = 0; j < 8; j++) {
      mostrarInformacionCorrespondiente(jugador, tablero[i][j]);
      // if (tablero[i][j] > 2)
      //   tablero[i][j] = 0;
      // cout << tablero[i][j] << "  ";
    }

    cout << endl;
  }
}

void Tablero::mostrarInformacionCorrespondiente(int jugador, int posicion) {
  if (jugador == 1) {
    if (posicion == 3)
      cout << "x"
           << "  ";
    else if ((posicion == 0) || (posicion == 4))
      cout << "."
           << "  ";
    else
      cout << posicion << "  ";
  }
  if (jugador == 2) {
    if (posicion == 4)
      cout << "x"
           << "  ";
    else if ((posicion == 0) || (posicion == 3)) {
      cout << "."
           << "  ";
    } else
      cout << posicion << "  ";
  }
}

int Tablero::getPosicion(coordenada p) { return tablero[p.y - 1][p.x - 1]; }

int Tablero::getCapacidad() { return capacidad; }
