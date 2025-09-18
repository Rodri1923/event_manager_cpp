#include "../include/jugada.h"

// Define la estructura Jugada
struct rep_jugada {
    int nJugada;
    Movimiento* movimientos;    //Puntero a un arreglo dinámico de movimientos
};

// Crea una jugada con los valores dados
TJugada crearTJugada(int numero, Movimiento mov1, Movimiento mov2, Movimiento mov3, Movimiento mov4){
    TJugada nuevaJugada = new rep_jugada;

    if (nuevaJugada != NULL){
        nuevaJugada->nJugada = numero;
        nuevaJugada->movimientos = new Movimiento[4];
    }if(nuevaJugada->movimientos != NULL){
        nuevaJugada->movimientos[0] = mov1;
        nuevaJugada->movimientos[1] = mov2;
        nuevaJugada->movimientos[2] = mov3;
        nuevaJugada->movimientos[3] = mov4;
    }else{
        //Por si ocurre algun error en la asignacion de memoria
        delete nuevaJugada;
        nuevaJugada = NULL;
    }

    return nuevaJugada;
}

// Función que retorna el numero de la jugada
int numeroTJugada(TJugada jugada){
    return jugada->nJugada;
}

// Función que retorna los movimientos de una jugada
Movimiento * movimientoTJugada(TJugada jugada) {
    if(jugada != NULL && jugada->movimientos != NULL){
        return jugada->movimientos;
    }
    return NULL;
}

// Devuelve true si y solo si la jugada tiene el movimiento mov en la posicion pos
bool tieneMovimientoEnPosTJugada(TJugada jugada, int pos, Movimiento mov){
    return jugada->movimientos[pos-1] == mov;
}

// Imprime la jugada
void imprimirTJugada(TJugada jugada) {
    // Jugada: <numeroDeJugada>
    // Movimientos: <mov1> <mov2> <mov3> <mov4>
    printf("Jugada: %d \n", jugada->nJugada);
    printf("Movimientos: ");
    for(int i = 0; i < 4; i++){
        switch(jugada->movimientos[i]){
        case Derecha:
            printf("Derecha ");
            break;
        case Izquierda:
            printf("Izquierda ");
            break;
        case Arriba:
            printf("Arriba ");
            break;
        case Abajo:
            printf("Abajo ");
            break;
        }
    }
    printf("\n");
}

// Libera la memoria asignada para un jugada
void liberarTJugada(TJugada &jugada) {
    delete[] jugada->movimientos;
    delete jugada;
    jugada = NULL;
}

// Retorna una copia de la jugada
TJugada copiarTJugada(TJugada jugada) {
    int nJugada = jugada->nJugada;
    
    TJugada nuevaJugada = crearTJugada(nJugada, jugada->movimientos[0], jugada->movimientos[1], jugada->movimientos[2], jugada->movimientos[3]);
    
    return nuevaJugada;
}