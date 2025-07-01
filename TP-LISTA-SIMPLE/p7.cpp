/*
Profe, aca le describo lo que hace cada fragmento de codigo: 
void enigma(Nodo* nodo)
{
if(nodo!=nullptr)
if(nodo->getSiguiente() == nullptr)
cout << nodo->getDato() << endl;
else{
enigma(nodo->getSiguiente());
cout << nodo->getDato() << endl;
}
}
Esto es una funcion recursiva que muestra los datos de una lista en orden inverso. Dado el nodo HEAD, va avanzando hasta que llega al final de la lista 
y empieza a mostrar todos los datos.

====================================================================

int misterio (Nodo* nodo)
{
if(nodo == nullptr)
return 0;
else
return misterio(nodo->getSiguiente()) + 1;
}
Esta funcion recursiva basicamente calcula la cantidad de elementos que tiene uan lista, ya que en cada recursion le aumenta uno al "contador" , hasta llegar al caso base que es el nodo final o el nodo que apunta a un valor nulo


===============================================================================

Nodo* desconocido(Nodo* nodo)
{
if(nodo == nullptr || nodo ->getSiguiente() ==
nullptr)
return nodo;
else
return desconocido(nodo->getSiguiente());
}

Esta funcion, de nuevo recursiva, basicamente devuelve un puntero al ultimo nodo de la lista.
La condicion de si nodo es nullptr es por si aun no hay elementos en la lista.
*/

#include <iostream>
using namespace std;

// === Clase Nodo ===
class Nodo {
private:
    int dato;
    Nodo* sig;
public:
    Nodo(int dato) {
        this->dato = dato;
        this->sig = nullptr;
    }
    int getDato() const { return dato; }
    Nodo* getSiguiente() const { return sig; }
    void setSiguiente(Nodo* p) { sig = p; }
};

// === Clase Lista Simple con métodos recursivos ===
class Lista {
private:
    Nodo* inicio;
    int cant;
public:
    Lista() {
        inicio = nullptr;
        cant = 0;
    }

    bool estaVacia() const {
        return inicio == nullptr;
    }

    void AgregarFinal(Nodo* nuevo) {
        if (estaVacia()) {
            inicio = nuevo;
        } else {
            Nodo* i = inicio;
            while (i->getSiguiente() != nullptr)
                i = i->getSiguiente();
            i->setSiguiente(nuevo);
        }
        cant++;
    }

    void MostrarLista() const {
        if (estaVacia()) {
            cout << "Lista vacía\n";
            return;
        }
        Nodo* i = inicio;
        while (i != nullptr) {
            cout << i->getDato() << " ";
            i = i->getSiguiente();
        }
        cout << "\n";
    }

    // --- a) enigma: imprime los datos en orden inverso ---
private:
    void enigmaRec(Nodo* nodo) const {
        if (nodo == nullptr) return;
        if (nodo->getSiguiente() == nullptr) {
            cout << nodo->getDato() << endl;
        } else {
            enigmaRec(nodo->getSiguiente());
            cout << nodo->getDato() << endl;
        }
    }
public:
    void Enigma() const {
        enigmaRec(inicio);
    }

    // --- b) misterio: devuelve la longitud de la lista ---
private:
    int misterioRec(Nodo* nodo) const {
        if (nodo == nullptr)
            return 0;
        else
            return 1 + misterioRec(nodo->getSiguiente());
    }
public:
    int Misterio() const {
        return misterioRec(inicio);
    }

    // --- c) desconocido: retorna el último nodo ---
private:
    Nodo* desconocidoRec(Nodo* nodo) const {
        if (nodo == nullptr || nodo->getSiguiente() == nullptr)
            return nodo;
        else
            return desconocidoRec(nodo->getSiguiente());
    }
public:
    Nodo* Desconocido() const {
        return desconocidoRec(inicio);
    }
};

// === MAIN de prueba con la lista 6→4→9→5→8→NULL ===
int main() {
    Lista L;
    L.AgregarFinal(new Nodo(6));
    L.AgregarFinal(new Nodo(4));
    L.AgregarFinal(new Nodo(9));
    L.AgregarFinal(new Nodo(5));
    L.AgregarFinal(new Nodo(8));

    cout << "Lista original: ";
    L.MostrarLista();

    cout << "\nSalida de Enigma (imprime inverso):\n";
    L.Enigma();

    cout << "\nResultado de Misterio (longitud): "
         << L.Misterio() << endl;

    Nodo* ultimo = L.Desconocido();
    if (ultimo) {
        cout << "\nResultado de Desconocido (último nodo): "
             << ultimo->getDato() << endl;
    } else {
        cout << "\nLista vacía, no hay último nodo.\n";
    }

    return 0;
}
