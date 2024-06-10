#include "../include/tablero.hpp"
#include "../include/coordenada.hpp"
#include <iostream>
#include <vector>

#define RED "\x1b[31m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define RESET "\x1b[0m"

using std::cout;
using std::endl;
using std::vector;

bool Tablero::tableroLleno() {
  if (capacidad == 0) return true;
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

  if (tablero[p.y - 1][p.x - 1] == 3) {
    tablero[p.y - 1][p.x - 1] = p.valor;
    capacidad--;
  } 

  else tablero[p.y - 1][p.x - 1] = p.valor;
  if (p.valor != 3) conteoDeFichas[p.valor - 1]++;
}

int (*(Tablero::getTablero)())[8] { return tablero; }

int Tablero::getPosicion(coordenada p) {
  return tablero[p.y - 1][p.x - 1];
}

int Tablero::getCapacidad() { return capacidad; } //Retorna la cantidad de espacios vacíos en el tablero

std::vector<coordenada> Tablero::getFichasEnJuego() { return fichasEnJuego; } //Retorna un Arreglo dinámico con 
void Tablero::modificarFichaEnJuego(coordenada ficha) {                       //las coordenadas de las fichas
  for (int i = 0; i < fichasEnJuego.size(); i++) {                            //en el tablero
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

  if ((p1.x == p2.x) && (p1.y == p2.y)) return true;
  return false;
}

int Tablero::getJugadorContrario(int jugador) {
  if (jugador == 1) return 2;
  else if (jugador == 2) return 1;

  return 0;
}

void Tablero::disminuirFichasJugador(int jugador) {
  if (jugador != 0) conteoDeFichas[jugador - 1]--;
}

void Tablero::limpiarSugerencias() { //Elimina las posiciones sugeridas del tablero
  jugadasPosibles = 0;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (tablero[i][j] == 3) tablero[i][j] = 0;
    }
  }
}

int Tablero::getJugadasPosibles() { return jugadasPosibles; }

void Tablero::contarJugadasPosibles() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (tablero[i][j] == 3) jugadasPosibles++;
    }
  }
}
