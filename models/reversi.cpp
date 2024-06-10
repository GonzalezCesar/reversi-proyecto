#include "../include/reversi.hpp"
#include "../include/coordenada.hpp"
#include "../include/jugador.hpp"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
Reversi::Reversi() {}

coordenada ruta[] = {{-1, 0, 0}, {-1, -1, 0}, {0, -1, 0}, {1, -1, 0}, //Sentidos de búsqueda
                     {-1, 1, 0}, {1, 0, 0},   {1, 1, 0},  {0, 1, 0}};

int Reversi::siguienteJugador(int jugadorActual) { //Retorna el jugador contrario
  if (jugadorActual == 1)
    return 2;
  else
    return 1;
}

bool Reversi::fueraDeRango(coordenada p) {            //Verdadero si las coordenadas dadas
  if ((p.x > 8 || p.y > 8) || (p.x < 1 || p.y < 1)) { //van más allá de la dimensión del tablero
    return true;
  }
  return false;
}

void Reversi::marcarLinea(coordenada sentido, coordenada posicionPrevia, //convierte en una dirección las fichas rivales encerradas
                          int jugador) {                                 //en el flanqueo
  int posiciones = 0;
  while (tablero->getPosicion(posicionPrevia) == siguienteJugador(jugador)) {

    if (revisarLinea(sentido, posicionPrevia, jugador)) {
      capturarFicha(posicionPrevia, jugador);
    }
    posicionPrevia.x += sentido.x;
    posicionPrevia.y += sentido.y;
    if (fueraDeRango(posicionPrevia))
      break;
  }
}

bool Reversi::revisarLinea(coordenada sentido, coordenada posicionPrevia, //revisa en una dirección 
                           int jugador) {                                 //verdadero: encuentra una ficha del jugador
  while (true) {                                                           //falso: nunca la encuentra
    if (tablero->getPosicion(posicionPrevia) == jugador)
      return true;

    posicionPrevia.x += sentido.x;
    posicionPrevia.y += sentido.y;

    if (fueraDeRango(posicionPrevia))
      break;
  }
  return false;
}

bool Reversi::marcarVecinos(coordenada posicion, int jugador) { //Revisa en las adyacencias de una ficha para
  int chequeo = 0;                                              //realizar múltiples flanqueos

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

bool Reversi::chequearCercanias(coordenada posicion, int jugador) {//Revisa en las adyacencias de una ficha para
  for (int i = 0; i < 8; i++) {                                    //Encontrar posibles flanqueos
    coordenada posicionVecina = posicion;                          //verdadero: hay flanqueos
                                                                   //falso: no los hay
    posicionVecina.x += ruta[i].x;
    posicionVecina.y += ruta[i].y;

    if (!fueraDeRango(posicionVecina)) {
      if ((tablero->getPosicion(posicionVecina) == siguienteJugador(jugador)) &&
          revisarLinea(ruta[i], posicion, jugador))
        return true;
    }
  }
  return false;
}

void Reversi::iniciarJuego() {
  coordenada jugadas[] = {{5, 4, 2}, {4, 5, 2}, {5, 5, 1}, {4, 4, 1}};

  for (int i = 0; i < 4; i++) {
    tablero->agregarFicha(jugadas[i]);
    tablero->guardarFichaJugada(jugadas[i]);
  }
}
bool Reversi::gameOver() {
  if ((tablero->tableroLleno()) || (turnosSaltados == 2)) {
    return true;
  }

  return false;
}

bool Reversi::realizarJugada(coordenada posicion, int jugador) { //aplica movimiento del jugador al tablero
  posicion.valor = jugador;

  if (((tablero->getPosicion(posicion) == 3) &&
       (tablero->getPosicion(posicion))) &&
      (chequearCercanias(posicion, jugador))) {
    turnosSaltados = 0;

    marcarVecinos(posicion, jugador);
    tablero->agregarFicha(posicion);
    tablero->guardarFichaJugada(posicion);
    return true;

  } else

  return false;
}

int Reversi::getGanador() {
  int fichas1 = tablero->getConteoDeFichas(1);
  int fichas2 = tablero->getConteoDeFichas(2);

  if (fichas1 > fichas2)
    return 1;
  else if (fichas1 < fichas2) {
    return 2;
  }
  return 0;
}

void Reversi::capturarFicha(coordenada posicion, int jugador) { //Modifica las fichas en el tablero
  tablero->agregarFicha(posicion);
  tablero->modificarFichaEnJuego(posicion);
}

bool Reversi::agregarPosicionesSugeridas(int jugador) {    //Agrega al tablero los movimientos disponibles para un jugador
  std::vector<coordenada> fichas = tablero->getFichasEnJuego();

  for (auto i : fichas) {
    if (i.valor == jugador) {
      buscarPosicionesDisponibles(jugador, i);
    }
  }
  return false;
}

void Reversi::buscarPosicionesDisponibles(int jugador, coordenada ficha) {//Revisa en las adyacencias de una ficha
                                                                          //y marca en el tablero las jugadas posibles
  for (int i = 0; i < 8; i++) {
    coordenada posicionVecina = ficha;

    posicionVecina.x += ruta[i].x;
    posicionVecina.y += ruta[i].y;

    if (!fueraDeRango(posicionVecina)) {
      if ((tablero->getPosicion(posicionVecina) == siguienteJugador(jugador)))
        marcarPosicionDisponible(ruta[i], ficha);
    }
  }
}

void Reversi::marcarPosicionDisponible(coordenada sentido,coordenada posicionPrevia) {//Revisa en una dirección la
  bool chequeo = false;                                                               //posible jugada y la marca
  while (true) {
    if (tablero->getPosicion(posicionPrevia) == 0) {
      break;
    }

    if (tablero->getPosicion(posicionPrevia) == tablero->getJugadorContrario(posicionPrevia.valor))
      chequeo = true;

    else chequeo = false;

    posicionPrevia.x += sentido.x;
    posicionPrevia.y += sentido.y;

    if (fueraDeRango(posicionPrevia)) {
      chequeo = false;
      break;
    }
  }

  if (chequeo) {
    posicionPrevia.valor = 3;
    tablero->agregarFicha(posicionPrevia);
  }
}

bool Reversi::saltarTurno(int turno) {
  if (tablero->getJugadasPosibles() == 0) {
    turnosSaltados++;
    return true;
  }
  return false;
}

void Reversi::setTablero(Tablero *t) { tablero = t; }

void Reversi::refrescarSugerencias(int jugadorActual) { //Limpia movimientos disponibles del jugador
  tablero->limpiarSugerencias();                        //anterior y agrega los del actual
  agregarPosicionesSugeridas(jugadorActual);
  tablero->contarJugadasPosibles();
}
