#include <iostream>
#include <unistd.h>

using std::cout;
using std::endl;
using std::string;
using std::cin;

struct coordenada{
  int x=0;
  int y=0;
};

int tablero[8][8];

coordenada ruta[]={{-1, 0}, {-1,-1}, {0,-1}, {1,-1},
                  {-1, 1},  {1,0},   {1,1},  {0,1}};

bool revisarLinea(coordenada sentido, coordenada posicionPrevia, int jugador);

int siguienteJugador(int jugadorActual){

  if(jugadorActual==1) return 2;
  else return 1;

}

void printTablero(){
  cout<<"    1  2  3  4  5  6  7  8"<<endl;
  cout<<"    ‾  ‾  ‾  ‾  ‾  ‾  ‾  ‾"<<endl;

  for(int i=0; i<8;i++){
    cout<<i+1<<"|  ";

    for(int j=0; j<8; j++){

      if(tablero[i][j]==0) cout<<"."<<"  "; 
      else cout<<tablero[i][j]<<"  ";
    }
    cout<<endl;
  }
}


void marcarPosicion(coordenada p, int jugador){
  tablero[p.y-1][p.x-1]=jugador;
} 

bool fueraDeRango(coordenada p){ 
  if((p.x>8 || p.y>8)||(p.x<1 || p.y<1)) return true;
  return false;
  }
 

//Dibuja la línea hasta la coordenada con la otra ficha del jugador
int marcarLinea(coordenada sentido, coordenada posicionPrevia, int jugador){
  int posiciones=0;
  
  while (tablero[posicionPrevia.y-1][posicionPrevia.x-1]==siguienteJugador(jugador)){

    if (revisarLinea(sentido, posicionPrevia, jugador)){
      marcarPosicion(posicionPrevia, jugador);
      posiciones++;
    }
    posicionPrevia.x+=sentido.x;
    posicionPrevia.y+=sentido.y;

    if(fueraDeRango(posicionPrevia)) break;
  }
  return posiciones;
}

//Revisa una línea, si encuntra otra ficha del jugador en el trayecto devuelve verdadero
// de lo contrario devuelve falso
bool revisarLinea(coordenada sentido, coordenada posicionPrevia, int jugador){
 
  while (true){
    if(tablero[posicionPrevia.y-1][posicionPrevia.x-1]==jugador) return true;

    posicionPrevia.x+=sentido.x;
    posicionPrevia.y+=sentido.y;

    if(fueraDeRango(posicionPrevia)) break;
  }
  return false;
}

//Revisa los alrededores de la ficha para dibujar las líneas
// 
 bool marcarVecinos(coordenada posicion, int jugador){
  int chequeo=0;

  for(int i=0; i<8;i++){ 
    coordenada posicionVecina=posicion;
    posicionVecina.x+=ruta[i].x;
    posicionVecina.y+=ruta[i].y;

    if(!fueraDeRango(posicionVecina)){
      chequeo+=marcarLinea(ruta[i],posicionVecina,jugador);
    }

  }
  if(chequeo>0) return true;
  return false;
}

 bool chequearCercanias(coordenada posicion, int jugador){
  int chequeo=0;

  for(int i=0; i<8;i++){ 
    coordenada posicionVecina=posicion;

    posicionVecina.x+=ruta[i].x;
    posicionVecina.y+=ruta[i].y;

    if(!fueraDeRango(posicionVecina)){
        if(tablero[posicionVecina.y-1][posicionVecina.x-1]==siguienteJugador(jugador)) return true;
    }
  }
  return false;
}

int main(){
  tablero[4][3]=1;
  tablero[3][4]=1;
  tablero[3][3]=2;
  tablero[4][4]=2;



  char n;
  coordenada movimiento;

  system("clear");
  printTablero();

  while(true){

    for(int player=1; player<3; player++){

      while(true){
      
        cout<<"Player: "<<player<<"\nX coord >>: ";
        cin>>movimiento.x;
        cout<<"\nY coord >>: ";
        cin>>movimiento.y;
        if (chequearCercanias(movimiento, player)){
          marcarVecinos(movimiento, player);
          marcarPosicion(movimiento, player);
          break;
        }  
        system("clear");
        cout<<"\nMovimiento errado, vuelva a intentarlo"<<endl;
        printTablero();
      }
      system("clear");
      printTablero();

    }
    
  }

}
