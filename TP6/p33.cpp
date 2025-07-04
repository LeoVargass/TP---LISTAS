#include <iostream>
using namespace std;

// === Definición del Nodo para Lista Doblemente Enlazada ===
typedef struct tnodo *pnodo;
typedef struct tnodo {
    int dato;
    pnodo sig;
    pnodo ant;
} tnodo;

// === Definición de la Lista con puntero a inicio y fin ===
typedef struct tlista {
    pnodo inicio;
    pnodo fin;
} tlista;

// --- Operaciones básicas sobre lista doble ---
// Inicializa lista vacía
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

// Agrega un nodo al inicio
void AgregarInicio(tlista &lista, pnodo nuevo) {
    if (lista.inicio == nullptr) {
        lista.inicio = lista.fin = nuevo;
    } else {
        nuevo->sig            = lista.inicio;
        lista.inicio->ant     = nuevo;
        lista.inicio          = nuevo;
    }
}

// Muestra la lista de principio a fin
void MostrarLista(const tlista &lista) {
    if (lista.inicio == nullptr) {
        cout << "[vacía]\n";
        return;
    }
    for (pnodo it = lista.inicio; it != nullptr; it = it->sig) {
        cout << it->dato;
    }
    cout << "\n";
}

// --- Función de conversión de decimal a binario usando la lista ---
// Convierte 'numero' a binario, guardando cada bit en un nodo al inicio.
void DecimalABinario(tlista &lista, int numero) {
    IniciarLista(lista);
    if (numero == 0) {
        pnodo nodo;
        CrearNodo(nodo, 0);
        AgregarInicio(lista, nodo);
        return;
    }
    while (numero > 0) {
        int bit = numero % 2;
        pnodo nodo;
        CrearNodo(nodo, bit);
        AgregarInicio(lista, nodo);
        numero /= 2;
    }
}

int main() {
    tlista listaBin;
    IniciarLista(listaBin);

    int valor;
    cout << "Ingrese un número decimal: ";
    cin  >> valor;

    DecimalABinario(listaBin, valor);

    cout << "Representación binaria: ";
    MostrarLista(listaBin);

    // Liberar memoria
    pnodo aux;
    while (listaBin.inicio != nullptr) {
        aux = listaBin.inicio;
        listaBin.inicio = aux->sig;
        delete aux;
    }

    return 0;
}
