#include "../include/cpu.hpp"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <time>

coordenada sentido[] = {{-1, 0, 0}, {-1, -1, 0}, {0, -1, 0}, {1, -1, 0},
                        {-1, 1, 0}, {1, 0, 0},   {1, 1, 0},  {0, 1, 0}};

using std::vector;

Cpu::Cpu() {}

coordenada Cpu::getJugada() {
  jugada.valor = turno;
  return jugada;
}

void Cpu::setTablero(Tablero *t) { tablero = t; }

void Cpu::setMejorJugada() {                             //Establece el flanqueo que captura
  coordenada jugada{0, 0, 0};                            //la mayor cantidad de fichas (conteo en 1 sola dirección)
  coordenada temp{0, 0, 0};
  vector<coordenada> jugadas = tablero->getFichasEnJuego();
  for (auto i : jugadas) {
    temp = evaluarJugadas(i);
    if (temp.valor > jugada.valor)
      jugada = temp;
  }
}

coordenada Cpu::evaluarJugadas(coordenada ficha) { //Retorna el mejor flanqueo

  coordenada mejorJugada{0, 0, 0};
  coordenada temp{0, 0, 0};

  for (int i = 0; i < 8; i++) {
    coordenada posicionVecina = ficha;

    posicionVecina.x += sentido[i].x;
    posicionVecina.y += sentido[i].y;

    if (!fueraDeRango(posicionVecina)) {
      if ((tablero->getPosicion(posicionVecina) ==
           tablero->getJugadorContrario(turno))) {
        temp = obtenerPosicion(sentido[i], ficha);
        if (temp.valor > mejorJugada.valor)
          mejorJugada = temp;
      }
    }
  }
  return mejorJugada;
}

coordenada Cpu::obtenerPosicion(coordenada sentido, coordenada posicionPrevia) { //Retorna la posición a elegir para un flanqueo
  bool chequeo = false;
  int fichasCapturadas = 0;

  while (true) {
    if (tablero->getPosicion(posicionPrevia) == 3) {
      break;
    }

    if (tablero->getPosicion(posicionPrevia) ==
        tablero->getJugadorContrario(posicionPrevia.valor)) {
      fichasCapturadas++;
      chequeo = true;
    }

    else
      chequeo = false;

    posicionPrevia.x += sentido.x;
    posicionPrevia.y += sentido.y;

    if (fueraDeRango(posicionPrevia)) {
      chequeo = false;
      break;
    }
  }
  if (chequeo) {
    posicionPrevia.valor = fichasCapturadas;
    return posicionPrevia;
  }
  posicionPrevia.valor = 0;
  return posicionPrevia;
}

bool Cpu::fueraDeRango(coordenada p) {
  if ((p.x > 8 || p.y > 8) || (p.x < 1 || p.y < 1)) {
    return true;
  }
  return false;
}

void Cpu::setJugadaAleatoria() {                     //Establece una jugada aleatoria
  vector<coordenada> posiciones;
  srand((unsigned)time(NULL));
  int target = rand() % tablero->getJugadasPosibles();
  int n = 1;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      coordenada p{i + 1, j + 1, turno};
      if (tablero->getPosicion(p) == 3) {
        posiciones.push_back(p);
      }
    }
  }
  jugada = posiciones[target];
}

void Cpu::setTurno(int n) { turno = n; }
