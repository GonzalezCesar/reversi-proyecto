#ifndef REVERSI
#define REVERSI

#include "coordenada.hpp"
#include "jugador.hpp"
#include "tablero.hpp"

class Reversi {
  int turnosSaltados = 0;
  Tablero *tablero;

public:
  Reversi();
  bool revisarLinea(coordenada sentido, coordenada posicionPrevia, int jugador);

  int siguienteJugador(int jugadorActual); 

  void marcarPosicion(coordenada p, int jugador);

  bool fueraDeRango(coordenada p);

  void marcarLinea(coordenada sentido, coordenada posicionPrevia, int jugador);

  bool marcarVecinos(coordenada posicion, int jugador);

  bool chequearCercanias(coordenada posicion, int jugador);

  void iniciarJuego();

  bool gameOver();

  bool realizarJugada(coordenada posicion,int jugador); 

  int getGanador();

  void capturarFicha(coordenada posicion, int jugador);

  bool agregarPosicionesSugeridas(int jugador);

  void buscarPosicionesDisponibles(int jugador, coordenada ficha);

  void marcarPosicionDisponible(coordenada sentido, coordenada posicionPrevia);

  bool saltarTurno(int turno);

  void setTablero(Tablero *t);

  void refrescarSugerencias(int jugadorActual);
};
#endif
