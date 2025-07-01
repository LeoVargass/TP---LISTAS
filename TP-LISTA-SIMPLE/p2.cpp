#include <iostream>
using namespace std;

// --- Definiciones básicas ---
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

// --- Operaciones sobre la lista ---

// Inicializa la lista vacía
void iniciar_lista(tlista &L) {
    L.inicio   = nullptr;
    L.final    = nullptr;
    L.contador = 0;
}

// Crea un nuevo nodo pidiendo el valor por teclado
void crear_nodo(pnodo &nuevo) {
    nuevo = new tnodo;
    if (nuevo != nullptr) {
        cout << "Ingrese valor: ";
        cin  >> nuevo->dato;
        nuevo->siguiente = nullptr;
    } else {
        cout << "Memoria insuficiente" << endl;
    }
}

// Agrega un nodo al final y actualiza el contador
void agregar_final(tlista &L, pnodo nuevo) {
    if (L.inicio == nullptr) {
        L.inicio = L.final = nuevo;
    } else {
        L.final->siguiente = nuevo;
        L.final            = nuevo;
    }
    L.contador++;
}

// Elimina un nodo con valor específico y actualiza el contador; retorna true si se eliminó
bool eliminar_nodo(tlista &L, int valor) {
    if (L.inicio == nullptr) {
        return false;
    }
    pnodo act = L.inicio;
    pnodo ant = nullptr;
    // buscar
    while (act != nullptr && act->dato != valor) {
        ant = act;
        act = act->siguiente;
    }
    if (act == nullptr) {
        // no encontrado
        return false;
    }
    // desconectar
    if (ant == nullptr) {
        // es el primero
        L.inicio = act->siguiente;
    } else {
        ant->siguiente = act->siguiente;
    }
    if (act == L.final) {
        // si era el último, actualizar final
        L.final = ant;
    }
    delete act;
    L.contador--;
    return true;
}

// Retorna el número de elementos actuales en la lista
int cantidad_elementos(const tlista &L) {
    return L.contador;
}

// Muestra la lista completa
void mostrar_lista(const tlista &L) {
    if (L.inicio == nullptr) {
        cout << "Lista vacía\n";
        return;
    }
    cout << "Elementos: ";
    for (pnodo i = L.inicio; i != nullptr; i = i->siguiente) {
        cout << i->dato << " ";
    }
    cout << "\n";
}

// --- Función principal ---
int main() {
    tlista lista;
    iniciar_lista(lista);

    int nAgregar;
    cout << "¿Cuántos elementos quiere agregar? ";
    cin  >> nAgregar;

    // Agregar uno por uno
    for (int i = 0; i < nAgregar; i++) {
        pnodo nuevo;
        crear_nodo(nuevo);
        agregar_final(lista, nuevo);
    }

    cout << "\nLista inicial:\n";
    mostrar_lista(lista);
    cout << "Total de elementos: " << cantidad_elementos(lista) << "\n\n";

    int nEliminar;
    cout << "¿Cuántos elementos quiere eliminar? ";
    cin  >> nEliminar;

    // Eliminar por valor, preguntando cada vez
    for (int i = 0; i < nEliminar; i++) {
        int valor;
        cout << "Ingrese el valor a eliminar #" << (i+1) << ": ";
        cin  >> valor;
        bool ok = eliminar_nodo(lista, valor);
        if (ok) {
            cout << "Se eliminó el valor " << valor << ".\n";
        } else {
            cout << "No se encontró el valor " << valor << " en la lista.\n";
        }
        cout << "Elementos restantes: " << cantidad_elementos(lista) << "\n";
    }

    cout << "\nResultado final:\n";
    mostrar_lista(lista);
    cout << "Total de elementos finales: " << cantidad_elementos(lista) << "\n";

    return 0;
}
