#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <iostream>
#include <string>
using namespace std;

//creacion de la plantilla Template
template <typename T>
struct Nodo {
    T        info;
    Nodo<T>* siguiente;

    Nodo(T valor) : info(valor), siguiente(nullptr) {}
};

//  PLAYLIST-Lista Simplemente Enlazada
template <typename T>
class Playlist {
private:
    Nodo<T>* primero;
    Nodo<T>* ultimo;
    Nodo<T>* actual;     // cancion en reproduccion
    int      tamanio;

public:
    Playlist();
    ~Playlist();

    void agregarCancion(T cancion);   // inserta al final  O(1)
    void siguiente();                 // avanza al siguiente nodo O(1)
    void anterior();                  // retrocede (recorre desde primero) O(n)
    void reproducirActual() const;
    void mostrarPlaylist()  const;
    bool eliminarCancion(T cancion);
    bool buscar(T cancion)  const;
    bool estaVacia()        const;
    int  obtenerTamanio()   const;
};

//implementacion de template

template <typename T>
Playlist<T>::Playlist()
    : primero(nullptr), ultimo(nullptr), actual(nullptr), tamanio(0) {}

template <typename T>
Playlist<T>::~Playlist() {
    Nodo<T>* nodo = primero;
    while (nodo != nullptr) {
        Nodo<T>* temp = nodo->siguiente;
        delete nodo;
        nodo = temp;
    }
}

//implementacion agreegar cancion
template <typename T>
void Playlist<T>::agregarCancion(T cancion) {
    Nodo<T>* nuevo = new Nodo<T>(cancion);
    if (primero == nullptr) {
        primero = ultimo = nuevo;
        actual  = primero;
    } else {
        ultimo->siguiente = nuevo;
        ultimo            = nuevo;
    }
    tamanio++;
}


// siguiente  —  O(1)
// Si ya estamos en el ultimo, avisa que no hay siguiente

template <typename T>
void Playlist<T>::siguiente() {
    if (actual == nullptr) {
        cout << "  [!] La playlist esta vacia." << endl;
        return;
    }
    if (actual->siguiente == nullptr) {
        cout << "  [!] Ya estas en la ultima cancion." << endl;
        cout << "  >> Reproduciendo: " << actual->info << endl;
        return;
    }
    actual = actual->siguiente;
    cout << "  >> Reproduciendo: " << actual->info << endl;
}


// anterior  —  O(n)
// Recorre desde primero hasta encontrar el nodo cuyo
// siguiente == actual  (unica forma en lista simplemente enlazada)

template <typename T>
void Playlist<T>::anterior() {
    if (actual == nullptr) {
        cout << "  [!] La playlist esta vacia." << endl;
        return;
    }
    if (actual == primero) {
        cout << "  [!] Ya estas en la primera cancion." << endl;
        cout << "  << Reproduciendo: " << actual->info << endl;
        return;
    }
    Nodo<T>* prev = primero;
    while (prev->siguiente != actual) {
        prev = prev->siguiente;
    }
    actual = prev;
    cout << "  << Reproduciendo: " << actual->info << endl;
}


// reproducirActual

template <typename T>
void Playlist<T>::reproducirActual() const {
    if (actual == nullptr) {
        cout << "  [!] No hay canciones en la playlist." << endl;
        return;
    }
    cout << "  >> Reproduciendo: " << actual->info << endl;
}


// mostrarPlaylist  —  O(n)
// Marca con [*] la cancion actual

template <typename T>
void Playlist<T>::mostrarPlaylist() const {
    if (primero == nullptr) {
        cout << "  [lista vacia]" << endl;
        return;
    }
    Nodo<T>* nodo = primero;
    int pos = 1;
    while (nodo != nullptr) {
        string marca = (nodo == actual) ? " [*]" : "    ";
        cout << marca << " " << pos++ << ". " << nodo->info << endl;
        nodo = nodo->siguiente;
    }
}


// eliminarCancion  —  O(n)

template <typename T>
bool Playlist<T>::eliminarCancion(T cancion) {
    if (primero == nullptr) return false;

    // caso: el primero es el que se elimina
    if (primero->info == cancion) {
        Nodo<T>* temp = primero;
        if (actual == primero) actual = primero->siguiente;
        primero = primero->siguiente;
        if (primero == nullptr) ultimo = actual = nullptr;
        delete temp;
        tamanio--;
        return true;
    }

    Nodo<T>* anterior = primero;
    Nodo<T>* nodo     = primero->siguiente;
    while (nodo != nullptr) {
        if (nodo->info == cancion) {
            if (actual == nodo) actual = nodo->siguiente ? nodo->siguiente : anterior;
            anterior->siguiente = nodo->siguiente;
            if (nodo == ultimo) ultimo = anterior;
            delete nodo;
            tamanio--;
            return true;
        }
        anterior = nodo;
        nodo     = nodo->siguiente;
    }
    return false;
}


// buscar  —  O(n)

template <typename T>
bool Playlist<T>::buscar(T cancion) const {
    Nodo<T>* nodo = primero;
    while (nodo != nullptr) {
        if (nodo->info == cancion) return true;
        nodo = nodo->siguiente;
    }
    return false;
}

template <typename T>
bool Playlist<T>::estaVacia() const { return primero == nullptr; }

template <typename T>
int Playlist<T>::obtenerTamanio() const { return tamanio; }

#endif
