#include <iostream>
using namespace std;

// --- Definición del Nodo ---
typedef struct tnodo *pnodo;
typedef struct tnodo {
    int dato;
    pnodo siguiente;
};

// --- Definición de la Lista con inicio, final y contador ---
typedef struct {
    pnodo inicio;
    pnodo final;
    int contador;
} tlista;

// --- Operaciones básicas sobre la lista ---

void iniciar_lista(tlista &lista) {
    lista.inicio   = NULL;
    lista.final    = NULL;
    lista.contador = 0;
}

void crear_nodo(pnodo &nuevo) {
    nuevo = new tnodo;
    if (nuevo != NULL) {
        cout << "Ingrese valor: ";
        cin  >> nuevo->dato;
        nuevo->siguiente = NULL;
    } else {
        cout << "Memoria insuficiente" << endl;
    }
}

void agregar_inicio(tlista &lista, pnodo nuevo) {
    nuevo->siguiente = lista.inicio;
    lista.inicio     = nuevo;
    if (lista.final == NULL)
        lista.final = nuevo;
    lista.contador++;
}

void agregar_final(tlista &lista, pnodo nuevo) {
    if (lista.inicio == NULL) {
        lista.inicio = lista.final = nuevo;
    } else {
        lista.final->siguiente = nuevo;
        lista.final            = nuevo;
    }
    lista.contador++;
}

void mostrar(const tlista &lista) {
    if (lista.inicio == NULL) {
        cout << "Lista vacía\n";
        return;
    }
    for (pnodo i = lista.inicio; i != NULL; i = i->siguiente)
        cout << "Nodo: " << i->dato << "\n";
}

pnodo eliminar_inicio(tlista &lista) {
    if (lista.inicio == NULL) return NULL;
    pnodo borrado = lista.inicio;
    lista.inicio  = borrado->siguiente;
    if (lista.inicio == NULL) lista.final = NULL;
    borrado->siguiente = NULL;
    lista.contador--;
    return borrado;
}

pnodo eliminar_final(tlista &lista) {
    if (lista.inicio == NULL) return NULL;
    pnodo borrado;
    if (lista.inicio == lista.final) {
        borrado         = lista.inicio;
        lista.inicio    = lista.final = NULL;
    } else {
        pnodo i = lista.inicio;
        while (i->siguiente != lista.final)
            i = i->siguiente;
        borrado            = lista.final;
        i->siguiente       = NULL;
        lista.final        = i;
    }
    lista.contador--;
    return borrado;
}

pnodo eliminar_nodo(tlista &lista, int valor) {
    if (lista.inicio == NULL) return NULL;
    pnodo borrado = NULL;
    if (lista.inicio->dato == valor) {
        borrado       = lista.inicio;
        lista.inicio  = borrado->siguiente;
        if (!lista.inicio) lista.final = NULL;
    } else {
        pnodo i = lista.inicio;
        while (i->siguiente && i->siguiente->dato != valor)
            i = i->siguiente;
        if (i->siguiente) {
            borrado         = i->siguiente;
            i->siguiente    = borrado->siguiente;
            if (borrado == lista.final) lista.final = i;
        }
    }
    if (borrado) {
        borrado->siguiente = NULL;
        lista.contador--;
    }
    return borrado;
}

int cantidad_elementos(const tlista &lista) {
    return lista.contador;
}

// --- Funciones solicitadas ---

// a) Busca un valor y devuelve su índice 0-based, o -1 si no está
int buscar_indice(const tlista &lista, int valor) {
    int idx = 0;
    for (pnodo i = lista.inicio; i != NULL; i = i->siguiente, idx++) {
        if (i->dato == valor)
            return idx;
    }
    return -1;
}

// b) Devuelve el puntero al nodo en la posición lógica 'indice' (0-based), o NULL
pnodo buscar_por_indice(const tlista &lista, int indice) {
    if (indice < 0 || indice >= lista.contador)
        return NULL;
    int idx = 0;
    pnodo i = lista.inicio;
    while (idx < indice) {
        i = i->siguiente;
        idx++;
    }
    return i;
}

// --- Ejemplo de uso ---
int main() {
    tlista lista;
    iniciar_lista(lista);

    pnodo nuevo;
    cout << "Cargando 5 nodos:\n";
    for (int i = 0; i < 5; i++) {
        crear_nodo(nuevo);
        agregar_final(lista, nuevo);
    }

    cout << "\nLista actual (" << cantidad_elementos(lista) << " nodos):\n";
    mostrar(lista);

    // Prueba buscar_indice
    int v;
    cout << "\nIngrese valor a buscar su índice: ";
    cin >> v;
    int pos = buscar_indice(lista, v);
    if (pos >= 0)
        cout << "Valor " << v << " está en la posición (0-based): " << pos << "\n";
    else
        cout << "Valor " << v << " no encontrado\n";

    // Prueba buscar_por_indice
    int idx;
    cout << "\nIngrese índice a buscar (0-based): ";
    cin >> idx;
    pnodo nodo = buscar_por_indice(lista, idx);
    if (nodo)
        cout << "En el índice " << idx << " está el valor: " << nodo->dato << "\n";
    else
        cout << "Índice " << idx << " fuera de rango\n";

    return 0;
}
