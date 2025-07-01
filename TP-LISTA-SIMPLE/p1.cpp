#include <iostream>
using namespace std;

typedef struct tnodo *pnodo;

typedef struct tnodo {
    int dato;
    pnodo siguiente;
};

// Iniciar lista (puntero a NULL)
void iniciar_lista(pnodo &lista) {
    lista = NULL;
}

// Crear un nodo nuevo con dato ingresado por teclado
void crear_nodo(pnodo &nuevo) {
    nuevo = new tnodo;
    if (nuevo != NULL) {
        cout << "Ingrese valor: ";
        cin >> nuevo->dato;
        nuevo->siguiente = NULL;
    } else {
        cout << "Memoria insuficiente" << endl;
    }
}

// Agregar al inicio de la lista
void agregar_inicio(pnodo &lista, pnodo nuevo) {
    nuevo->siguiente = lista;
    lista = nuevo;
}

// Agregar al final de la lista
void agregar_final(pnodo &lista, pnodo nuevo) {
    pnodo i;
    if (lista == NULL) {
        lista = nuevo;
    } else {
        for (i = lista; i->siguiente != NULL; i = i->siguiente);
        i->siguiente = nuevo;
    }
}

// Agregar de forma ordenada
void agregar_ordenado(pnodo &lista, pnodo nuevo) {
    pnodo i;
    if (lista == NULL) {
        lista = nuevo;
    } else {
        if (nuevo->dato < lista->dato) {
            nuevo->siguiente = lista;
            lista = nuevo;
        } else {
            for (i = lista; i->siguiente != NULL && nuevo->dato > i->siguiente->dato; i = i->siguiente);
            nuevo->siguiente = i->siguiente;
            i->siguiente = nuevo;
        }
    }
}

// Mostrar todos los nodos de la lista
void mostrar(pnodo lista) {
    pnodo i;
    if (lista != NULL) {
        for (i = lista; i != NULL; i = i->siguiente) {
            cout << "Nodo: " << i->dato << endl;
        }
    } else {
        cout << "Lista vacía" << endl;
    }
}

// Buscar si un valor está en la lista
bool buscar_nodo(pnodo lista, int valor) {
    pnodo i;
    bool encontrado = false;
    if (lista != NULL) {
        for (i = lista; i != NULL && !encontrado; i = i->siguiente) {
            if (i->dato == valor) {
                encontrado = true;
            }
        }
    }
    return encontrado;
}

// Eliminar el primer nodo de la lista
pnodo eliminar_inicio(pnodo &lista) {
    pnodo borrado;
    if (lista == NULL) {
        borrado = NULL;
    } else {
        borrado = lista;
        lista = lista->siguiente;
        borrado->siguiente = NULL;
    }
    return borrado;
}

// Eliminar el último nodo de la lista
pnodo eliminar_final(pnodo &lista) {
    pnodo borrado, i;
    if (lista == NULL) {
        borrado = NULL;
    } else {
        if (lista->siguiente == NULL) {
            borrado = lista;
            lista = NULL;
        } else {
            for (i = lista; i->siguiente->siguiente != NULL; i = i->siguiente);
            borrado = i->siguiente;
            i->siguiente = NULL;
        }
    }
    return borrado;
}

// Eliminar un nodo con un valor específico
pnodo eliminar_nodo(pnodo &lista, int valor) {
    pnodo borrado, i;
    if (lista == NULL) {
        borrado = NULL;
    } else {
        if (lista->dato == valor) {
            borrado = lista;
            lista = borrado->siguiente;
            borrado->siguiente = NULL;
        } else {
            for (i = lista; i->siguiente != NULL && i->siguiente->dato != valor; i = i->siguiente);
            if (i->siguiente != NULL) {
                borrado = i->siguiente;
                i->siguiente = borrado->siguiente;
                borrado->siguiente = NULL;
            } else {
                borrado = NULL;
            }
        }
    }
    return borrado;
}

pnodo extraer_minimo(pnodo &lista) {
    if (lista == NULL) {
        cout << "La lista está vacía." << endl;
        return NULL;
    }

    pnodo min = lista;
    pnodo antMin = NULL;

    pnodo actual = lista;
    pnodo anterior = NULL;

    while (actual != NULL) {
        if (actual->dato < min->dato) {
            min = actual;
            antMin = anterior;
        }
        anterior = actual;
        actual = actual->siguiente;
    }

    if (antMin == NULL) {
        lista = lista->siguiente;
    } else {
        antMin->siguiente = min->siguiente;
    }

    min->siguiente = NULL;
    return min;
}

int main() {
    pnodo lista;
    iniciar_lista(lista);

    pnodo nuevo;

    cout << "Cargando lista:\n";
    for (int i = 0; i < 4; i++) {
        crear_nodo(nuevo);
        agregar_final(lista, nuevo);
    }

    cout << "\nLista original:\n";
    mostrar(lista);

    pnodo extraido = extraer_minimo(lista);
    if (extraido != NULL) {
        cout << "\nMinimo extraido: " << extraido->dato << endl;
        delete extraido;
    }

    cout << "\nLista luego de extraer minimo:\n";
    mostrar(lista);

    return 0;
}
