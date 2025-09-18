#include "../include/pilaJugador.h"

struct rep_pilaJugador {
  TJugador jugador;
  rep_pilaJugador * sig;
  int cantidad;
};

TPilaJugador crearTPilaJugador() {
  TPilaJugador nuevaPilaJugador = new rep_pilaJugador;
  nuevaPilaJugador->jugador = NULL;
  nuevaPilaJugador->sig = NULL;
  nuevaPilaJugador->cantidad = 0;
  return nuevaPilaJugador;
}

void liberarTPilaJugador(TPilaJugador &p) {
  TPilaJugador actual = p;
  TPilaJugador siguiente;

  if(p->jugador != NULL){
    while(actual != NULL && cantidadEnTPilaJugador(p) > 0){
      siguiente = actual->sig;
      liberarTJugador(actual->jugador);
      //delete actual;
      actual = siguiente;
    }
  }
  delete p;
  p = NULL;
}

nat cantidadEnTPilaJugador(TPilaJugador p) { 
  return p ? p->cantidad : 0;
}

void apilarEnTPilaJugador(TPilaJugador &p, TJugador jugador) {
  TPilaJugador nuevaPilaJugador = crearTPilaJugador();

  if(p->jugador != NULL){
    nuevaPilaJugador->cantidad = p->cantidad + 1;
  }else{
    nuevaPilaJugador->cantidad = 1;
  }
  nuevaPilaJugador->jugador = copiarTJugador(jugador);
  nuevaPilaJugador->sig = p;

  p = nuevaPilaJugador;
}

TJugador cimaDeTPilaJugador(TPilaJugador p) { 
  return p->jugador;
}

void desapilarDeTPilaJugador(TPilaJugador &p) {
  if (cantidadEnTPilaJugador(p) == 1){
    p->cantidad = 0;
  }

  TPilaJugador aux = p;
  p = p->sig;

  liberarTJugador(aux->jugador);
  delete aux;
  aux = NULL;
}
