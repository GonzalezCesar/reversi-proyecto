#include "coordenada.hpp"
#include <iostream>
#include <vector>
#ifndef INTERFAZ
#define INTERFAZ

class Interfaz {
public:
  Interfaz();
  void mainMenu();

  void printTablero(int tablero[8][8], int jugador);

  coordenada obtenerPosicion();

  int getMenuInput(int range);

  bool validarInput(std::string input);

  void simboloCorrespondiente(int jugador, int posicion);

  void printSugerencias(std::vector<coordenada> sugerencias);

  void movimientoEquivocado();

  void avisoTurnoSaltado(int turno);

  void anunciarGanador(int jugador, std::string playerName, int conteoDeFichas);

  void printCoordenada(coordenada p, int color);

  void printJugadaCPU(int turno, coordenada p);

  std::string inputNombre();

  void printJugadorActual(int turno, std::string nombre);
};

#endif
