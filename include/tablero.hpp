
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
  int jugadasPosibles = 0;

public:
  Tablero();

  bool tableroLleno();

  void agregarFicha(coordenada p); // agrega ficha a la matriz

  int (*(getTablero)())[8];

  int getPosicion(coordenada p); // Devuelve el valor del la matriz en la
                                 // coordenada especificada

  void mostrarTablero(int jugador); //(1)

  void mostrarInformacionCorrespondiente(
      int jugador, int posicion); //(1) imprime los símbolso correspondientes a
                                  //los números en la matriz

  int getCapacidad();

  std::vector<coordenada> getFichasEnJuego(); // arreglo dinámico con las fichas

  void modificarFichaEnJuego(
      coordenada ficha); // modifica el arreglo dinámico con la información
                         // actualizada de las fichas

  void guardarFichaJugada(
      coordenada p); // agrega ficha al arreglo dinámico de fichas

  void disminuirFichasJugador(int jugador);

  bool coordenadasIguales(coordenada p1, coordenada p2);

  int getJugadorContrario(int jugador); //(1)

  int getConteoDeFichas(int jugador);

  void printFichasEnJuego(); // (1)

  void limpiarSugerencias(); //(1)

  void printSugerencias(std::vector<coordenada> sugerencias); //(1)

  int getJugadasPosibles();

  void testing(); //(1)

  void contarJugadasPosibles();
};

#endif

//(1): remover luego
