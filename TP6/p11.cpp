#include <iostream>
using namespace std;

// === Definición del Nodo para Lista Doblemente Enlazada ===
typedef struct tnodo* pnodo;
struct tnodo {
    int dato;
    pnodo sig;
    pnodo ant;
};

// === Operaciones Fundamentales ===

void IniciarLista(pnodo &inicio) {
    inicio = nullptr;
}

// c) Crear un nodo con valor especificado
void CrearNodo(pnodo &nuevo, int valor) {
    nuevo = new tnodo;
    if (nuevo != nullptr) {
        nuevo->dato = valor;
        nuevo->sig  = nullptr;
        nuevo->ant  = nullptr;
    }
    else {
        cout << "Error: memoria insuficiente\n";
    }
}

// d) Agregar al inicio
void AgregarInicio(pnodo &inicio, pnodo nuevo) {
    if (inicio == nullptr) {
        inicio = nuevo;
    } else {
        nuevo->sig       = inicio;
        inicio->ant      = nuevo;
        inicio          = nuevo;
    }
}

// e) Agregar al final
void AgregarFinal(pnodo &inicio, pnodo nuevo) {
    if (inicio == nullptr) {
        inicio = nuevo;
    } else {
        pnodo it = inicio;
        while (it->sig != nullptr)
            it = it->sig;
        it->sig   = nuevo;
        nuevo->ant = it;
    }
}

// f) Agregar en orden ascendente por dato
void AgregarOrden(pnodo &inicio, pnodo nuevo) {
    if (inicio == nullptr) {
        inicio = nuevo;
    }
    else if (nuevo->dato < inicio->dato) {
        // corresponde antes del primero
        nuevo->sig       = inicio;
        inicio->ant      = nuevo;
        inicio          = nuevo;
    }
    else {
        // buscar posición
        pnodo it = inicio;
        while (it->sig != nullptr && it->sig->dato < nuevo->dato)
            it = it->sig;
        // insertar después de it
        nuevo->sig = it->sig;
        nuevo->ant = it;
        if (it->sig != nullptr)
            it->sig->ant = nuevo;
        it->sig = nuevo;
    }
}

// g) Quitar el primer nodo
pnodo QuitarInicio(pnodo &inicio) {
    if (inicio == nullptr)
        return nullptr;
    pnodo extraido = inicio;
    inicio = inicio->sig;
    if (inicio != nullptr)
        inicio->ant = nullptr;
    extraido->sig = extraido->ant = nullptr;
    return extraido;
}

// h) Quitar el último nodo
pnodo QuitarFinal(pnodo &inicio) {
    if (inicio == nullptr)
        return nullptr;
    pnodo it = inicio;
    // avanzar hasta el último
    while (it->sig != nullptr)
        it = it->sig;
    // it es el último
    pnodo extraido = it;
    if (it->ant != nullptr) {
        it->ant->sig = nullptr;
    } else {
        // era el único
        inicio = nullptr;
    }
    extraido->sig = extraido->ant = nullptr;
    return extraido;
}

// i) Quitar un nodo específico por valor
pnodo QuitarNodo(pnodo &inicio, int valor) {
    if (inicio == nullptr)
        return nullptr;
    // si es el primero
    if (inicio->dato == valor)
        return QuitarInicio(inicio);
    // buscar
    pnodo it = inicio->sig;
    while (it != nullptr && it->dato != valor)
        it = it->sig;
    if (it == nullptr)
        return nullptr;
    // desconectar it
    pnodo extraido = it;
    it->ant->sig = it->sig;
    if (it->sig != nullptr)
        it->sig->ant = it->ant;
    extraido->sig = extraido->ant = nullptr;
    return extraido;
}

// j) Buscar si existe un valor
bool BuscarNodo(pnodo inicio, int valor) {
    pnodo it = inicio;
    while (it != nullptr) {
        if (it->dato == valor)
            return true;
        it = it->sig;
    }
    return false;
}

// k) Mostrar la lista de principio a fin
void MostrarLista(pnodo inicio) {
    if (inicio == nullptr) {
        cout << "[Lista vacía]\n";
        return;
    }
    pnodo it = inicio;
    cout << "Lista: ";
    while (it != nullptr) {
        cout << it->dato << (it->sig ? " <-> " : "\n");
        it = it->sig;
    }
}

// === Ejemplo de uso en main() ===
int main() {
    pnodo lista;
    IniciarLista(lista);

    for (int v : {10, 5, 20, 15}) {
        pnodo n;
        CrearNodo(n, v);
        AgregarFinal(lista, n);
    }
    cout << "Despues de AgregarFinal: \n"; MostrarLista(lista);

    pnodo n1; CrearNodo(n1, 2);
    AgregarInicio(lista, n1);
    cout << "Despues de AgregarInicio(2): \n"; MostrarLista(lista);

    // Agregar en orden
    pnodo n2; CrearNodo(n2, 12);
    AgregarOrden(lista, n2);
    cout << "Despues de AgregarOrden(12): \n"; MostrarLista(lista);

    // Buscar
    cout << "Existe 20? " << (BuscarNodo(lista,20)?"Sí":"No") << "\n";
    cout << "Existe 7? "  << (BuscarNodo(lista,7)?"Sí":"No") << "\n";

    // Quitar inicio
    pnodo q = QuitarInicio(lista);
    cout << "QuitarInicio(): " << q->dato << "\n"; delete q;
    MostrarLista(lista);

    // Quitar final
    q = QuitarFinal(lista);
    cout << "QuitarFinal(): " << q->dato << "\n"; delete q;
    MostrarLista(lista);

    q = QuitarNodo(lista, 12);
    cout << "QuitarNodo(12): " << (q? to_string(q->dato) : string("no hallado")) << "\n";
    if (q) delete q;
    MostrarLista(lista);

    return 0;
}
