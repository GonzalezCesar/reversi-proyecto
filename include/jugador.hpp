
#ifndef JUGADOR
#define JUGADOR

#include "coordenada.hpp"
#include <iostream>

class Jugador {
private:
  std::string nombre;
  int turno;
  int posicionActual = 0;

public:
  Jugador();
  void setTurno(int n);
  void setNombre(std::string);
  std::string getNombre();
  int getTurno();
};

#endif
