#include "../include/interfaz.hpp"
#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::vector;

Interfaz::Interfaz() {}

#define RED "\x1b[31m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define RESET "\x1b[0m"
#define GREEN "\x1B[32m"

void Interfaz::mainMenu() {
  cout << YELLOW << "### --- REVERSI --- ###" << RESET
       << "\n(1) - Jugador vs Jugador\n(2) - Jugador vs "
          "CPU\n(3) - CPU vs "
          "CPU\n(4) - Salir"
       << endl;
}

int Interfaz::getMenuInput(int range) {     //Entrada de datos numérica
  string input;
  cout << GREEN << ">>: " << RESET;
  getline(std::cin, input);
  if (!validarInput(input)) return 0;

  int inputOpcion = stoi(input);

  if ((inputOpcion) > 0 && (inputOpcion <= range)) {
    return stoi(input);
  } 

  else return 0;
}

bool Interfaz::validarInput(string input) { //Valida entra de datos numéricas
  if (input == "") return false;            //verdadero: solo hay números en el string dado
  for (auto i : input) {                    //falso:hay otros caracteres
    if (isalpha(i)) return false;
  }
  return true;
}

void Interfaz::printTablero(int tablero[8][8], int jugador) {
  cout << "    1  2  3  4  5  6  7  8" << endl;
  cout << "    |  |  |  |  |  |  |  |" << endl;

  for (int i = 0; i < 8; i++) {
    std::vector<coordenada> sugerencias;
    cout << i + 1 << "|  ";

    for (int j = 0; j < 8; j++) {
      simboloCorrespondiente(jugador, tablero[i][j]);
      if (tablero[i][j] == 3) {
        coordenada posicion{j + 1, i + 1, tablero[i][j]};
        sugerencias.push_back(posicion);
      }
    }
    printSugerencias(sugerencias);
    cout << endl;
  }
}

void Interfaz::simboloCorrespondiente(int jugador, int posicion) {//Cambia por caracteres las fichas en el tablero
  if (posicion == 3) printf(YELLOW "x  " RESET);                  //x: posible flanqueo
  else if (posicion == 0) cout << ".  ";                          //.: posición vacía
  else if (posicion == 1) printf(RED "o  " RESET);                //o: ficha de jugador
  else printf(BLUE "o  " RESET);
}

void Interfaz::printSugerencias(std::vector<coordenada> sugerencias) { //Imprime los posibles flanqueos
  if (sugerencias.size() >= 1) {
    cout << "  --> ";
    for (auto i : sugerencias) {
      printf(YELLOW "[%d, %d]" RESET, i.x, i.y);
    }
  }
}

coordenada Interfaz::obtenerPosicion() {//Entrada de datos para las coordenadas en el tablero

  coordenada jugada;

  cout << "Coordenada en x ";
  jugada.x = getMenuInput(8);
  cout << "Coordenada en y ";
  jugada.y = getMenuInput(8);

  return jugada;
}

void Interfaz::movimientoEquivocado() {
  printf(RED "\nMovimiento erroneo.\n" RESET);
  cout << "\nPresione enter para continuar";
  getchar();
}
void Interfaz::avisoTurnoSaltado(int turno) {
  printf(YELLOW "\nEl jugador %d no posee movimientos disponibles, su turno "
                "ha sido saltado\n" RESET,
         turno);
}

void Interfaz::anunciarGanador(int turno, string playerName, int conteoDefichas) {
  cout << "\nEl ganador es ";
  if (turno == 1) {
    cout << RED << playerName << " (" << turno << ")" << RESET << endl;
    cout << "Fichas capturadas: " << RED << conteoDefichas << RESET << endl;
  } else if (turno == 2) {
    cout << BLUE << playerName << " (" << turno << ")" << RESET << endl;
    cout << "Fichas capturadas: " << BLUE << conteoDefichas << RESET << endl;
  } else
    cout << "Empate!" << endl;

  cout << "\nPresione enter para continuar" << endl;
  getchar();
}

void Interfaz::printCoordenada(coordenada p, int color) {
  if (color == 0)
    cout << "(" << p.x << "," << p.y << ")";
  if (color == 1)
    cout << RED << "(" << p.x << "," << p.y << ")" << RESET;
  if (color == 2)
    cout << BLUE << "(" << p.x << "," << p.y << ")" << RESET;
}

void Interfaz::printJugadaCPU(int turno, coordenada p) {
  cout << "El ";
  if (turno == 1) {
    cout << RED "CPU(" << turno << ")" << RESET;
    cout << " ha tomado la posicion ";
    printCoordenada(p, turno);

  } else if (turno == 2) {
    cout << BLUE "CPU(" << turno << ")" << RESET;
    cout << " ha tomado la posicion ";
    printCoordenada(p, turno);
  }
  cout << "\nPresione enter para continuar.";
}

string Interfaz::inputNombre() {
  cout << GREEN << ">>: " << RESET;
  string nombre;
  getline(std::cin, nombre);
  return nombre;
}

void Interfaz::printJugadorActual(int turno, string nombre) {
  cout << "Turno: ";
  if (turno == 1) cout << RED << nombre << RESET << endl;
  else if (turno == 2) cout << BLUE << nombre << RESET << endl;
}
