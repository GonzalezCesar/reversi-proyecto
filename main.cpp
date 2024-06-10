#include "include/cpu.hpp"
#include "include/interfaz.hpp"
#include "include/jugador.hpp"
#include "include/reversi.hpp"
#include <iostream>
#include <unistd.h>

using std::cout;
using std::endl;
using std::string;

void jugadorVSjugador(Interfaz i, Reversi juego, Jugador jugador[2]);

void jugadorVScpu(Interfaz i, Reversi juego, Jugador jugador);

void cpuVScpu(Interfaz i, Reversi juego);

int main() {

  Interfaz i;
  int opcion;

  while (opcion != 4) {
    system("cls");
    i.mainMenu();
    opcion = i.getMenuInput(4);
    Reversi juego;

    switch (opcion) {
    case 1: {
      system("cls");
      Jugador jugador[2];
      for (int j = 0; j < 2; j++) {
        cout << "Nombre del jugador " << j + 1 << " ";
        jugador[j].setNombre(i.inputNombre());
      }
      jugadorVSjugador(i, juego, jugador);
      break;
    }
    case 2: {
      system("cls");
      Jugador jugador;
      cout << "Nombre de jugador ";
      jugador.setNombre(i.inputNombre());
      jugadorVScpu(i, juego, jugador);
      break;
    }
    case 3:
      cpuVScpu(i, juego);
      break;
    }
  }
}




//----------------------------------------------------- CPU VS CPU
void cpuVScpu(Interfaz i, Reversi juego) {
  int jugadorActual = 0;
  Cpu cpu[2];
  cpu[0].setTurno(1);
  cpu[1].setTurno(2);
  Tablero t;
  cpu[0].setTablero(&t);
  cpu[1].setTablero(&t);
  juego.setTablero(&t);
  juego.iniciarJuego();

  while (!juego.gameOver()) {

    system("cls");
    juego.refrescarSugerencias(jugadorActual + 1);
    if (t.getJugadasPosibles() == 0)
      i.avisoTurnoSaltado(jugadorActual + 1);

    while (!juego.saltarTurno(jugadorActual + 1)) {
      // system("cls");
      i.printTablero(t.getTablero(), jugadorActual + 1);
      cpu[jugadorActual].setJugadaAleatoria();
      juego.realizarJugada(cpu[jugadorActual].getJugada(), jugadorActual + 1);

      i.printJugadorActual(jugadorActual + 1, "CPU");
      i.printJugadaCPU(jugadorActual + 1, cpu[jugadorActual].getJugada());
      break;
    }
    getchar();
    jugadorActual = juego.siguienteJugador(jugadorActual + 1) - 1;
  }
  int ganador = juego.getGanador();

  system("cls");
  i.printTablero(t.getTablero(), 1);
  i.anunciarGanador(ganador, "CPU", t.getConteoDeFichas(ganador));
}

//----------------------------------------------------- JUGADOR VS CPU
void jugadorVScpu(Interfaz i, Reversi juego, Jugador jugador) {
  int jugadorActual = 1; // No hace falta iniciar en 0
  Cpu cpu;
  Tablero t;
  cpu.setTablero(&t);
  juego.setTablero(&t);
  juego.iniciarJuego();
  while (!juego.gameOver()) {

    system("cls");
    juego.refrescarSugerencias(jugadorActual);

    if (t.getJugadasPosibles() == 0)
      i.avisoTurnoSaltado(jugadorActual);

    while (!juego.saltarTurno(jugadorActual)) {
      system("cls");
      i.printTablero(t.getTablero(), jugadorActual);

      if (jugadorActual == 1) {
        i.printJugadorActual(1, jugador.getNombre());

        if (juego.realizarJugada(i.obtenerPosicion(), jugadorActual))
          break;
        else {
        }
        i.movimientoEquivocado();
      } else if (jugadorActual == 2) {
        cpu.setJugadaAleatoria();
        juego.realizarJugada(cpu.getJugada(), jugadorActual);
        i.printJugadorActual(2, "CPU");
        i.printJugadaCPU(2, cpu.getJugada());
        getchar();
        break;
      }
    }
    jugadorActual = juego.siguienteJugador(jugadorActual);
  }
  int ganador = juego.getGanador();

  system("cls");
  i.printTablero(t.getTablero(), 1);

  if (ganador == 1)
    i.anunciarGanador(ganador, jugador.getNombre(),
                      t.getConteoDeFichas(ganador));
  else if (ganador == 2)
    i.anunciarGanador(ganador, "CPU", t.getConteoDeFichas(ganador));
}
//----------------------------------------------------- JUGADOR VS JUGADOR
void jugadorVSjugador(Interfaz i, Reversi juego, Jugador jugador[2]) {

  int jugadorActual = 0;
  Tablero t;
  juego.setTablero(&t);
  juego.iniciarJuego();

  while (!juego.gameOver()) {

    system("cls");
    juego.refrescarSugerencias(jugadorActual + 1);
    if (t.getJugadasPosibles() == 0)
      i.avisoTurnoSaltado(jugadorActual + 1);

    while (!juego.saltarTurno(jugadorActual + 1)) {
      system("cls");
      i.printTablero(t.getTablero(), jugadorActual + 1);
      i.printJugadorActual(jugadorActual + 1,
                           jugador[jugadorActual].getNombre());
      if (juego.realizarJugada(i.obtenerPosicion(), jugadorActual + 1))
        break;
      else
        i.movimientoEquivocado();
    }
    jugadorActual = juego.siguienteJugador(jugadorActual + 1) - 1;
  }
  int ganador = juego.getGanador();

  system("cls");
  i.printTablero(t.getTablero(), 1);
  i.anunciarGanador(ganador, jugador[ganador - 1].getNombre(),
                    t.getConteoDeFichas(ganador));
}

