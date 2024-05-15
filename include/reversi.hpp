#ifndef REVERSI
#define REVERSI

#include "coordenada.hpp"
#include "jugador.hpp"
#include "tablero.hpp"

class Reversi {
private:
  coordenada fichasEnJuego[64];
  int conteoDeFichas[2];
  int ultimaFicha;

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

  // bool chequearCercanias2(coordenada posicion, int jugador);

  void printTablero(int jugador);

  void iniciarJuego();

  void agregarFichaJugador(coordenada ficha);

  coordenada *buscarJugadas(Jugador j);

  bool gameOver();
  bool realizarJugada(int jugador);
  void autoJugada(coordenada input, int jugador);
  int getFichasEnTablero(int jugador);
  int getGanador();
  void anunciarGanador(Jugador p1, Jugador p2);
};

#endif
