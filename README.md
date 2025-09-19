#Player Management and Scheduling System
------------------------------------------

This repository contains the final implementation of an academic programming project.

The project implements various abstract data types (ADTs) and dynamic structures in C++, such as:

- Dates and events
- Event agendas
- Moves, matches, and players
- Lists (singly and doubly linked)
- Stacks and queues
- Binary search trees
- Sets of identifiers
- Applications that integrate all these ADTs

-------------------------------------------------------------------------------------------------------------------------------------

##📂 Repository Structure
```
agenda_de_eventos/
│── include/         # Header files (.h)
│── src/             # C++ implementations (.cpp)
│── test/            # Test cases (.in and .out)
│   └── salidas/     # Folder where test outputs are generated
│── obj/             # Object files generated during compilation
│── Makefile         # Build rules (provided)
│── principal.cpp    # Main program (provided)
│── README.md
│── README.es.md

```

> 🔹 Note: `principal.cpp`, the `Makefile`, and the test files were provided by the instructors.  
> 🔹 The `.cpp` files in `src/` are the implementations I developed (see Authoring section).  
> 🔹 The `obj/` and `test/salidas/` folders are included even if empty, using `.gitkeep` files, because they are necessary for the Makefile to work correctly.

-------------------------------------------------------------------------------------------------------------------------------------

##⚙️ Compilation and Execution

> ⚠️ Note: This project is intended for a Linux environment. Compilation on macOS or Windows may require adjustments to the compiler or compilation flags.

Compile the project:

```
make
```

Run the program:
```
./principal
```

Run an example test:
```
./principal < test/fecha1-crear-imprimir-liberar.in
```

Run all tests automatically:
```
make testing
```
-------------------------------------------------------------------------------------------------------------------------------------

##✍️ Authorship

Files implemented by me:

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
>📌 `principal.cpp`, the `Makefile` and the tests (.in / .out) were provided by the course.

-------------------------------------------------------------------------------------------------------------------------------------

##👤 Author

Rodrigo Navone
