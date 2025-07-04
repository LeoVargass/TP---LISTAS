#include <iostream>
using namespace std;

typedef struct tnodo *pnodo;
typedef struct tnodo {
    int dato;
    pnodo sig;
    pnodo ant;
} tnodo;

typedef struct tlista {
    pnodo inicio;
    pnodo fin;
} tlista;

// Inicializa la lista vacía
void IniciarLista(tlista &lista) {
    lista.inicio = nullptr;
    lista.fin    = nullptr;
}

// Crea un nodo con un valor dado
void CrearNodo(pnodo &nuevo, int valor) {
    nuevo = new tnodo;
    if (nuevo != nullptr) {
        nuevo->dato = valor;
        nuevo->sig  = nullptr;
        nuevo->ant  = nullptr;
    } else {
        cout << "Error: memoria insuficiente\n";
    }
}

// Agrega un nodo al final
void AgregarFinal(tlista &lista, pnodo nuevo) {
    if (lista.inicio == nullptr) {
        lista.inicio = lista.fin = nuevo;
    } else {
        lista.fin->sig   = nuevo;
        nuevo->ant       = lista.fin;
        lista.fin        = nuevo;
    }
}

// Muestra la lista de principio a fin
void MostrarLista(const tlista &lista) {
    if (lista.inicio == nullptr) {
        cout << "[Lista vacía]\n";
        return;
    }
    for (pnodo it = lista.inicio; it != nullptr; it = it->sig) {
        cout << it->dato << (it->sig ? " " : "\n");
    }
}

// --- Función solicitada: mostrar valor mínimo y máximo ---
void MostrarMinimoMaximo(const tlista &lista) {
    if (lista.inicio == nullptr) {
        cout << "La lista está vacía.\n";
        return;
    }
    int minimo = lista.inicio->dato;
    int maximo = lista.inicio->dato;
    for (pnodo it = lista.inicio->sig; it != nullptr; it = it->sig) {
        if (it->dato < minimo) minimo = it->dato;
        if (it->dato > maximo) maximo = it->dato;
    }
    cout << "Valor mínimo: " << minimo << "\n";
    cout << "Valor máximo: " << maximo << "\n";
}

int main() {
    tlista lista;
    IniciarLista(lista);

    int n, v;
    cout << "¿Cuántos valores desea agregar a la lista? ";
    cin  >> n;
    for (int i = 0; i < n; i++) {
        cout << "Ingrese valor #" << (i+1) << ": ";
        cin  >> v;
        pnodo nodo;
        CrearNodo(nodo, v);
        AgregarFinal(lista, nodo);
    }

    cout << "\nContenido de la lista:\n";
    MostrarLista(lista);

    cout << "\nExtremos de la lista:\n";
    MostrarMinimoMaximo(lista);

    // Liberar memoria
    pnodo aux;
    while (lista.inicio != nullptr) {
        aux = lista.inicio;
        lista.inicio = aux->sig;
        delete aux;
    }

    return 0;
}
