#include "../include/tablaJugadores.h"
/*
struct rep_nodoHash{
    TJugador jugador;   //Dominio
    TFecha fecha;       //Rango
    rep_nodoHash* sig;
};
typedef rep_nodoHash* TNodoHash;
*/

struct rep_tablaJugadores {
    //rep_nodoHash** tabla;
    //int cantidad;
    int cota;
    TJugadoresLDE* tabla;
};

nat funcionDeDispersion(const char nombre[100]){
    nat res = 0;
    int i = 0;
    while(i< 100 && nombre[i] != '\0'){
        res += int(nombre[i]);
        i++;
    }
    return res;
}

TTablaJugadores crearTTablaJugadores(int max){
    TTablaJugadores t = new rep_tablaJugadores;
    t->tabla = new TJugadoresLDE[max];

    for(int i=0; i < max; i++) t->tabla[i] = crearTJugadoresLDE();
    //t->cantidad = 0;
    t->cota = max;
    return t;
}

/*
void liberarNodoHash(TNodoHash nodo){
    liberarTJugador(nodo->jugador);
    delete nodo;
}
*/

void liberarTTablaJugadores(TTablaJugadores &tabla){
    for(int i=0; i < tabla->cota; i++){
        TJugadoresLDE punteroAux = tabla->tabla[i];
        liberarTJugadoresLDE(punteroAux);
    }
    delete[] tabla->tabla;
    delete tabla;
    tabla = NULL;
}

// PRE: !perteneceATTablaJugadores(tabla, nombreTJugador(jugador)), osea que no existe jugador con ese nombre en la tabla
void insertarJugadorEnTabla(TTablaJugadores &tabla, TJugador jugador, TFecha fecha){
    int pos = funcionDeDispersion(nombreTJugador(jugador)) % (tabla->cota); //Veo en que posicion de la lista del hash voy a insertar
    insertarTJugadoresLDE(tabla->tabla[pos], jugador, fecha);//La funcion es Theta(n) pero como se supone que no hay nada en esa pos termina siendo Theta(1) en promedio
}


void eliminarJugadorDeTTablaJugadores(TTablaJugadores &tabla, const char nombre[100]){
    int pos = funcionDeDispersion(nombre) % (tabla->cota);//Posicion en la que deberia estar el jugador con ese nombre
    eliminarJugadorConNombreTJugadoresLDE(tabla->tabla[pos], nombre);
}

bool perteneceATTablaJugadores(TTablaJugadores tabla, const char nombre[100]){
    int pos = funcionDeDispersion(nombre) % (tabla->cota);//Posicion en la que deberia estar el jugador con ese nombre
    bool esta = false;

    if(estaJugadorConNombreEnTJugadoresLDE(tabla->tabla[pos], nombre)){
        esta = true;
    }

    return esta;
}

TJugador obtenerJugadorDeTTablaJugadores(TTablaJugadores tabla, const char nombre[100]){
    int pos = funcionDeDispersion(nombre) % (tabla->cota);//Posicion en la que deberia estar el jugador con ese nombre
    TJugador jugador = obtenerJugadorConNombreTJugadoresLDE(tabla->tabla[pos], nombre);
    return jugador;
}

void imprimirTTablaJugadores(TTablaJugadores tabla){
    for(int i=0; i < tabla->cota; i++){
        TJugadoresLDE punteroAux = tabla->tabla[i];
        imprimirMayorAMenorTJugadoresLDE(punteroAux);
    }
}