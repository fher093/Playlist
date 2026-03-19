#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <iostream>
#include <string>
using namespace std;

//  NODO  —  Doblemente enlazado
template <typename T>
struct Nodo {
    T        info;
    Nodo<T>* siguiente;
    Nodo<T>* anterior;   // puntero nuevo 

    Nodo(T valor) : info(valor), siguiente(NULL), anterior(NULL) {}
};

// Lista Doblemente Enlazada
template <typename T>
class Playlist {
private:
    Nodo<T>* primero;
    Nodo<T>* ultimo;
    Nodo<T>* actual;     // reproduccion 
    int      tamanio;

public:
    Playlist();
    ~Playlist();

    void agregarCancion(T cancion);   // inserta al final 
    void siguiente();                 // avanza al siguiente nodo 
    void anterior();                  // retrocede al nodo anterior 
    void reproducirActual() const;
    void mostrarPlaylist()  const;
    bool eliminarCancion(T cancion);
    bool buscar(T cancion)  const;
    bool estaVacia()        const;
    int  obtenerTamanio()   const;
};

//  Implementacion 

template <typename T>
Playlist<T>::Playlist()
    : primero(NULL), ultimo(NULL), actual(NULL), tamanio(0) {}

template <typename T>
Playlist<T>::~Playlist() {
    Nodo<T>* nodo = primero;
    while (nodo != NULL) {
        Nodo<T>* temp = nodo->siguiente;
        delete nodo;
        nodo = temp;
    }
}

// Agregar Cancion 
template <typename T>
void Playlist<T>::agregarCancion(T cancion) {
    Nodo<T>* nuevo = new Nodo<T>(cancion);
    if (primero == NULL) {
        primero = ultimo = nuevo;
        actual  = primero;
    } else {
        nuevo->anterior   = ultimo;   // dirección hacia atras
        ultimo->siguiente = nuevo;
        ultimo            = nuevo;
    }
    tamanio++;
}

// siguiente  

template <typename T>
void Playlist<T>::siguiente() {
    if (actual == NULL) {
        cout << "  [!] La playlist esta vacia." << endl;
        return;
    }
    if (actual->siguiente == NULL) {
        cout << "  [!] Ya estas en la ultima cancion." << endl;
        cout << "  >> Reproduciendo: " << actual->info << endl;
        return;
    }
    actual = actual->siguiente;
    cout << "  >> Reproduciendo: " << actual->info << endl;
}

// anterior  

template <typename T>
void Playlist<T>::anterior() {
    if (actual == NULL) {
        cout << "  [!] La playlist esta vacia." << endl;
        return;
    }
    if (actual->anterior == NULL) {   // ya estamos en el primero
        cout << "  [!] Ya estas en la primera cancion." << endl;
        cout << "  << Reproduciendo: " << actual->info << endl;
        return;
    }
    actual = actual->anterior;           // salto directo 
    cout << "  << Reproduciendo: " << actual->info << endl;
}

// Reproducir cancion actual 
template <typename T>
void Playlist<T>::reproducirActual() const {
    if (actual == NULL) {
        cout << "  [!] No hay canciones en la playlist." << endl;
        return;
    }
    cout << "  >> Reproduciendo: " << actual->info << endl;
}

// mostrarPlaylist 
// Marca con [*] la cancion actual
template <typename T>
void Playlist<T>::mostrarPlaylist() const {
    if (primero == NULL) {
        cout << "  [lista vacia]" << endl;
        return;
    }
    Nodo<T>* nodo = primero;
    int pos = 1;
    while (nodo != NULL) {
        string marca = (nodo == actual) ? " [*]" : "    ";
        cout << marca << " " << pos++ << ". " << nodo->info << endl;
        nodo = nodo->siguiente;
    }
}

// Eliminar Cancion 
// Se actualizan los punteros anterior y siguiente de los vecinos
template <typename T>
bool Playlist<T>::eliminarCancion(T cancion) {
    Nodo<T>* nodo = primero;

    while (nodo != NULL) {
        if (nodo->info == cancion) {

            // Ajustar actual antes de borrar
            if (actual == nodo) {
                actual = nodo->siguiente ? nodo->siguiente : nodo->anterior;
            }

            // Reconectar vecinos
            if (nodo->anterior != NULL)          // no es el primero
                nodo->anterior->siguiente = nodo->siguiente;
            else                                    // era el primero
                primero = nodo->siguiente;

            if (nodo->siguiente != NULL)         // no es el ultimo
                nodo->siguiente->anterior = nodo->anterior;
            else                                    // era el ultimo
                ultimo = nodo->anterior;

            delete nodo;
            tamanio--;
            return true;
        }
        nodo = nodo->siguiente;
    }
    return false;   // no se encontro la cancion
}


// buscar  —  O(n)

template <typename T>
bool Playlist<T>::buscar(T cancion) const {
    Nodo<T>* nodo = primero;
    while (nodo != NULL) {
        if (nodo->info == cancion) return true;
        nodo = nodo->siguiente;
    }
    return false;
}

template <typename T>
bool Playlist<T>::estaVacia() const { return primero == NULL; }

template <typename T>
int Playlist<T>::obtenerTamanio() const { return tamanio; }

#endif
