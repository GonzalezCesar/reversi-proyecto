
#ifndef TABLERO
#define TABLERO

#include "coordenada.hpp"

class Tablero {
private:
  int capacidad = 64;
  int tablero[8][8];

public:
  Tablero();
  bool tableroLleno();
  void agregarFicha(coordenada p);
  int (*(getTablero)())[8];
  int getPosicion(coordenada p);
  void mostrarTablero(int jugador);
  void mostrarInformacionCorrespondiente(int jugador, int posicion);
  int getCapacidad();
};

#endif
