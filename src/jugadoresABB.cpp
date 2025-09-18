#include "../include/jugadoresABB.h"
#include "../include/colaJugadoresABB.h"
#include "../include/pilaJugador.h"

struct rep_jugadoresABB {
    TJugador jugador;
    rep_jugadoresABB* izq;
    rep_jugadoresABB* der;
};

TJugadoresABB crearTJugadoresABB() {
    rep_jugadoresABB* nuevoNodo = NULL;
    return nuevoNodo;
}

bool esVacioTJugadoresABB(TJugadoresABB jugadoresABB) {
    return jugadoresABB == NULL;
}

void insertarTJugadoresABB(TJugadoresABB &jugadoresABB, TJugador jugador) {
    if(jugadoresABB == NULL){
        jugadoresABB = new rep_jugadoresABB;
        jugadoresABB->jugador = jugador;
        jugadoresABB->der = NULL;
        jugadoresABB->izq = NULL;
    }
    else if(idTJugador(jugador) > idTJugador(jugadoresABB->jugador)){
        insertarTJugadoresABB(jugadoresABB->der, jugador);
    }
    else if(idTJugador(jugador) < idTJugador(jugadoresABB->jugador)){
        insertarTJugadoresABB(jugadoresABB->izq, jugador);
    }
}

//Funcion auxiliar para liberar un nodo individual
void liberarNodoABB(TJugadoresABB &jugadoresABB){
    if(jugadoresABB !=NULL){
        liberarTJugador(jugadoresABB->jugador);
        delete jugadoresABB;
    }
};

void liberarTJugadoresABB(TJugadoresABB &jugadoresABB) {
    if(jugadoresABB != NULL){
        liberarTJugadoresABB(jugadoresABB->izq);
        liberarTJugadoresABB(jugadoresABB->der);
        liberarNodoABB(jugadoresABB);
        jugadoresABB = NULL;
    }
}

void imprimirTJugadoresABB(TJugadoresABB jugadoresABB) {
    if(jugadoresABB != NULL){
        imprimirTJugadoresABB(jugadoresABB->izq);
        imprimirTJugador(jugadoresABB->jugador);
        imprimirTJugadoresABB(jugadoresABB->der);
    }
}

nat cantidadTJugadoresABB(TJugadoresABB jugadoresABB) {
    if(jugadoresABB == NULL){
        return 0;
    }
    return 1 + cantidadTJugadoresABB(jugadoresABB->izq) + cantidadTJugadoresABB(jugadoresABB->der);
}

TJugador maxIdJugador(TJugadoresABB jugadoresABB) {
    // Caso base: el arbol binario solo tiene un nodo
    if (jugadoresABB->izq == NULL && jugadoresABB->der == NULL) {
        return jugadoresABB->jugador;
    }

    // Recursivamente buscar el nodo mas a la derecha
    if (jugadoresABB->der != NULL) {
        return maxIdJugador(jugadoresABB->der);
    } else {
        return jugadoresABB->jugador;
    }
}

void removerTJugadoresABB(TJugadoresABB &jugadoresABB, nat id) {
    if(id == idTJugador(jugadoresABB->jugador)){ //Encuentro el nodo a eliminar
        TJugadoresABB aux = NULL;
        if(jugadoresABB->der == NULL){ //
            aux = jugadoresABB;
            jugadoresABB = jugadoresABB->izq;
            liberarNodoABB(aux);
            aux = NULL;
        }else if(jugadoresABB->izq == NULL){
            aux = jugadoresABB;
            jugadoresABB = jugadoresABB->der;
            liberarNodoABB(aux);
            aux = NULL;
        }else{
            TJugador maxIzq = maxIdJugador(jugadoresABB->izq);
            TJugador copiaMaxIzq = copiarTJugador(maxIzq);
            liberarTJugador(jugadoresABB->jugador);
            jugadoresABB->jugador = copiaMaxIzq;
            removerTJugadoresABB(jugadoresABB->izq, idTJugador(maxIzq));
            maxIzq = NULL;
        }
    }else if(id > idTJugador(jugadoresABB->jugador)){
        removerTJugadoresABB(jugadoresABB->der, id);
    }else{
        removerTJugadoresABB(jugadoresABB->izq, id);
    }
}

bool estaTJugadoresABB(TJugadoresABB jugadoresABB, nat id) {
    if (esVacioTJugadoresABB(jugadoresABB)) {
        return false;
    } else if (id == idTJugador(jugadoresABB->jugador)) {
        return true;
    } else if (id < idTJugador(jugadoresABB->jugador)) {
        return estaTJugadoresABB(jugadoresABB->izq, id);
    } else {
        return estaTJugadoresABB(jugadoresABB->der, id);
    }    
    return false;
}

TJugador obtenerDeTJugadoresABB(TJugadoresABB jugadoresABB, nat id) {
    // Caso base: arbol vacio
    if (esVacioTJugadoresABB(jugadoresABB)) {
        // No deberia llegar aca si se cumplio PRE
        return NULL;
    } else {
        // Comparar ID del jugador a obtener con ID de la raiz
        nat idRaiz = idTJugador(jugadoresABB->jugador);
        if (id == idRaiz) {
            // Se encontro el jugador
            return jugadoresABB->jugador;
        } else if (id < idRaiz) {
            // Buscar en subarbol izquierdo
            return obtenerDeTJugadoresABB(jugadoresABB->izq, id);
        } else {
            // Buscar en subarbol derecho
            return obtenerDeTJugadoresABB(jugadoresABB->der, id);
        }
    }
    return NULL;
}

nat alturaTJugadoresABB(TJugadoresABB jugadoresABB) {
    if (esVacioTJugadoresABB(jugadoresABB)) {
        return 0;
    } else {
        // Obtener la altura de los subarboles izquierdo y derecho
        nat alturaIzq = alturaTJugadoresABB(jugadoresABB->izq);
        nat alturaDer = alturaTJugadoresABB(jugadoresABB->der);
        // La altura del arbol es la altura del subarbol mas alto mas 1
        if (alturaIzq > alturaDer) {
            return 1 + alturaIzq;
        } else {
            return 1 + alturaDer;
        }
    }
    
    return 0;
}

bool esPerfectoTJugadoresABB(TJugadoresABB jugadoresABB) {
    if (esVacioTJugadoresABB(jugadoresABB) || (esVacioTJugadoresABB(jugadoresABB->izq) && esVacioTJugadoresABB(jugadoresABB->der))) {
        return true;
    } else if (esVacioTJugadoresABB(jugadoresABB->izq) || esVacioTJugadoresABB(jugadoresABB->der)) {
        return false;
    } else {
        nat alturaIzq = alturaTJugadoresABB(jugadoresABB->izq);
        nat alturaDer = alturaTJugadoresABB(jugadoresABB->der);
        if (alturaIzq != alturaDer) {
            return false;
        } else {
            return esPerfectoTJugadoresABB(jugadoresABB->izq) && esPerfectoTJugadoresABB(jugadoresABB->der);
        }
    }  
    return false;
}

//Funcion auxiliar
void mayoresAux(TJugadoresABB jugadoresABB, nat edad, TJugadoresABB &nuevoABB) {
    if (jugadoresABB == NULL) {
        return;
    }

    mayoresAux(jugadoresABB->izq, edad, nuevoABB);

    if (edadTJugador(jugadoresABB->jugador) > edad) {
        insertarTJugadoresABB(nuevoABB, copiarTJugador(jugadoresABB->jugador));
    }

    mayoresAux(jugadoresABB->der, edad, nuevoABB);
}

TJugadoresABB mayoresTJugadoresABB(TJugadoresABB jugadoresABB, nat edad) {
    TJugadoresABB nuevoABB = crearTJugadoresABB();
    mayoresAux(jugadoresABB, edad, nuevoABB);
    return nuevoABB;
}

///////////////////////////////////
////// FIN CÓDIGO TAREA 2 //////
///////////////////////////////////

///////////////////////////////////////////////////////////////////////////
/////////////  NUEVAS FUNCIONES  //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

//Funcion auxiliar: Me dice el maximo entre a y b
int max(int a, int b) {
    return (a > b) ? a : b;
}

nat amplitudTJugadoresABB(TJugadoresABB t) {
    if (t == NULL) {
        return 0; // Si el arbol esta vacio la amplitud es 0
    }

    // Creo una cola de jugadoresABB para realizar el recorrido por niveles
    TColaJugadoresABB cola = crearTColaJugadoresABB();
    encolarEnTColaJugadoresABB(t, cola);

    int maxAmplitud = 1;

    while (cantidadEnTColaJugadoresABB(cola) > 0) {
        int nivelAmplitud = cantidadEnTColaJugadoresABB(cola);
       // printf("nivelAmplitud = %d\n", nivelAmplitud);
        
        maxAmplitud = max(maxAmplitud, nivelAmplitud);
        //printf("maxAmplitud = %d\n", maxAmplitud);
        
        // Agregamos los hijos a la cola para el siguiente nivel
        for (int i = 0; i < nivelAmplitud; i++) {
            TJugadoresABB nodo = frenteDeTColaJugadoresABB(cola);
            desencolarDeTColaJugadoresABB(cola);
            
            if (nodo->izq != NULL) {
                encolarEnTColaJugadoresABB(nodo->izq, cola);
            }
            if (nodo->der != NULL) {
                encolarEnTColaJugadoresABB(nodo->der, cola);
            }
        }
    }
    
    liberarTColaJugadoresABB(cola);
    
    return maxAmplitud;
}

TPilaJugador serializarTJugadoresABB(TJugadoresABB t) {
    TPilaJugador pila = crearTPilaJugador();
    TPilaJugador pilainvertida = crearTPilaJugador();
    if (t == NULL) {
        return pila; // Árbol vacío, devuelve la pila vacía
    }

    // Utilizamos una cola para realizar el recorrido por niveles
    TColaJugadoresABB cola = crearTColaJugadoresABB();
    encolarEnTColaJugadoresABB(t, cola);

    while (cantidadEnTColaJugadoresABB(cola) > 0) {
        TJugadoresABB nodo = frenteDeTColaJugadoresABB(cola);
        desencolarDeTColaJugadoresABB(cola);

        // Apilamos el jugador correspondiente al nodo actual en la pila
        apilarEnTPilaJugador(pila, nodo->jugador);

        // Agregamos los hijos a la cola para el siguiente nivel en el orden correcto
        if (nodo->izq != NULL) {
            encolarEnTColaJugadoresABB(nodo->izq, cola);
        }
        if (nodo->der != NULL) {
            encolarEnTColaJugadoresABB(nodo->der, cola);
        }
    }

    while(cantidadEnTPilaJugador(pila) > 0){   
        apilarEnTPilaJugador(pilainvertida, cimaDeTPilaJugador(pila));
        desapilarDeTPilaJugador(pila);
    }
    liberarTPilaJugador(pila);

    liberarTColaJugadoresABB(cola);
    return pilainvertida;
}

TJugadoresABB deserializarTJugadoresABB(TPilaJugador &p) {
    if(cantidadEnTPilaJugador(p) == 0){
        //printf("El arbol no es completo \n");
        return NULL;
    }
    TColaJugadoresABB cola = crearTColaJugadoresABB();
    TJugadoresABB arbol = crearTJugadoresABB();

    if(cantidadEnTPilaJugador(p) > 0){
        
        //Creo el nodo del arbol
        arbol = new rep_jugadoresABB;
        arbol->jugador = copiarTJugador(cimaDeTPilaJugador(p));
        desapilarDeTPilaJugador(p);
        arbol->der = NULL;
        arbol->izq = NULL;
        
        encolarEnTColaJugadoresABB(arbol,cola);
    }

    while(cantidadEnTColaJugadoresABB(cola) > 0 && cantidadEnTPilaJugador(p) > 0){

        TJugadoresABB padre = frenteDeTColaJugadoresABB(cola);
        //printf("el padre es: %d \n", idTJugador(padre->jugador));

        //agrego al jugadorABB al arbol
        if(padre->izq == NULL && cantidadEnTPilaJugador(p) > 0){//Si el hijo izquierdo es el null agrego la cima de la pila como hijo, desapilo y pongo en la cola el nodo
           //printf("cantidad en la cola: %d \n", cantidadEnTColaJugadoresABB(cola));
            //printf("entra \n");
            //printf("agrego el nodo %d \n", idTJugador(cimaDeTPilaJugador(p)));

            //creo el nodo hijo con la cima de la pila
            TJugadoresABB jugadorABB = new rep_jugadoresABB;
            //printf("1 \n");
            jugadorABB->jugador = copiarTJugador(cimaDeTPilaJugador(p));
            jugadorABB->der = NULL;
            jugadorABB->izq = NULL;
            
            padre->izq = jugadorABB;
            
            desapilarDeTPilaJugador(p);
            
            encolarEnTColaJugadoresABB(jugadorABB , cola);
            
        }
        if(padre->der == NULL && cantidadEnTPilaJugador(p) > 0){//Si el hijo derecho es null agrego la cima de la pila como hijo, desapilo y pongo el nodo en la cola
            //creo el nodo hijo con la cima de la pila
            //printf("2 \n");
           // printf("agrego el nodo %d \n", idTJugador(cimaDeTPilaJugador(p))); 

            TJugadoresABB jugadorABB = new rep_jugadoresABB;
            jugadorABB->jugador = copiarTJugador(cimaDeTPilaJugador(p));
            jugadorABB->der = NULL;
            jugadorABB->izq = NULL;
            
            padre->der = jugadorABB;
            
            desapilarDeTPilaJugador(p);

            encolarEnTColaJugadoresABB(jugadorABB , cola); 
        }
        
        desencolarDeTColaJugadoresABB(cola);
        //printf("4 \n");
    }
    liberarTColaJugadoresABB(cola);
    liberarTPilaJugador(p);
    

    return arbol;
}


///////////////////////////////////////////////////////////////////////////
/////////////  FIN NUEVAS FUNCIONES  //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
