#ifndef REVERSI
#define REVERSI

#include "coordenada.hpp"
#include "jugador.hpp"
#include "tablero.hpp"

class Reversi {
  int turnosSaltados = 0;

public:
  Tablero tablero;
  Reversi();

  void removerFicha(int jugador);

  bool revisarLinea(coordenada sentido, coordenada posicionPrevia, int jugador);

  int siguienteJugador(int jugadorActual);

  void marcarPosicion(coordenada p, int jugador);

  bool fueraDeRango(coordenada p);

  void marcarLinea(coordenada sentido, coordenada posicionPrevia, int jugador);

  bool marcarVecinos(coordenada posicion, int jugador);

  bool chequearCercanias(coordenada posicion, int jugador);

  void printTablero(int jugador); // remover al añadir interfaz

  void iniciarJuego();

  bool gameOver();

  bool realizarJugada(int jugador); // remover al añadir interfaz

  void autoJugada(coordenada input, int jugador); // remover

  int getGanador();

  void anunciarGanador(Jugador p1, Jugador p2); // remover al añadir interfaz

  void capturarFicha(coordenada posicion, int jugador);

  bool agregarPosicionesSugeridas(int jugador);

  void buscarPosicionesDisponibles(int jugador, coordenada ficha);

  void marcarPosicionDisponible(coordenada sentido, coordenada posicionPrevia);

  void sinMovimientosDisponibles();

  bool saltarTurno(int turno);

  bool forzarGameOver();
};
#endif
