#include "../include/reversi.hpp"
#include "../include/coordenada.hpp"
#include "../include/jugador.hpp"
#include <iostream>

#define RED "\x1b[31m"
#define RESET "\x1b[0m"
#define YELLOW "\x1b[33m"

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
    return true;
  }
  return false;
}

void Reversi::marcarLinea(coordenada sentido, coordenada posicionPrevia,
                          int jugador) {
  int posiciones = 0;

  while (tablero.getPosicion(posicionPrevia) == siguienteJugador(jugador)) {

    if (revisarLinea(sentido, posicionPrevia, jugador)) {
      capturarFicha(posicionPrevia, jugador);
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
    if (tablero.getPosicion(posicionPrevia) == jugador)
      return true;

    posicionPrevia.x += sentido.x;
    posicionPrevia.y += sentido.y;

    if (fueraDeRango(posicionPrevia))
      break;
  }
  return false;
}

bool Reversi::marcarVecinos(coordenada posicion, int jugador) {
  int chequeo = 0;

  for (int i = 0; i < 8; i++) {
    coordenada posicionVecina = posicion;
    posicionVecina.x += ruta[i].x;
    posicionVecina.y += ruta[i].y;

    if (!fueraDeRango(posicionVecina))
      marcarLinea(ruta[i], posicionVecina, jugador);
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
  coordenada jugadas[] = {{5, 4, 1}, {4, 5, 1}, {5, 5, 2}, {4, 4, 2}};

  for (int i = 0; i < 4; i++) {
    tablero.agregarFicha(jugadas[i]);
    tablero.guardarFichaJugada(jugadas[i]);
  }
}
bool Reversi::gameOver() {
  if ((tablero.tableroLleno()) || (turnosSaltados == 2))
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

  if (((tablero.getPosicion(input) == 3) && (tablero.getPosicion(input))) &&
      (chequearCercanias(input, jugador))) {
    turnosSaltados = 0;

    marcarVecinos(input, jugador);
    tablero.agregarFicha(input);
    tablero.guardarFichaJugada(input);
    return true;

  } else
    printf(RED "\nMovimiento erroneo.\n" RESET);

  return false;
}

void Reversi::autoJugada(coordenada input, int jugador) {

  if (tablero.getPosicion(input) == 3) {
    input.valor = jugador;
    marcarVecinos(input, jugador);
    tablero.agregarFicha(input);
  }
}

int Reversi::getGanador() {
  int fichas1 = tablero.getConteoDeFichas(1);
  int fichas2 = tablero.getConteoDeFichas(2);

  if (fichas1 > fichas2)
    return 1;
  else if (fichas1 < fichas2) {
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

void Reversi::capturarFicha(coordenada posicion, int jugador) {
  tablero.agregarFicha(posicion);
  tablero.modificarFichaEnJuego(posicion);
}

bool Reversi::agregarPosicionesSugeridas(int jugador) {
  std::vector<coordenada> fichas = tablero.getFichasEnJuego();

  for (auto i : fichas) {
    if (i.valor == jugador) {
      buscarPosicionesDisponibles(jugador, i);
    }
  }
  return false;
}

void Reversi::buscarPosicionesDisponibles(int jugador, coordenada ficha) {

  for (int i = 0; i < 8; i++) {
    coordenada posicionVecina = ficha;

    posicionVecina.x += ruta[i].x;
    posicionVecina.y += ruta[i].y;

    if (!fueraDeRango(posicionVecina)) {
      if ((tablero.getPosicion(posicionVecina) == siguienteJugador(jugador)))
        // cout << "in" << endl;
        marcarPosicionDisponible(ruta[i], ficha);
    }
  }
}

void Reversi::marcarPosicionDisponible(coordenada sentido,
                                       coordenada posicionPrevia) {
  bool chequeo = false;
  // cout << "\n[sentido: " << sentido.x << ", " << sentido.y << "]" << endl;
  // cout << "from: " << posicionPrevia.x << ", " << posicionPrevia.y;
  while (true) {
    if (tablero.getPosicion(posicionPrevia) == 0) {
      // cout << " | to: " << posicionPrevia.x << ", " << posicionPrevia.y;
      break;
    }

    if (tablero.getPosicion(posicionPrevia) ==
        tablero.getJugadorContrario(posicionPrevia.valor))
      chequeo = true;

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
    posicionPrevia.valor = 3;
    // cout << " --> " << posicionPrevia.x << ", " << posicionPrevia.y << endl;
    tablero.agregarFicha(posicionPrevia);
  }
}

void Reversi::sinMovimientosDisponibles() {
  printf(YELLOW
         "\nNo hay movimientos disponibles. Presione cualquier tecla para "
         "continuar\n" RESET);
  getchar();
}

bool Reversi::forzarGameOver() {
  if (turnosSaltados == 2)
    return true;
  return false;
}

bool Reversi::saltarTurno(int turno) {
  if (tablero.getJugadasPosibles() == 0) {
    if ((turnosSaltados < 1) && (tablero.getCapacidad() > 0))
      printf(YELLOW
             "\nEl jugador %d no posee movimientos disponibles, su turno "
             "ha sido saltado\n" RESET,
             turno);

    turnosSaltados++;
    return true;
  }

  return false;
}
