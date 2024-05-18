#include "../include/tablero.hpp"
#include "../include/coordenada.hpp"
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

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
  conteoDeFichas[0] = 0;
  conteoDeFichas[1] = 0;
}

void Tablero::agregarFicha(coordenada p) {

  if (tablero[p.y - 1][p.x - 1] == 0) {

    tablero[p.y - 1][p.x - 1] = p.valor;
    capacidad--;
  } else
    tablero[p.y - 1][p.x - 1] = p.valor;

  if (p.valor != 3)
    conteoDeFichas[p.valor - 1]++;
}

int (*(Tablero::getTablero)())[8] { return tablero; }

void Tablero::mostrarTablero(int jugador) {
  jugadasPosibles = 0;
  cout << "    1  2  3  4  5  6  7  8" << endl;
  cout << "    |  |  |  |  |  |  |  |" << endl;

  for (int i = 0; i < 8; i++) {
    std::vector<coordenada> sugerencias;
    cout << i + 1 << "|  ";

    for (int j = 0; j < 8; j++) {
      mostrarInformacionCorrespondiente(jugador, tablero[i][j]);
      if (tablero[i][j] == 3) {
        coordenada posicion{j + 1, i + 1, tablero[i][j]};
        sugerencias.push_back(posicion);
        jugadasPosibles++;
      }
    }
    printSugerencias(sugerencias);

    cout << endl;
  }
}

void Tablero::mostrarInformacionCorrespondiente(int jugador, int posicion) {
  if (posicion == 3)
    cout << "x  ";

  else if (posicion == 0)
    cout << ".  ";

  else
    cout << posicion << "  ";
}

int Tablero::getPosicion(coordenada p) { return tablero[p.y - 1][p.x - 1]; }

int Tablero::getCapacidad() { return capacidad; }

std::vector<coordenada> Tablero::getFichasEnJuego() { return fichasEnJuego; }

void Tablero::modificarFichaEnJuego(coordenada ficha) {

  for (int i = 0; i < fichasEnJuego.size(); i++) {
    if (coordenadasIguales(fichasEnJuego[i], ficha)) {
      fichasEnJuego[i] = ficha;
      disminuirFichasJugador(getJugadorContrario(ficha.valor));
    }
  }
}

void Tablero::guardarFichaJugada(coordenada p) { fichasEnJuego.push_back(p); }

int Tablero::getConteoDeFichas(int jugador) {
  return conteoDeFichas[jugador - 1];
}

bool Tablero::coordenadasIguales(coordenada p1, coordenada p2) {

  if ((p1.x == p2.x) && (p1.y == p2.y))
    return true;
  return false;
}

int Tablero::getJugadorContrario(int jugador) {
  if (jugador == 1)
    return 2;
  else if (jugador == 2)
    return 1;
  return 0;
}

void Tablero::disminuirFichasJugador(int jugador) {
  if (jugador != 0)
    conteoDeFichas[jugador - 1]--;
}

void Tablero::printFichasEnJuego() {

  for (auto i : fichasEnJuego) {

    cout << "(" << i.x << ", " << i.y << "=" << i.valor << ")" << endl;
  }
}

void Tablero::limpiarSugerencias() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (tablero[i][j] == 3)
        tablero[i][j] = 0;
    }
  }
}

void Tablero::printSugerencias(std::vector<coordenada> sugerencias) {

  if (sugerencias.size() >= 1) {
    cout << "  --> ";
    for (auto i : sugerencias) {
      cout << "[" << i.x << ", " << i.y << "]";
    }
  }
}

int Tablero::getJugadasPosibles() { return jugadasPosibles; }
