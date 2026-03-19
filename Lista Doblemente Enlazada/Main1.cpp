// main.cpp
// Programa que controla el reproductor de música
// usando una lista doblemente enlazada
#include <iostream>   // entrada y salida (cout, cin)
#include <string>     // uso de string
#include <limits>     // limpiar buffer
#include "playlist.h"
using namespace std;

// Limpia el buffer del teclado (evita errores con getline)
void limpiarBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Muestra el título del programa
void encabezado() {
    cout << endl;
    cout << "  ________________________________________" << endl;
    cout << "  |              Playlist                |" << endl;
    cout << "  |     Lista Doblemente Enlazada        |" << endl;
    cout << "  |______________________________________|" << endl;
}

// Muestra el menú de opciones
void menuPrincipal() {
    cout << endl;
    cout << "  ________________________________________" << endl;
    cout << "  |  1. Agregar cancion                  |" << endl;
    cout << "  |  2. Siguiente cancion                |" << endl;
    cout << "  |  3. Cancion anterior                 |" << endl;
    cout << "  |  4. Ver cancion actual               |" << endl;
    cout << "  |  5. Mostrar playlist completa        |" << endl;
    cout << "  |  6. Buscar cancion                   |" << endl;
    cout << "  |  7. Eliminar cancion                 |" << endl;
    cout << "  |  8. Salir                            |" << endl;
    cout << "  |______________________________________|" << endl;
    cout << "  Opcion: ";
}

void separador() {
    cout << "  ----------------------------------------" << endl;
}


// OPCIONES DEL MENÚ

// Opción 1: Agregar canción
//Inserta una nueva canción al FINAL de la lista
void opAgregar(Playlist<string>& pl) {
    separador();
    cout << "  Nombre de la cancion: ";

    limpiarBuffer(); // limpia antes de leer texto
    string cancion;
    getline(cin, cancion); // permite espacios

    // Validación: no permitir vacío
    if (cancion.empty()) {
        cout << "Error: Se debe ingresar una cancion" << endl;
        return;
    }

    pl.agregarCancion(cancion); // se agrega a la lista
    cout << "  Listo...cancion agregada a la lista" << endl;
}

// Opción 2: Siguiente canción
// Mueve el puntero actual hacia adelante
void opSiguiente(Playlist<string>& pl) {
    separador();

    if (pl.estaVacia()) {
        cout << "  Playlist vacia." << endl;
        return;
    }

    pl.siguiente(); // avanza al siguiente nodo
}

// Opción 3: Canción anterior
// Mueve el puntero actual hacia atrás
void opAnterior(Playlist<string>& pl) {
    separador();

    if (pl.estaVacia()) {
        cout << "  Playlist vacia." << endl;
        return;
    }

    pl.anterior(); // retrocede al nodo anterior
}

// Opción 4: Ver canción actual
// Muestra la canción donde está el puntero "actual"
void opActual(Playlist<string>& pl) {
    separador();
    pl.reproducirActual();
}

// Opción 5: Mostrar toda la lista
// Recorre toda la lista desde el inicio
void opMostrar(Playlist<string>& pl) {
    separador();
    cout << "  PLAYLIST (" << pl.obtenerTamanio() << " canciones)" << endl;
    separador();

    pl.mostrarPlaylist(); // imprime cada nodo
}

// Opción 6: Buscar canción
// Recorre la lista y verifica si existe (búsqueda lineal)
void opBuscar(Playlist<string>& pl) {
    separador();
    cout << "  Cancion a buscar: ";

    limpiarBuffer();
    string cancion;
    getline(cin, cancion);

    if (pl.buscar(cancion))
        cout << "  Listo...Encontrada." << endl;
    else
        cout << "  No se encontro la cancion" << endl;
}

// Opción 7: Eliminar canción
// Busca la canción y la elimina reconectando nodos
void opEliminar(Playlist<string>& pl) {
    separador();

    if (pl.estaVacia()) {
        cout << "  Playlist vacia." << endl;
        return;
    }

    cout << "  Cancion a eliminar: ";

    limpiarBuffer();
    string cancion;
    getline(cin, cancion);

    if (pl.eliminarCancion(cancion))
        cout << "   Cancion eliminada." << endl;
    else
        cout << "   No se encontro la cancion." << endl;
}

// FUNCIÓN PRINCIPAL

int main() {

    // Se crea la lista (estructura dinámica)
    Playlist<string> pl;

    // Se agregan canciones iniciales 
    pl.agregarCancion("Niño Bendecido - Jose Ordoñez");
    pl.agregarCancion("La Fila - Hakuna Group");

    encabezado(); // muestra título

    int opcion = 0;

    // Ciclo principal del programa
    // Se repite hasta que el usuario elija salir (8)
    do {
        menuPrincipal();
        cin >> opcion;

        switch (opcion) {
            case 1: opAgregar(pl); break;   // insertar
            case 2: opSiguiente(pl); break; // avanzar
            case 3: opAnterior(pl); break;  // retroceder
            case 4: opActual(pl); break;    // mostrar actual
            case 5: opMostrar(pl); break;   // mostrar todo
            case 6: opBuscar(pl); break;    // buscar
            case 7: opEliminar(pl); break;  // eliminar
        }

    } while (opcion != 8); 

    return 0;
}
