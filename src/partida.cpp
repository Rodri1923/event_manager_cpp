#include "../include/partida.h"

struct rep_partida {
    TJugada jugada ;
    rep_partida * sig;
};

TPartida crearTPartida(){
    TPartida nuevaPartida = NULL;
    return nuevaPartida;
}

void agregarEnTPartida(TPartida& partida, TJugada jugada){
    //Si la partida no tiene jugadas.
    if(partida == NULL){
        partida = new rep_partida;
        partida->jugada = jugada;
        partida->sig = NULL;
    }else{
    //Si la partida tiene jugadas => busco la posicion donde tengo que colocar la jugada.
        TPartida actual = partida;
        TPartida anterior = NULL;

        while(actual != NULL && numeroTJugada(jugada) > numeroTJugada(actual->jugada)){
            anterior = actual;
            actual = actual->sig;
        }
    //Meto el nodo partida en la lista.
        TPartida nuevaPartida = new rep_partida;
        nuevaPartida->jugada = jugada;
        nuevaPartida->sig = actual;
        if (anterior == NULL){
            partida = nuevaPartida;
        }else {
            anterior->sig = nuevaPartida;
        }
    }
}

void imprimirTPartida(TPartida partida){
    TPartida actual = partida;
    while(actual != NULL){
        imprimirTJugada(actual->jugada);
        actual = actual->sig;
    }
}

void liberarTPartida(TPartida& partida){
    TPartida actual = partida;
    TPartida siguiente;
    
    if(partida != NULL && partida->jugada != NULL){
        while (actual != NULL){
            siguiente = actual->sig;
            liberarTJugada(actual->jugada);
            delete actual;
            actual = siguiente;
        }
    }
    partida = NULL;
    
}

bool esVaciaTPartida(TPartida partida){
    return partida == NULL;
}

TPartida copiarTPartida(TPartida partida){
    TPartida nuevaPartida = crearTPartida();
    TPartida nuevaPActual = nuevaPartida;
    TPartida actual = partida;

    while(actual != NULL){
        if(nuevaPartida == NULL){
            nuevaPartida = new rep_partida;
            nuevaPartida->jugada = copiarTJugada(actual->jugada);
            nuevaPartida->sig = NULL;
            actual = actual->sig;
            nuevaPActual = nuevaPartida;
        }else{
            TPartida nuevoNodo = new rep_partida;
            nuevoNodo->jugada = copiarTJugada(actual->jugada);
            nuevoNodo->sig = NULL;
            nuevaPActual->sig = nuevoNodo;
            nuevaPActual = nuevoNodo;
            actual = actual->sig;
        }
    }

    return nuevaPartida;
}

bool estaEnTPartida(TPartida partida, int numeroDeJugada){
    bool tuki = false;
    TPartida actual = partida;
    while(actual != NULL && numeroDeJugada != numeroTJugada(actual->jugada)){
        actual = actual->sig;
    }
    if(actual == NULL){
        return tuki;
    }else{
        tuki = true;
        return tuki;
    }
}

TJugada obtenerDeTPartida(TPartida partida, int numeroDeJugada){
    TPartida actual = partida;
    TJugada objetivo = NULL;

    while(actual != NULL && numeroDeJugada != numeroTJugada(actual->jugada)){
        actual = actual->sig;
    }
    if(numeroDeJugada == numeroTJugada(actual->jugada)){
        objetivo = actual->jugada;
        return objetivo;
    }else{
        return NULL;
    }
}

void imprimirJugadasConMovimiento(TPartida partida, int pos, Movimiento mov){
    TPartida actual = partida;
    while(actual != NULL){
        if(tieneMovimientoEnPosTJugada(actual->jugada, pos, mov)){
            imprimirTJugada(actual->jugada);
        }
        actual = actual->sig;
    }
}

void removerDeTPartida(TPartida& partida, int numeroDeJugada){
    TPartida actual = partida;
    TPartida anterior = NULL;

    while(actual != NULL && numeroTJugada(actual->jugada) != numeroDeJugada){
        anterior = actual;
        actual = actual->sig;
    }

    if(actual != NULL){
        // Se encontró el evento con el id dado
        if(anterior == NULL){
            // El evento a eliminar es el primer nodo de la lista
            partida = actual->sig;
        }else{
            anterior->sig = actual->sig;
        }

        // Se libera la memoria del nodo eliminado
        liberarTJugada(actual->jugada);
        delete actual;
    }
}