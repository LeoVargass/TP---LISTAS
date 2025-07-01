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
    int getDato() { return dato; }
    Nodo* getSiguiente() { return sig; }
    void setDato(int v) { dato = v; }
    void setSiguiente(Nodo* p) { sig = p; }
};

// === Clase Lista Simple ===
class Lista {
private:
    Nodo* inicio;
    int cant;
public:
    Lista() {
        inicio = nullptr;
        cant = 0;
    }

    bool estaVacia() {
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

    void MostrarLista() {
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

    int getCantidad() {
        return cant;
    }

    // --- b) Ordenación por selección ---
    void OrdenarSeleccion() {
        for (Nodo* p = inicio; p != nullptr; p = p->getSiguiente()) {
            Nodo* minNodo = p;
            for (Nodo* q = p->getSiguiente(); q != nullptr; q = q->getSiguiente()) {
                if (q->getDato() < minNodo->getDato())
                    minNodo = q;
            }
            // intercambiar datos p <-> minNodo
            int tmp = p->getDato();
            p->setDato(minNodo->getDato());
            minNodo->setDato(tmp);
        }
    }

    // --- c.i) Combinar sin importar orden ---
    // Simplemente engancha ambos inicios: lista resultante puede quedar mezclada
    void CombinarNoImportaOrden(Lista& otra) {
        if (otra.inicio == nullptr) return;
        if (estaVacia()) {
            inicio = otra.inicio;
        } else {
            // enganchar la otra al frente
            Nodo* tail = otra.inicio;
            // contar nodos de 'otra' para ajustar contador
            int c = 1;
            while (tail->getSiguiente() != nullptr) {
                tail = tail->getSiguiente();
                c++;
            }
            tail->setSiguiente(inicio);
            inicio = otra.inicio;
            cant += c;
        }
        // vaciar la otra lista
        otra.inicio = nullptr;
        otra.cant = 0;
    }

    // --- c.ii) Combinar manteniendo orden ---
    // Agrega al final todos los nodos de 'otra' en orden
    void CombinarManteniendoOrden(Lista& otra) {
        if (otra.inicio == nullptr) return;
        if (estaVacia()) {
            inicio = otra.inicio;
        } else {
            Nodo* i = inicio;
            while (i->getSiguiente() != nullptr)
                i = i->getSiguiente();
            i->setSiguiente(otra.inicio);
        }
        cant += otra.cant;
        otra.inicio = nullptr;
        otra.cant = 0;
    }
};

// === MAIN de prueba ===
int main() {
    // a+b: crear y ordenar
    Lista A, B;
    A.AgregarFinal(new Nodo(7));
    A.AgregarFinal(new Nodo(3));
    A.AgregarFinal(new Nodo(5));
    B.AgregarFinal(new Nodo(2));
    B.AgregarFinal(new Nodo(9));

    cout << "Lista A original: ";
    A.MostrarLista();
    cout << "Lista B original: ";
    B.MostrarLista();

    A.OrdenarSeleccion();
    B.OrdenarSeleccion();
    cout << "A ordenada: ";
    A.MostrarLista();
    cout << "B ordenada: ";
    B.MostrarLista();

    // c.i: combinación sin importar orden
    Lista C1 = A; // copia superficial: para prueba, usamos nuevos nodos
    Lista C2 = B;
    C1.CombinarNoImportaOrden(C2);
    cout << "\nCombinarNoImportaOrden (A+B): ";
    C1.MostrarLista();
    cout << "Cantidad total: " << C1.getCantidad() << "\n";

    // c.ii: combinación manteniendo orden
    // recrear listas A y B
    Lista D1, D2;
    D1.AgregarFinal(new Nodo(7));
    D1.AgregarFinal(new Nodo(3));
    D1.AgregarFinal(new Nodo(5));
    D2.AgregarFinal(new Nodo(2));
    D2.AgregarFinal(new Nodo(9));

    D1.OrdenarSeleccion();
    D2.OrdenarSeleccion();
    D1.CombinarManteniendoOrden(D2);
    cout << "\nCombinarManteniendoOrden (A+B): ";
    D1.MostrarLista();
    cout << "Cantidad total: " << D1.getCantidad() << "\n";

    return 0;
}
