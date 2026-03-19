#include <iostream>
#include <string>
#include <limits>
#include "playlist.h"
using namespace std;


void limpiarBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void separador() {
    cout << "  +--------------------------------------+" << endl;
}

//encebecado del menu
void encabezado() {
    cout << endl;
    cout << "  +--------------------------------------+" << endl;
    cout << "  ¦     REPRODUCTOR DE MUSICA            ¦" << endl;
    cout << "  +--------------------------------------+" << endl;
} 

//impresion del menu principal 

void menuPrincipal() {
    cout << endl;
    cout << "  +--------------------------------------+" << endl;
    cout << "  ¦  1. Agregar cancion                  ¦" << endl;
    cout << "  ¦  2. Siguiente cancion                ¦" << endl;
    cout << "  ¦  3. Cancion anterior                 ¦" << endl;
    cout << "  ¦  4. Ver cancion actual               ¦" << endl;
    cout << "  ¦  5. Mostrar playlist completa        ¦" << endl;
    cout << "  ¦  6. Buscar cancion                   ¦" << endl;
    cout << "  ¦  7. Eliminar cancion                 ¦" << endl;
    cout << "  ¦  8. Salir                            ¦" << endl;
    cout << "  +--------------------------------------+" << endl;
    cout << "  Opcion: ";
}

//metodos para cada operacion 

//metodo agregar

void opAgregar(Playlist<string>& pl) {
    separador();
    cout << "  Nombre de la cancion: ";
    limpiarBuffer();
    string cancion;
    getline(cin, cancion);
    if (cancion.empty()) {
        cout << "  [!] El nombre no puede estar vacio." << endl;
        return;
    }
    pl.agregarCancion(cancion);
    cout << "  [OK] '" << cancion << "' agregada a la playlist." << endl;
    cout << "  Total de canciones: " << pl.obtenerTamanio() << endl;
}

//metodo sigueinte 
void opSiguiente(Playlist<string>& pl) {
    separador();
    if (pl.estaVacia()) {
        cout << "  [!] La playlist esta vacia." << endl;
        return;
    }
    pl.siguiente();
}
//metodo anterior 
void opAnterior(Playlist<string>& pl) {
    separador();
    if (pl.estaVacia()) {
        cout << "  [!] La playlist esta vacia." << endl;
        return;
    }
    pl.anterior();
} 

//metodo cancion actual

void opActual(Playlist<string>& pl) {
    separador();
    pl.reproducirActual();
} 

//metodo mostrar cancion

void opMostrar(Playlist<string>& pl) {
    separador();
    cout << "  PLAYLIST  (" << pl.obtenerTamanio() << " canciones)" << endl;
    separador();
    pl.mostrarPlaylist();
    cout << "  [*] = cancion actual" << endl;
} 

//metodo buscar

void opBuscar(Playlist<string>& pl) {
    separador();
    cout << "  Cancion a buscar: ";
    limpiarBuffer();
    string cancion;
    getline(cin, cancion);
    if (pl.buscar(cancion))
        cout << "  [OK] '" << cancion << "' encontrada en la playlist." << endl;
    else
        cout << "  [--] '" << cancion << "' no esta en la playlist." << endl;
} 

//metodo eliminar

void opEliminar(Playlist<string>& pl) {
    separador();
    if (pl.estaVacia()) {
        cout << "  [!] La playlist esta vacia." << endl;
        return;
    }
    cout << "  Cancion a eliminar: ";
    limpiarBuffer();
    string cancion;
    getline(cin, cancion);
    if (pl.eliminarCancion(cancion))
        cout << "  [OK] '" << cancion << "' eliminada." << endl;
    else
        cout << "  [--] '" << cancion << "' no encontrada." << endl;
}

//Clase main, pricipal

int main() {

    Playlist<string> pl;

    // Canciones de ejemplo 
    pl.agregarCancion("Bohemian Rhapsody - Queen");
    pl.agregarCancion("Stairway to Heaven - Led Zeppelin");
    pl.agregarCancion("Hotel California - Eagles");
    pl.agregarCancion("Smells Like Teen Spirit - Nirvana");
    pl.agregarCancion("Imagine - John Lennon");

    encabezado();
    cout << endl;
    cout << "  Playlist cargada con " << pl.obtenerTamanio() << " canciones." << endl;

    int opcion = 0;
//control de flujo para controlar el menu 
    do {
        menuPrincipal();
        cin >> opcion;

        switch (opcion) {
            case 1: opAgregar(pl);   break;
            case 2: opSiguiente(pl); break;
            case 3: opAnterior(pl);  break;
            case 4: opActual(pl);    break;
            case 5: opMostrar(pl);   break;
            case 6: opBuscar(pl);    break;
            case 7: opEliminar(pl);  break;
            case 8:
                separador();
                cout << "  Hasta luego." << endl;
                separador();
                break;
            default:
                cout << "  [!] Opcion invalida. Ingrese un numero del 1 al 8." << endl;
        }

    } while (opcion != 8);

    return 0;
}
