#include <iostream>
using namespace std;

// --- Definiciones de la lista simplemente enlazada ---
typedef struct tnodo *pnodo;
typedef struct tnodo {
    int dato;
    pnodo siguiente;
} tnodo;

typedef struct {
    pnodo inicio;
    pnodo final;
    int contador;
} tlista;

// Inicializa la lista vacía
void iniciar_lista(tlista &L) {
    L.inicio   = nullptr;
    L.final    = nullptr;
    L.contador = 0;
}

// Crea un nodo leyendo el valor desde teclado
void crear_nodo(pnodo &nuevo) {
    nuevo = new tnodo;
    if (nuevo != nullptr) {
        cout << "Ingrese valor: ";
        cin  >> nuevo->dato;
        nuevo->siguiente = nullptr;
    } else {
        cout << "Memoria insuficiente\n";
    }
}

// Agrega un nodo al inicio de la lista (para Pila)
void agregar_inicio(tlista &L, pnodo nuevo) {
    if (L.inicio == nullptr) {
        L.inicio = L.final = nuevo;
    } else {
        nuevo->siguiente = L.inicio;
        L.inicio         = nuevo;
    }
    L.contador++;
}

// Agrega un nodo al final de la lista (para Cola)
void agregar_final(tlista &L, pnodo nuevo) {
    if (L.inicio == nullptr) {
        L.inicio = L.final = nuevo;
    } else {
        L.final->siguiente = nuevo;
        L.final            = nuevo;
    }
    L.contador++;
}

// Elimina y retorna el nodo al inicio (para desapilar y desencolar)
pnodo eliminar_inicio(tlista &L) {
    if (L.inicio == nullptr) {
        return nullptr;
    }
    pnodo borrado = L.inicio;
    L.inicio      = borrado->siguiente;
    if (L.inicio == nullptr)
        L.final = nullptr;
    borrado->siguiente = nullptr;
    L.contador--;
    return borrado;
}

// Retorna la cantidad de elementos en la lista
int cantidad_elementos(const tlista &L) {
    return L.contador;
}

// Muestra el contenido de la lista
void mostrar_lista(const tlista &L) {
    if (L.inicio == nullptr) {
        cout << "  [vacía]\n";
        return;
    }
    cout << "  [ ";
    for (pnodo i = L.inicio; i != nullptr; i = i->siguiente) {
        cout << i->dato;
        if (i->siguiente) cout << " | ";
    }
    cout << " ]\n";
}

// --- Funciones específicas de Pila y Cola usando la misma lista ---

void apilar(tlista &pila, pnodo nuevo) {
    agregar_inicio(pila, nuevo);
}

pnodo desapilar(tlista &pila) {
    return eliminar_inicio(pila);
}

void encolar(tlista &cola, pnodo nuevo) {
    agregar_final(cola, nuevo);
}

pnodo desencolar(tlista &cola) {
    return eliminar_inicio(cola);
}

// === Main interactivo ===
int main() {
    tlista pila, cola;
    iniciar_lista(pila);
    iniciar_lista(cola);

    int n, i;
    pnodo nodo;

    // ----- Interacción con la pila -----
    cout << "=== PILA (LIFO) ===\n";
    cout << "¿Cuántos elementos desea apilar? ";
    cin >> n;
    for (i = 0; i < n; i++) {
        crear_nodo(nodo);
        apilar(pila, nodo);
    }
    cout << "Pila actual (" << cantidad_elementos(pila) << " elementos):\n";
    mostrar_lista(pila);

    cout << "¿Cuántos elementos desea desapilar? ";
    cin >> n;
    for (i = 0; i < n; i++) {
        pnodo sacado = desapilar(pila);
        if (sacado) {
            cout << "Desapilado: " << sacado->dato << "\n";
            delete sacado;
            cout << "Pila ahora (" << cantidad_elementos(pila) << " elementos):\n";
            mostrar_lista(pila);
        } else {
            cout << "Pila vacía. No hay más elementos.\n";
            break;
        }
    }

    // ----- Interacción con la cola -----
    cout << "\n=== COLA (FIFO) ===\n";
    cout << "¿Cuántos elementos desea encolar? ";
    cin >> n;
    for (i = 0; i < n; i++) {
        crear_nodo(nodo);
        encolar(cola, nodo);
    }
    cout << "Cola actual (" << cantidad_elementos(cola) << " elementos):\n";
    mostrar_lista(cola);

    cout << "¿Cuántos elementos desea desencolar? ";
    cin >> n;
    for (i = 0; i < n; i++) {
        pnodo sacado = desencolar(cola);
        if (sacado) {
            cout << "Desencolado: " << sacado->dato << "\n";
            delete sacado;
            cout << "Cola ahora (" << cantidad_elementos(cola) << " elementos):\n";
            mostrar_lista(cola);
        } else {
            cout << "Cola vacía. No hay más elementos.\n";
            break;
        }
    }

    return 0;
}
