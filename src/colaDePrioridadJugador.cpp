/*
  Módulo de implementación de `TColaDePrioridadJugador`.


  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#include "../include/colaDePrioridadJugador.h"
#include "../include/utils.h"


#include <assert.h>
#include <stdlib.h>
//#include <string.h>

struct rep_nodoHeap{
  TJugador jugador;
  nat prioridad;  //Igual a la edad
};
typedef rep_nodoHeap* TNodoHeap;

struct rep_colaDePrioridadJugador {
  TNodoHeap * arreglo;    //Arreglo de punteros heap
  TNodoHeap * arregloIDs; //Arreglo de punteros ubicados por id
  nat capacidad;  //Capacidad maxima
  nat tope;
  bool invertida;
};

//Funcion auxiliar para cambiar la posicion de dos nodos entre si
void swapNodos(nat pos1, nat pos2, TColaDePrioridadJugador cp){
  TNodoHeap temp = cp->arreglo[pos1];     //Copio el puntero al nodo en la pos1
  cp->arreglo[pos1] = cp->arreglo[pos2];  //Pongo al nodo pos2 en pos1
  cp->arreglo[pos2] = temp;               //En pos2 ahora pongo el nodo que estaba en pos1
}

//Funcion auxiliar para hacer un filtrado ascendente desde una posicion
void filtrado_ascendente(nat pos, TColaDePrioridadJugador &cp){
  nat posPadre = pos / 2; //La posicion del padre del nodo va a ser la parte entera de dividir la pos entre 2

if(cp->invertida){  //----------------------Si esta invertida-------------------------------

  //Mientras que la posicion del hijo no sea la raiz (porque no puedo ir mas arriba)
  //y que el padre no tenga menor prioridad (porque si el padre es menor esta ordenado, no tengo que swapear)
  while(pos > 1 && cp->arreglo[posPadre]->prioridad < cp->arreglo[pos]->prioridad){
    swapNodos(pos, posPadre, cp);
    pos = posPadre;
    posPadre = pos / 2;
  }

}else{  //----------------------Si NO esta invertida-------------------------------

  //Mientras que la posicion del hijo no sea la raiz (porque no puedo ir mas arriba)
  //y que el padre no tenga menor prioridad (porque si el padre es menor esta ordenado, no tengo que swapear)
  while(pos > 1 && cp->arreglo[posPadre]->prioridad > cp->arreglo[pos]->prioridad){
    swapNodos(pos, posPadre, cp);
    pos = posPadre;
    posPadre = pos / 2;
  }

}

}

//Funcion auxiliar para hacer un filtrado decendente desde una posicion
void filtrado_descendente(nat pos, TColaDePrioridadJugador &cp){
  nat posHijo = pos * 2;
  while (posHijo < cp->tope) { //Mientras haya al menos un hijo izquierdo

    if(cp->invertida){  //----------------------Si esta invertida-------------------------------

      //Si hay un hijo derecho y tiene menor prioridad que el izquierdo, selecciono el hijo derecho
      if (posHijo + 1 < cp->tope && cp->arreglo[posHijo + 1]->prioridad > cp->arreglo[posHijo]->prioridad) {
        posHijo = posHijo + 1;
      }

      //Si la prioridad del hijo es menor que la del padre swapeo
      if (cp->arreglo[posHijo]->prioridad > cp->arreglo[pos]->prioridad) {
        swapNodos(pos, posHijo, cp);
        pos = posHijo;
        posHijo = 2 * pos; //Actualizo la posicion del hijo izquierdo para la siguiente iteracion
      } else {
        break; //Si el hijo tiene mayor o igual prioridad, termino el bucle
      }     

    }else{  //----------------------Si NO esta invertida-------------------------------

      //Si hay un hijo derecho y tiene menor prioridad que el izquierdo, selecciono el hijo derecho
      if (posHijo + 1 < cp->tope && cp->arreglo[posHijo + 1]->prioridad < cp->arreglo[posHijo]->prioridad) {
        posHijo = posHijo + 1;
      }

      //Si la prioridad del hijo es menor que la del padre swapeo
      if (cp->arreglo[posHijo]->prioridad < cp->arreglo[pos]->prioridad) {
        swapNodos(pos, posHijo, cp);
        pos = posHijo;
        posHijo = 2 * pos; //Actualizo la posicion del hijo izquierdo para la siguiente iteracion
      } else {
        break; //Si el hijo tiene mayor o igual prioridad, termino el bucle
      }

    }
  }
}

TColaDePrioridadJugador crearCP(nat N) {
  TColaDePrioridadJugador cp = new rep_colaDePrioridadJugador;
  cp->arreglo = new TNodoHeap[N+1];
  cp->arregloIDs = new TNodoHeap[N+1];

  for(nat i = 0; i <= N; i++){
    cp->arreglo[i] = NULL;
    cp->arregloIDs[i] = NULL;
  }

  cp->invertida = false;
  cp->capacidad = N+1;
  cp->tope = 1;

  return cp;

} // crearCP

void invertirPrioridad(TColaDePrioridadJugador &cp) {
  if(cp->tope == 1){
    //Cambio el estado de si esta invertida
    cp->invertida = !cp->invertida;
    return;
  }else{
    cp->invertida = !cp->invertida;
    for(nat i = cp->tope - 1; i > cp->tope /2; i--){
      filtrado_ascendente(i, cp);
    }
  }
}

void liberarCP(TColaDePrioridadJugador &cp) {

  for(nat i = 1; i < cp->tope; i++){
    liberarTJugador(cp->arreglo[i]->jugador);
    delete cp->arreglo[i];
  }

  delete[] cp->arreglo;

  delete[] cp->arregloIDs;

  delete cp;

} // liberarCP


void insertarEnCP(TJugador jugador, TColaDePrioridadJugador &cp) {
  // Si el arreglo está lleno, no hago nada
  if (cp->tope < cp->capacidad) {
    // Creo el nodo a insertar
    TNodoHeap nuevoNodo = new rep_nodoHeap;
    nuevoNodo->jugador = jugador;
    nuevoNodo->prioridad = edadTJugador(jugador);



    // Agrego el nuevoNodo al final del arreglo
    cp->arreglo[cp->tope] = nuevoNodo;

    // Corro el tope 1
    cp->tope = cp->tope + 1;

    // Agrego el nodo al arreglo de IDs
    cp->arregloIDs[idTJugador(jugador)] = nuevoNodo;

    // Corro un filtrado ascendente para ir swapeando hasta donde tenga que quedar el nodo
    filtrado_ascendente((cp->tope - 1), cp);

  }
} // insertarEnCP

bool estaVaciaCP(TColaDePrioridadJugador cp) {
  return cp->tope == 1;
} // estaVacioCP

TJugador prioritario(TColaDePrioridadJugador cp) {
  if(cp->tope > 1){
    return cp->arreglo[1]->jugador;
  }else{
    //Si el tope NO es mayor a 1 es que no hay jugadores en el heap
    return NULL;
  }
} // prioritario

void eliminarPrioritario(TColaDePrioridadJugador &cp) {
  if(cp->tope > 2){
    cp->arregloIDs[idTJugador(cp->arreglo[1]->jugador)] = NULL; //Saco el nodo del arreglo IDs
    liberarTJugador(cp->arreglo[1]->jugador);                   //Libero la memoria del jugador del nodo prioritario
    delete cp->arreglo[1];
    cp->arreglo[1] = NULL;                                      //Pongo el prioritario como NULL
    swapNodos(1,(cp->tope - 1), cp);                            //Cambio el NULL en la pos 1 por el ultimo nodo del arreglo
    cp->tope = cp->tope - 1;                                    //Corro el tope 1 para atras
    filtrado_descendente(1, cp);                                //Hago un filtrado descendente desde la raiz
  }else if(cp->tope == 2){
    cp->arregloIDs[idTJugador(cp->arreglo[1]->jugador)] = NULL; //Saco el nodo del arreglo IDs
    liberarTJugador(cp->arreglo[1]->jugador);                   //Libero la memoria del jugador del nodo prioritario
    delete cp->arreglo[1];
    cp->arreglo[1] = NULL;                                      //Pongo el prioritario como NULL
    cp->tope = cp->tope - 1;                                    //Corro el tope 1 para atras
  }
} // eliminarPrioritario

bool estaEnCP(nat id, TColaDePrioridadJugador cp) {
  if(id > cp->capacidad - 1){
    return false;
  }else{
    return cp->arregloIDs[id] != NULL;
  }
} // estaEnCP

nat prioridad(nat id, TColaDePrioridadJugador cp){
  int x = cp->arregloIDs[id]->prioridad;
  return abs(x);
}