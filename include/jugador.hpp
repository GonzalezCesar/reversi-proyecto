
#ifndef JUGADOR
#define JUGADOR

#include "coordenada.hpp"
#include <iostream>

class Jugador {
private:
  std::string nombre;
  int turno;
  coordenada fichas[64]; // remover //remover
  int posicionActual = 0;

public:
  Jugador();

  void setTurno(int n);
  void setNombre(std::string);
  void agregarFicha(coordenada posicion);

  std::string getNombre();
  int getTurno();
  coordenada *getFichas();
};

#endif
