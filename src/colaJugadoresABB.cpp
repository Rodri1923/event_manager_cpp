#include "../include/colaJugadoresABB.h"
#include "../include/jugadoresLDE.h"

struct nodoCola {
  TJugadoresABB jugadorABB;
  nodoCola* siguiente;
};
typedef struct nodoCola *TColaJugadoresABBAux;

struct rep_colaJugadoresABB {
  nodoCola * primero;
  nodoCola * ultimo;
  nat cantidad = 0;
};

TColaJugadoresABB crearTColaJugadoresABB() {
  TColaJugadoresABB nuevaColaJugadores = new rep_colaJugadoresABB;
  nuevaColaJugadores->primero = NULL;
  nuevaColaJugadores->ultimo = NULL;
  return nuevaColaJugadores;
}

void liberarTColaJugadoresABB(TColaJugadoresABB &c) {
  while (c->primero != NULL) {
    TColaJugadoresABBAux temp = c->primero;
    c->primero = c->primero->siguiente;
    delete temp;
  }
  delete c;
  c = nullptr;
}

nat cantidadEnTColaJugadoresABB(TColaJugadoresABB c) { 
  return c->cantidad;
}

void encolarEnTColaJugadoresABB(TJugadoresABB t, TColaJugadoresABB &c) {
  if (c->primero == NULL){//la cola no tiene elementos
    TColaJugadoresABBAux nuevoNodo = new nodoCola;
    nuevoNodo->jugadorABB = t;
    nuevoNodo->siguiente = NULL;

    c->primero = nuevoNodo;
    c->ultimo = nuevoNodo;
  }else{
    TColaJugadoresABBAux nuevoNodo = new nodoCola;
    nuevoNodo->jugadorABB = t;
    nuevoNodo->siguiente = NULL;

    c->ultimo->siguiente = nuevoNodo;

    c->ultimo = nuevoNodo;
  }
  c->cantidad = c->cantidad + 1;
}

TJugadoresABB frenteDeTColaJugadoresABB(TColaJugadoresABB c) { 
  return c->primero->jugadorABB;
}

void desencolarDeTColaJugadoresABB(TColaJugadoresABB &c) {
  if (c->primero != NULL) {
    TColaJugadoresABBAux temp = c->primero;
    c->primero = c->primero->siguiente;
    delete temp;
    if (c->primero == NULL) {
      c->ultimo = NULL;
    }
  }
  c->cantidad = c->cantidad - 1;
}
