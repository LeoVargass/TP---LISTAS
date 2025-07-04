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

// Elimina todos los nodos cuyos datos sean múltiplos de 3
void EliminarMultiplosDeTres(tlista &lista) {
    pnodo actual = lista.inicio;
    while (actual != nullptr) {
        pnodo siguiente = actual->sig;
        if (actual->dato % 3 == 0) {
            // Desconectar current
            if (actual->ant != nullptr)
                actual->ant->sig = actual->sig;
            else
                // actual era inicio
                lista.inicio = actual->sig;

            if (actual->sig != nullptr)
                actual->sig->ant = actual->ant;
            else
                // actual era fin
                lista.fin = actual->ant;

            delete actual;
        }
        actual = siguiente;
    }
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

    cout << "\nLista original:\n";
    MostrarLista(lista);

    EliminarMultiplosDeTres(lista);

    cout << "\nLista después de eliminar múltiplos de 3:\n";
    MostrarLista(lista);

    // Liberar memoria restante
    pnodo aux;
    while (lista.inicio != nullptr) {
        aux = lista.inicio;
        lista.inicio = aux->sig;
        delete aux;
    }

    return 0;
}
