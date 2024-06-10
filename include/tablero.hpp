
#ifndef TABLERO
#define TABLERO

#include "coordenada.hpp"
#include <vector>

class Tablero {
private:
  int capacidad = 60;
  int tablero[8][8];
  std::vector<coordenada> fichasEnJuego;
  int conteoDeFichas[2];
  int jugadasPosibles = 0;

public:
  Tablero();

  bool tableroLleno();

  void agregarFicha(coordenada p); 

  int (*(getTablero)())[8];

  int getPosicion(coordenada p); 
                                 
  int getCapacidad();

  std::vector<coordenada> getFichasEnJuego();

  void modificarFichaEnJuego(coordenada ficha);

  void guardarFichaJugada(coordenada p);

  void disminuirFichasJugador(int jugador);

  bool coordenadasIguales(coordenada p1, coordenada p2);

  int getJugadorContrario(int jugador); 

  int getConteoDeFichas(int jugador);

  void limpiarSugerencias(); 

  int getJugadasPosibles();

  void contarJugadasPosibles();
};

#endif

