#include "../include/jugador.hpp"

Jugador::Jugador() {}
std::string Jugador::getNombre() { return nombre; }
int Jugador::getTurno() { return turno; }
coordenada *Jugador::getFichas() { return fichas; }

void Jugador::setTurno(int n) { turno = n; }
void Jugador::setNombre(std::string n) { nombre = n; }
void Jugador::agregarFicha(coordenada posicion) {
  fichas[posicionActual] = posicion;
  posicionActual++;
}
