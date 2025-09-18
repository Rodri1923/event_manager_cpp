#include "../include/jugadoresLDE.h"


struct rep_jugadoresAux {
    // Elementos almacenados en el nodo
    TJugador jugador;
    TFecha fecha;
    // Puntero al siguiente nodo de la lista
    rep_jugadoresAux* siguiente;
    // Puntero al nodo anterior de la lista
    rep_jugadoresAux* anterior;
};
typedef struct rep_jugadoresAux *TJugadoresAux;

struct rep_jugadoresLDE {
    // Puntero al primer nodo de la lista
    rep_jugadoresAux* primero;
    // Puntero al último nodo de la lista
    rep_jugadoresAux* ultimo;
    //Cantidad de elementos en la lista
    nat cantidad = 0;
};

TJugadoresLDE crearTJugadoresLDE(){
    TJugadoresLDE jugadorLDE = new rep_jugadoresLDE;
    jugadorLDE->primero = NULL;
    jugadorLDE->ultimo = NULL;
    jugadorLDE->cantidad = 0;
    return jugadorLDE;
}

void insertarTJugadoresLDE(TJugadoresLDE &jugadores, TJugador &jugador, TFecha &fecha){

    //Si no tengo nodos en la lista
    if(jugadores->primero == NULL){
        //Creo el nodo de la lista
        TJugadoresAux nuevoNodo = new rep_jugadoresAux;
        nuevoNodo->anterior = NULL;
        nuevoNodo->siguiente = NULL;
        nuevoNodo->jugador = jugador;
        nuevoNodo->fecha = fecha;

        //Como la lista esta vacia apunto el primero y ultimo del cabezal a este unico nodo
        jugadores->primero = nuevoNodo;
        jugadores->ultimo = nuevoNodo;
        jugadores->cantidad = jugadores->cantidad + 1;
       // printf("no tengo nodos en la lista\n");
    }else{
        //Si la lista tiene algun nodo voy al primero y empiezo a comparar las fechas
        TJugadoresAux punteroAux = jugadores->primero;
        while(punteroAux != NULL && compararTFechas(fecha , punteroAux->fecha) == -1){
            punteroAux = punteroAux->siguiente;
        }
        if(punteroAux == NULL){//Si el nodo a agregar es el que tiene la fecha mas chica, es el ultimo nodo
            //Creo el nodo de la lista
            TJugadoresAux nuevoNodo = new rep_jugadoresAux;
            nuevoNodo->anterior = jugadores->ultimo; //Si el nuevoNodo es el nuevo ultimo nodo entonces apunto el puntero anterior al que era el ultimo nodo
            nuevoNodo->siguiente = NULL;
            nuevoNodo->jugador = jugador;
            nuevoNodo->fecha = fecha;
            //Edito el puntero "siguiente" del que es el ultimo nodo porque voy a agregar el nuevoNodo a lo ultimo
            jugadores->ultimo->siguiente = nuevoNodo;
            //Marco el nuevoNodo como el ultimo nodo
            jugadores->ultimo = nuevoNodo;
            jugadores->cantidad = jugadores->cantidad + 1;
          //  printf("es el ultimo nodo\n");

        }else if(punteroAux->anterior == NULL){//Si el nodo a agregar es el que tiene la fecha mas grande, es el primer nodo
            //Creo el nodo de la lista
            TJugadoresAux nuevoNodo = new rep_jugadoresAux;
            nuevoNodo->anterior = NULL;
            nuevoNodo->siguiente = jugadores->primero;//Como el nodo a agregar es el primero, su nodo anterior es el NULL y el siguiente apunta al actual primer nodo.
            nuevoNodo->jugador = jugador;
            nuevoNodo->fecha = fecha;
            //Edito el puntero "anterior" del que era el primer nodo para que apunte al nuevo primer nodo
            jugadores->primero->anterior = nuevoNodo;
            //Marco el nuevo nodo como el nuevo primer nodo
            jugadores->primero = nuevoNodo;
            jugadores->cantidad = jugadores->cantidad + 1;
         //   printf("es el primer nodo\n");

        }else{//Si el nodo esta en el medio de la lista, tiene nodos en anterior y siguiente
            //Creo el nodo de la lista
            TJugadoresAux nuevoNodo = new rep_jugadoresAux;
            nuevoNodo->anterior = punteroAux->anterior;//Como punteroAux queda parado en el nodo que tiene la fecha mas chica(a la derecha de donde voy a agregar el nodo)
            nuevoNodo->siguiente = punteroAux;//el puntero siguiente del nuevoNodo debe apuntar a punteroAux
            nuevoNodo->jugador = jugador;
            nuevoNodo->fecha = fecha;
            //Ahora edito el puntero de la derecha(donde estoy parado con punteroAux)
            punteroAux->anterior = nuevoNodo;
            //Edito el de la izquierda
            nuevoNodo->anterior->siguiente = nuevoNodo;
            jugadores->cantidad = jugadores->cantidad + 1;
          //  printf("es nodo del medio\n");

        }
    }
    return;
}

void liberarNodoJugadoresLDE(TJugadoresAux jugadoresAux){
    liberarTJugador(jugadoresAux->jugador);
    liberarTFecha(jugadoresAux->fecha);
    delete jugadoresAux;
}


void liberarTJugadoresLDE(TJugadoresLDE &jugadores){
   TJugadoresAux punteroAux = jugadores->primero;
   TJugadoresAux siguienteAux = NULL;
   while (punteroAux != NULL){
    siguienteAux = punteroAux->siguiente;
    liberarNodoJugadoresLDE(punteroAux);
    punteroAux = siguienteAux;
   }
   delete jugadores;
   //Agregado haciendo las aplicaciones
   jugadores = NULL;
}
/*
Jugador 8:  Andres, Argentina, 21 años
Jugada: 2 
Movimientos: Izquierda Izquierda Izquierda Izquierda 
Jugada: 3 
Movimientos: Izquierda Arriba Abajo Abajo 
Jugada: 4 
Movimientos: Arriba Arriba Izquierda Izquierda 
1/1/2023
*/
void imprimirMayorAMenorTJugadoresLDE(TJugadoresLDE jugadores){
    if(jugadores->primero != NULL){
        TJugadoresAux punteroAux = jugadores->primero;
        while (punteroAux != NULL){
        imprimirTJugador(punteroAux->jugador);
        imprimirTFecha(punteroAux->fecha);
        punteroAux = punteroAux->siguiente;
    }    
    }

}

void imprimirMenorAMayorTJugadoresLDE(TJugadoresLDE jugadores){
    if(jugadores->ultimo != NULL){
        TJugadoresAux punteroAux = jugadores->ultimo;
        while (punteroAux != NULL){
        imprimirTJugador(punteroAux->jugador);
        imprimirTFecha(punteroAux->fecha);
        punteroAux = punteroAux->anterior;
    }
    }
}

nat cantidadTJugadoresLDE(TJugadoresLDE jugadores){
    return jugadores->cantidad;
}

void eliminarInicioTJugadoresLDE(TJugadoresLDE &jugadores){
    TJugadoresAux punteroAEliminar = jugadores->primero;
    if(jugadores->primero != NULL && jugadores->ultimo != jugadores->primero){
        jugadores->primero = jugadores->primero->siguiente;
        jugadores->primero->anterior = NULL;
        liberarNodoJugadoresLDE(punteroAEliminar);
        jugadores->cantidad = jugadores->cantidad - 1;
    }else{
        liberarNodoJugadoresLDE(punteroAEliminar);
        jugadores->primero = NULL;
        jugadores->ultimo = NULL;
        jugadores->cantidad = jugadores->cantidad - 1;
    }
}

void eliminarFinalTJugadoresLDE(TJugadoresLDE &jugadores){
    TJugadoresAux punteroAEliminar = jugadores->ultimo;
    if(jugadores->ultimo != NULL && jugadores->primero != jugadores->ultimo){
        jugadores->ultimo = jugadores->ultimo->anterior;
        jugadores->ultimo->siguiente = NULL;
        liberarNodoJugadoresLDE(punteroAEliminar);
        jugadores->cantidad = jugadores->cantidad - 1;
    }else{
        liberarNodoJugadoresLDE(punteroAEliminar);
        jugadores->primero = NULL;
        jugadores->ultimo = NULL;
        jugadores->cantidad = jugadores->cantidad - 1;
    }
}

bool estaEnTJugadoresLDE(TJugadoresLDE jugadores, nat id){
    TJugadoresAux punteroAux = jugadores->primero;
    bool schrodinger = false;
    while (punteroAux != NULL && idTJugador(punteroAux->jugador) != id){
        punteroAux = punteroAux->siguiente;
    }if(punteroAux == NULL){
        return schrodinger;
    }else{
        schrodinger = true;
        return schrodinger;
    }
}

TJugador obtenerTJugadorDeTJugadoresLDE(TJugadoresLDE jugadores, nat id){
    TJugadoresAux punteroAux = jugadores->primero;
    TJugador este = NULL;
    while (punteroAux != NULL && idTJugador(punteroAux->jugador) != id){
        punteroAux = punteroAux->siguiente;
    }if(punteroAux == NULL){
        return este;
    }else{
        este = punteroAux->jugador;
        return este;
    }

}

TFecha obtenerTFechaDeTJugadoresLDE(TJugadoresLDE jugadores, nat id){
    TJugadoresAux punteroAux = jugadores->primero;
    TFecha esta = NULL;
    while (punteroAux != NULL && idTJugador(punteroAux->jugador) != id){
        punteroAux = punteroAux->siguiente;
    }if(punteroAux == NULL){
        return esta;
    }else{
        esta = punteroAux->fecha;
        return esta;
    }
}

TJugadoresLDE obtenerSegunTFecha(TJugadoresLDE jugadores, TFecha fecha){
    TJugadoresAux punteroAux = jugadores->primero;
    while(punteroAux != NULL && compararTFechas(fecha, punteroAux->fecha) == 1){
        punteroAux = punteroAux->siguiente;
    }
    if(punteroAux == NULL){
        return NULL;
    }else{
        TJugadoresLDE estos = crearTJugadoresLDE();
        while (compararTFechas(fecha, punteroAux->fecha) == 0){
            insertarTJugadoresLDE(estos, punteroAux->jugador, punteroAux->fecha);
        }
        return estos;
    }
}

TJugadoresLDE unirTJugadoresLDE(TJugadoresLDE &jugadores1, TJugadoresLDE &jugadores2){
    TJugadoresLDE jugadoresUnion = crearTJugadoresLDE();
    jugadoresUnion->cantidad = jugadores1->cantidad + jugadores2->cantidad;
    TJugadoresAux puntero1 = jugadores1->primero;
    TJugadoresAux puntero2 = jugadores2->primero;
    TJugadoresAux punteroAux = NULL;

//Si una o las dos listas son vacis => devuelvo la lista que no es vacia o devuelvo la lista jugadoresUnion vacia
    if(puntero1 == NULL || puntero2 == NULL){
    //Si la lista 1 es vacia devuelvo la lista 2
        if (puntero1 == NULL){
            jugadoresUnion->primero = jugadores2->primero;
            jugadoresUnion->ultimo = jugadores2->ultimo;

            delete jugadores1;
            delete jugadores2;
            return jugadoresUnion;
        }else if(puntero2 == NULL){
    //Si la lista 2 es vacia devuelvo la lista 1
            jugadoresUnion->primero = jugadores1->primero;
            jugadoresUnion->ultimo = jugadores1->ultimo;

            delete jugadores1;
            delete jugadores2;
            return jugadoresUnion;
        }else{
    //Si las dos listas son vacias devuelvo jugadoresUnion con los dos punteros NULL
            delete jugadores1;
            delete jugadores2;
            return jugadoresUnion;
        }

    }

//Bucle While para recorrer las listas hasta llegar al final de una de las dos
    while(puntero1 != NULL && puntero2 != NULL){
    //Comparo las fechas, si da 1 o 2(fecha del nodo 2 >= fecha del nodo 1) => el nodo de la lista 2 va primero
        if (compararTFechas(puntero2->fecha, puntero1->fecha) == -1){
        //Entro a este if solamente si va a ser el primer nodo de jugadoresUnion
            if(jugadoresUnion->primero == NULL){
                punteroAux = puntero1->siguiente;
                jugadoresUnion->primero = puntero1;
                puntero1 = punteroAux;
                punteroAux = jugadoresUnion->primero;
        //Entra a este else si ya hay nodos en la lista jugadoresUnion
            }else{
                punteroAux->siguiente =  puntero1;
                puntero1->anterior = punteroAux;
                punteroAux = puntero1;
                puntero1 = puntero1->siguiente;
            }
    //Entra a este else solo si la fecha del puntero1 es mayor a la del puntero2
        }else{
        //Entro a este if solamente si va a ser el primer nodo de jugadoresUnion
            if(jugadoresUnion->primero == NULL){
                punteroAux = puntero2->siguiente;
                jugadoresUnion->primero = puntero2;
                puntero2 = punteroAux;
                punteroAux = jugadoresUnion->primero;
        //Entra a este else si ya hay nodos en la lista jugadoresUnion
            }else{
                punteroAux->siguiente = puntero2;
                puntero2->anterior = punteroAux;
                punteroAux = puntero2;
                puntero2 = puntero2->siguiente;
            }
        }
    }
    //Salgo del while cuando llegue al final de una de las dos listas
    //Lo que me queda hacer es unir los nodos restantes de la lista que no llego al final
    //Los nodos restantes ya estan unidos en orden y tienen el NULL al final

    //Entro a este if solo si quedan nodos de la lista 1 por agregar
    if(puntero1 != NULL){
    //Uno el ultimo nodo cargado de jugadoresUnion con los nodos restantes de la lista 1
        punteroAux->siguiente = puntero1;
        puntero1->anterior = punteroAux;
        jugadoresUnion->ultimo = jugadores1->ultimo;
    }else{
    //Entro a este else si la lista que no llego al final es la lista 2
        punteroAux->siguiente = puntero2;
        puntero2->anterior = punteroAux;
        jugadoresUnion->ultimo = jugadores2->ultimo;
    }
//Libero la memoria de las listas y devuelvo la union ordenada
    delete jugadores1;
    delete jugadores2;
    return jugadoresUnion;
}

///////////////////////////////////
////// FIN CÓDIGO TAREA 2 //////
///////////////////////////////////

///////////////////////////////////////////////////////////////////////////
/////////////  NUEVAS FUNCIONES  //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////


TJugador obtenerInicioDeTJugadoresLDE(TJugadoresLDE jugadores){
    return jugadores->primero->jugador;
}

///////////////////////////////////////////////////////////////////////////
/////////////  NUEVAS FUNCIONES TAREA 4 ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////

void eliminarJugadorConNombreTJugadoresLDE(TJugadoresLDE &jugador, const char nombre[100]){
    TJugadoresAux punteroAux = jugador->primero;
    
    while (punteroAux != NULL && strcmp(nombre, nombreTJugador(punteroAux->jugador)) != 0){
        punteroAux = punteroAux->siguiente;
    }if(punteroAux == NULL){
        printf("No se encontro el jugador con ese nombre\n");
        
    }else{
        if(cantidadTJugadoresLDE(jugador) == 1){ //Si es el unico
            jugador->primero = NULL;
            jugador->ultimo = NULL;
        }
        else if(punteroAux == jugador->primero){ //Si es el primero
            jugador->primero = punteroAux->siguiente;
            punteroAux->siguiente->anterior = NULL;
        }
        else if(punteroAux == jugador->ultimo){ //Si es el ultimo
            jugador->ultimo = punteroAux->anterior;
            punteroAux->anterior->siguiente = NULL;
        }
        else{                                   //Si NO es el unico, NI el primero, NI el ultimo, ES uno del medio
            punteroAux->anterior->siguiente = punteroAux->siguiente;
            punteroAux->siguiente->anterior = punteroAux->anterior;
        }
        
        liberarNodoJugadoresLDE(punteroAux);
        punteroAux = NULL;
        jugador->cantidad = jugador->cantidad - 1;
    }
}

bool estaJugadorConNombreEnTJugadoresLDE(TJugadoresLDE jugador, const char nombre[100]){
    TJugadoresAux punteroAux = jugador->primero;
    bool esta = false;
    
    while (punteroAux != NULL && strcmp(nombre, nombreTJugador(punteroAux->jugador)) != 0){
        punteroAux = punteroAux->siguiente;
    }if(punteroAux == NULL){
        //printf("No se encontro el jugador con ese nombre\n");
        
    }else{
        esta = true;
    }
    return esta;
}

TJugador obtenerJugadorConNombreTJugadoresLDE(TJugadoresLDE jugador, const char nombre[100]){
    TJugadoresAux punteroAux = jugador->primero;
    TJugador este = NULL;

    while (punteroAux != NULL && strcmp(nombre, nombreTJugador(punteroAux->jugador)) != 0){
        punteroAux = punteroAux->siguiente;
    }if(punteroAux == NULL){
        printf("No se encontro el jugador con ese nombre\n");
        
    }else{
        este = punteroAux->jugador;
    }
    return este;
}


///////////////////////////////////////////////////////////////////////////
/////////////  FIN NUEVAS FUNCIONES TAREA 4 ///////////////////////////////
///////////////////////////////////////////////////////////////////////////
