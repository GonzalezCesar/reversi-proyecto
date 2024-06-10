
#ifndef CPU
#define CPU

#include "coordenada.hpp"
#include "tablero.hpp"

class Cpu {
private:
  coordenada jugada;
  int turno;
  Tablero *tablero;

public:
  Cpu();

  coordenada getJugada();

  void setMejorJugada();

  void setJugadaAleatoria();

  void setTablero(Tablero *t);

  coordenada evaluarJugadas(coordenada ficha);

  coordenada obtenerPosicion(coordenada sentido, coordenada posicionPrevia);

  bool fueraDeRango(coordenada p);

  void setTurno(int n);
};
#endif
