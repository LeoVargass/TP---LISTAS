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

// a) Inicializar lista vacía
void IniciarLista(tlista &lista) {
    lista.inicio = nullptr;
    lista.fin    = nullptr;
}

// b) Crear nodo con valor dado
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

// c) Agregar al inicio
void AgregarInicio(tlista &lista, pnodo nuevo) {
    if (lista.inicio == nullptr) {
        lista.inicio = lista.fin = nuevo;
    } else {
        nuevo->sig              = lista.inicio;
        lista.inicio->ant       = nuevo;
        lista.inicio            = nuevo;
    }
}

// d) Agregar al final
void AgregarFinal(tlista &lista, pnodo nuevo) {
    if (lista.inicio == nullptr) {
        lista.inicio = lista.fin = nuevo;
    } else {
        lista.fin->sig   = nuevo;
        nuevo->ant       = lista.fin;
        lista.fin        = nuevo;
    }
}

// e) Quitar el primer nodo y retornarlo (o NULL si la lista está vacía)
pnodo QuitarInicio(tlista &lista) {
    if (lista.inicio == nullptr) {
        // lista vacía
        return nullptr;
    }
    pnodo extraido = lista.inicio;
    if (lista.inicio == lista.fin) {
        // solo un nodo
        lista.inicio = lista.fin = nullptr;
    } else {
        // más de un nodo
        lista.inicio         = extraido->sig;
        lista.inicio->ant    = nullptr;
        extraido->sig        = nullptr;
    }
    return extraido;
}

// f) Quitar el último nodo y retornarlo (o NULL si la lista está vacía)
pnodo QuitarFinal(tlista &lista) {
    if (lista.fin == nullptr) {
        // lista vacía
        return nullptr;
    }
    pnodo extraido = lista.fin;
    if (lista.inicio == lista.fin) {
        // solo un nodo
        lista.inicio = lista.fin = nullptr;
    } else {
        // más de un nodo
        lista.fin           = extraido->ant;
        lista.fin->sig      = nullptr;
        extraido->ant       = nullptr;
    }
    return extraido;
}

// g) Buscar un valor en la lista
bool BuscarNodo(tlista &lista, int valor) {
    for (pnodo it = lista.inicio; it != nullptr; it = it->sig) {
        if (it->dato == valor) return true;
    }
    return false;
}

// h) Mostrar toda la lista de inicio a fin
void MostrarLista(const tlista &lista) {
    if (lista.inicio == nullptr) {
        cout << "[Lista vacía]\n";
        return;
    }
    for (pnodo it = lista.inicio; it != nullptr; it = it->sig) {
        cout << it->dato
             << (it->sig ? " <-> " : "\n");
    }
}

int main() {
    tlista lista;
    IniciarLista(lista);

    pnodo nodo;

    // Prueba: agrego algunos valores
    for (int v : { 10, 20, 30 }) {
        CrearNodo(nodo, v);
        AgregarFinal(lista, nodo);
    }
    cout << "Lista tras AgregarFinal(10,20,30):\n"; 
    MostrarLista(lista);

    CrearNodo(nodo, 5);
    AgregarInicio(lista, nodo);
    cout << "Lista tras AgregarInicio(5):\n"; 
    MostrarLista(lista);

    // Quitar inicio
    pnodo q = QuitarInicio(lista);
    cout << "QuitarInicio(): " 
         << (q ? to_string(q->dato) : string("NULL")) << "\n";
    delete q;
    MostrarLista(lista);

    // Quitar final
    q = QuitarFinal(lista);
    cout << "QuitarFinal(): " 
         << (q ? to_string(q->dato) : string("NULL")) << "\n";
    delete q;
    MostrarLista(lista);

    return 0;
}
