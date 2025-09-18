#include "../include/conjuntoIds.h"

struct rep_conjuntoIds{
    bool* ids;// Array para almacenar los IDs
    nat maxCant;// Cantidad máxima de elementos que puede tener el conjunto
    nat cantidad; // Cantidad actual de elementos en el conjunto
};


TConjuntoIds crearTConjuntoIds(nat cantMax){
    TConjuntoIds conjunto = new rep_conjuntoIds;
    conjunto->ids = new bool[cantMax];
    conjunto->maxCant = cantMax;
    conjunto->cantidad = 0;

    for (nat i = 0; i < cantMax; i++) {
        conjunto->ids[i] = false; // Inicializar todos los elementos en false
    }

    return conjunto;
};


bool esVacioTConjuntoIds(TConjuntoIds c){
    return c->cantidad == 0;
};

void insertarTConjuntoIds(nat id, TConjuntoIds &c) {
    if (id >= 1 && id <= c->maxCant) {
        // Insertar el nuevo ID en la posicion especificada
        c->ids[id - 1] = true;                                  //Ojo con insertar si en la pos id ya estaba en true
        c->cantidad++;                                          //Si ya estaba en true no debo sumar en la cantidad
    }
}

void borrarTConjuntoIds(nat id, TConjuntoIds &c){
    if (id >= 1 && id <= c->maxCant) {
        // Insertar el nuevo ID en la posicion especificada
        c->ids[id - 1] = false;                                 //Ojo con restar si en la pos id ya estaba en false
        c->cantidad--;
    }
};

bool perteneceTConjuntoIds(nat id, TConjuntoIds c){
    if(0 < id && id <= c->maxCant){
        return c->ids[id - 1] == true;
    }else{
        return false;
    }
}


nat cardinalTConjuntoIds(TConjuntoIds c){
    return c->cantidad;
};

nat cantMaxTConjuntoIds(TConjuntoIds c){
    return c->maxCant;
};

void imprimirTConjuntoIds(TConjuntoIds c){
    for (nat i = 0; i < c->maxCant; i++) {
        if (c->ids[i]) {
            printf("%u ", i + 1); // Imprime el indice + 1 para mostrar los IDs reales
        }
    }
    printf("\n");
};

void liberarTConjuntoIds(TConjuntoIds &c){
    delete[] c->ids;
    delete c;
    c = NULL;
};




TConjuntoIds unionTConjuntoIds(TConjuntoIds c1, TConjuntoIds c2){
    // Crear un nuevo conjunto con la capacidad máxima
    TConjuntoIds resultado = crearTConjuntoIds(c1->maxCant);

    // Copiar los elementos de c1 al conjunto resultado
    for (nat i = 0; i < c1->maxCant; i++) {
        if (c1->ids[i]) {
            insertarTConjuntoIds(i + 1, resultado); // i + 1 para ajustar el valor del ID
        }
    }

    // Copiar los elementos de c2 al conjunto resultado
    for (nat i = 0; i < c2->maxCant; i++) {
        if (c2->ids[i]) {
            insertarTConjuntoIds(i + 1, resultado); // i + 1 para ajustar el valor del ID
        }
    }

    return resultado;
};

TConjuntoIds interseccionTConjuntoIds(TConjuntoIds c1, TConjuntoIds c2){
    // Crear un nuevo conjunto con la capacidad máxima
    TConjuntoIds resultado = crearTConjuntoIds(c1->maxCant);

    // Realizar la intersección
    for (nat i = 0; i < c1->maxCant; i++) {
        // Verificar si el elemento está presente en ambos conjuntos
        if (c1->ids[i] && c2->ids[i]) {
            insertarTConjuntoIds(i + 1, resultado); // i + 1 para ajustar el valor del ID
        }
    }

    return resultado;
};

TConjuntoIds diferenciaTConjuntoIds(TConjuntoIds c1, TConjuntoIds c2){
    // Crear un nuevo conjunto con la capacidad máxima
    TConjuntoIds resultado = crearTConjuntoIds(c1->maxCant);

    // Realizar la diferencia
    for (nat i = 0; i < c1->maxCant; i++) {
        // Verificar si el elemento está presente en c1 pero no en c2
        if (c1->ids[i] && !c2->ids[i]) {
            insertarTConjuntoIds(i + 1, resultado); // i + 1 para ajustar el valor del ID
        }
    }

    return resultado;
};
