#Proyecto de Agenda y Gestión de Jugadores
------------------------------------------

Este repositorio contiene la versión final de un proyecto academico de programación.

El proyecto implementa distintos tipos abstractos de datos (TADs) y estructuras dinámicas en C++, como:

- Fechas y eventos
- Agendas de eventos
- Jugadas, partidas y jugadores
- Listas (simples y dobles)
- Pilas y colas
- Árboles binarios de búsqueda
- Conjuntos de identificadores
- Aplicaciones que integran todos estos TADs

-------------------------------------------------------------------------------------------------------------------------------------

##📂 Estructura del repositorio
```
agenda_de_eventos/
│── include/         # Archivos de cabecera (.h)
│── src/             # Implementaciones en C++ (.cpp)
│── test/            # Casos de prueba (.in y .out)
│   └── salidas/     # Carpeta donde se generan las salidas de los tests
│── obj/             # Archivos objeto generados en la compilación
│── Makefile         # Reglas de compilación (provisto)
│── principal.cpp    # Programa principal (provisto)
│── README.md

```

> 🔹 Nota: `principal.cpp`, el `Makefile` y los tests fueron provistos por los docentes.  
> 🔹 Los archivos `.cpp` en `src/` son las implementaciones realizadas por mí (ver sección Autoría).  
> 🔹 Las carpetas `obj/` y `test/salidas/` se incluyen aunque estén vacías, usando archivos `.gitkeep`, porque son necesarias para que el Makefile funcione correctamente.

-------------------------------------------------------------------------------------------------------------------------------------

##⚙️ Compilación y ejecución

> ⚠️ Nota: Este proyecto está pensado para un entorno Linux. Puede que la compilación en macOS o Windows requiera ajustes en el compilador o las flags de compilación.

Compilar el proyecto:

```
make
```

Ejecutar el programa:
```
./principal
```

Ejecutar un test de ejemplo:
```
./principal < test/fecha1-crear-imprimir-liberar.in
```

Ejecutar todos los tests automáticamente:
```
make testing
```
-------------------------------------------------------------------------------------------------------------------------------------

##✍️ Autoría

Archivos que implementé yo:

- `src/fecha.cpp`
- `src/jugada.cpp`
- `src/jugador.cpp`
- `src/partida.cpp`
- `src/jugadoresLDE.cpp`
- `src/jugadoresABB.cpp`
- `src/pilaJugador.cpp`
- `src/colaJugadoresABB.cpp`
- `src/conjuntoIds.cpp`
- `src/tablaJugadores.cpp`
- `src/aplicaciones.cpp`
- `src/colaDePrioridadJugador.cpp`
>📌 `principal.cpp`, el `Makefile` y los tests (.in / .out) fueron provistos por el curso.

-------------------------------------------------------------------------------------------------------------------------------------

##👤 Autor

Rodrigo Navone
