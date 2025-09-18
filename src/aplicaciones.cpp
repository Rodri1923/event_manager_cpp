#include "../include/aplicaciones.h"
#include "../include/colaDePrioridadJugador.h"

void listarEnOrden(TTablaJugadores t, char** nombres, nat n){
    TColaDePrioridadJugador cp = crearCP(MAX_ID);

    for(nat i = 0; i < n; i++){//Recorro el arreglo con los nombres
        //Si el jugador con ese nombre esta en la tabla no agrego a la cp
        if(perteneceATTablaJugadores(t, nombres[i])){
            insertarEnCP(copiarTJugador(obtenerJugadorDeTTablaJugadores(t,nombres[i])), cp);
        }
    }

    while(!estaVaciaCP(cp)){//Imprimo el prioritario y borro el prioritario mientras no sea vacia
        imprimirTJugador(prioritario(cp));
        eliminarPrioritario(cp);
    }
    liberarCP(cp);
}