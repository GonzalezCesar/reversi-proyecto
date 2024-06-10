#include "../include/jugador.hpp"

Jugador::Jugador() {}
std::string Jugador::getNombre() { return nombre; }
int Jugador::getTurno() { return turno; }
void Jugador::setTurno(int n) { turno = n; }
void Jugador::setNombre(std::string n) { nombre = n; }

