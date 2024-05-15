#include "../include/reversi.hpp"
#include "../include/coordenada.hpp"
#include "../include/jugador.hpp"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

Reversi::Reversi() {}

coordenada ruta[] = {{-1, 0, 0}, {-1, -1, 0}, {0, -1, 0}, {1, -1, 0},
                     {-1, 1, 0}, {1, 0, 0},   {1, 1, 0},  {0, 1, 0}};

int Reversi::siguienteJugador(int jugadorActual) {

  if (jugadorActual == 1)
    return 2;
  else
    return 1;
}

bool Reversi::fueraDeRango(coordenada p) {
  if ((p.x > 8 || p.y > 8) || (p.x < 1 || p.y < 1)) {
    // cout << p.x << p.y << endl;
    return true;
  }
  return false;
}

// Dibuja la línea hasta la coordenada con la otra ficha del jugador

void Reversi::marcarLinea(coordenada sentido, coordenada posicionPrevia,
                          int jugador) {
  int posiciones = 0;

  while (tablero.getPosicion(posicionPrevia) == siguienteJugador(jugador)) {

    if (revisarLinea(sentido, posicionPrevia, jugador)) {
      tablero.agregarFicha(posicionPrevia);
      conteoDeFichas[jugador - 1]++;
      conteoDeFichas[siguienteJugador(jugador) - 1]--;
    }
    posicionPrevia.x += sentido.x;
    posicionPrevia.y += sentido.y;
    if (fueraDeRango(posicionPrevia))
      break;
  }
}

bool Reversi::revisarLinea(coordenada sentido, coordenada posicionPrevia,
                           int jugador) {

  while (true) {
    if (tablero.getPosicion(posicionPrevia) == jugador) {
      return true;
    }
    posicionPrevia.x += sentido.x;
    posicionPrevia.y += sentido.y;

    if (fueraDeRango(posicionPrevia)) {
      break;
    }
  }
  return false;
}
bool Reversi::marcarVecinos(coordenada posicion, int jugador) {
  int chequeo = 0;

  for (int i = 0; i < 8; i++) {
    coordenada posicionVecina = posicion;
    posicionVecina.x += ruta[i].x;
    posicionVecina.y += ruta[i].y;

    if (!fueraDeRango(posicionVecina)) {
      marcarLinea(ruta[i], posicionVecina, jugador);
    }
  }
  if (chequeo > 0)
    return true;
  return false;
}

bool Reversi::chequearCercanias(coordenada posicion, int jugador) {
  int chequeo = 0;

  for (int i = 0; i < 8; i++) {
    coordenada posicionVecina = posicion;

    posicionVecina.x += ruta[i].x;
    posicionVecina.y += ruta[i].y;

    if (!fueraDeRango(posicionVecina)) {
      if ((tablero.getPosicion(posicionVecina) == siguienteJugador(jugador)) &&
          revisarLinea(ruta[i], posicion, jugador))
        return true;
    }
  }
  return false;
}

void Reversi::printTablero(int jugador) { tablero.mostrarTablero(jugador); }

void Reversi::iniciarJuego() {
  tablero.agregarFicha({5, 4, 1});
  tablero.agregarFicha({4, 5, 1});
  tablero.agregarFicha({5, 5, 2});
  tablero.agregarFicha({4, 4, 2});

  fichasEnJuego[0] = {5, 4, 1};
  fichasEnJuego[1] = {4, 5, 1};
  fichasEnJuego[2] = {5, 5, 2};
  fichasEnJuego[3] = {4, 4, 2};

  conteoDeFichas[0] = 2;
  conteoDeFichas[1] = 2;

  ultimaFicha = 4;
}

void Reversi::agregarFichaJugador(coordenada ficha) {
  conteoDeFichas[ficha.valor] += 1;
}

bool Reversi::gameOver() {
  if (tablero.tableroLleno())
    return true;
  return false;
}

bool Reversi::realizarJugada(int jugador) {
  coordenada input;

  input.valor = jugador;
  cout << "x coord: ";
  cin >> input.x;
  cout << "y coord: ";
  cin >> input.y;

  if ((tablero.getPosicion(input) == 0) &&
      (chequearCercanias(input, jugador))) {
    marcarVecinos(input, jugador);
    tablero.agregarFicha(input);
    conteoDeFichas[input.valor - 1]++;
    return true;

  } else {
    cout << "\nMovimiento erroneo" << endl;
  }
  return false;
}

void Reversi::autoJugada(coordenada input, int jugador) {
  if (tablero.getPosicion(input) == 0) {
    input.valor = jugador;
    marcarVecinos(input, jugador);
    tablero.agregarFicha(input);
  }
}

int Reversi::getFichasEnTablero(int jugador) {
  return conteoDeFichas[jugador - 1];
}
int Reversi::getGanador() {
  if (conteoDeFichas[0] > conteoDeFichas[1])
    return 1;
  else if (conteoDeFichas[0] < conteoDeFichas[1]) {
    return 2;
  }
  return 0;
}

void Reversi::anunciarGanador(Jugador p1, Jugador p2) {

  if (getGanador() == 1) {
    cout << p1.getNombre() << "(" << p1.getTurno() << ")"
         << " es el ganador!" << endl;
  } else if (getGanador() == 2) {
    cout << p2.getNombre() << "(" << p2.getTurno() << ")"
         << " es el ganador!" << endl;
  } else
    cout << "Empate!" << endl;
}
