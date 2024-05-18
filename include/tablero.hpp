
#ifndef TABLERO
#define TABLERO

#include "coordenada.hpp"
#include <vector>

class Tablero {
private:
  int capacidad = 64;
  int tablero[8][8];
  std::vector<coordenada> fichasEnJuego;
  int conteoDeFichas[2];
  int jugadasPosibles;

public:
  Tablero();

  bool tableroLleno();

  void agregarFicha(coordenada p);

  int (*(getTablero)())[8];

  int getPosicion(coordenada p);

  void mostrarTablero(int jugador); //(1)

  void mostrarInformacionCorrespondiente(int jugador, int posicion); //(1)

  int getCapacidad();

  std::vector<coordenada> getFichasEnJuego();

  void modificarFichaEnJuego(coordenada ficha);

  void guardarFichaJugada(coordenada p);

  void disminuirFichasJugador(int jugador);

  bool coordenadasIguales(coordenada p1, coordenada p2);

  int getJugadorContrario(int jugador);

  int getConteoDeFichas(int jugador);

  void printFichasEnJuego(); // remover al implementar interfaz (1)

  void limpiarSugerencias(); //(1)

  void printSugerencias(std::vector<coordenada> sugerencias); //(1)

  int getJugadasPosibles();
};

#endif
