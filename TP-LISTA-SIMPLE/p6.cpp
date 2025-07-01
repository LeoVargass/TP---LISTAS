#include <iostream>
#include <cctype>    // para isupper, islower
#include <cmath>     // para sqrt
using namespace std;

// === Clase Nodo genérico ===
template<typename T>
class Nodo {
private:
    T dato;
    Nodo<T>* sig;
public:
    Nodo(const T& dato) {
        this->dato = dato;
        this->sig = nullptr;
    }
    T getDato() const { return dato; }
    Nodo<T>* getSiguiente() const { return sig; }
    void setSiguiente(Nodo<T>* p) { sig = p; }
};

// === Clase Lista genérica ===
template<typename T>
class Lista {
private:
    Nodo<T>* inicio;
    int cant;
public:
    Lista() {
        inicio = nullptr;
        cant = 0;
    }

    bool estaVacia() const {
        return inicio == nullptr;
    }

    void AgregarFinal(Nodo<T>* nuevo) {
        if (estaVacia()) {
            inicio = nuevo;
        } else {
            Nodo<T>* i = inicio;
            while (i->getSiguiente() != nullptr)
                i = i->getSiguiente();
            i->setSiguiente(nuevo);
        }
        cant++;
    }

    // Recorre y aplica f(nodo)
    template<typename F>
    void forEach(F f) const {
        for (Nodo<T>* i = inicio; i != nullptr; i = i->getSiguiente())
            f(i);
    }

    void MostrarLista() const {
        if (estaVacia()) {
            cout << "Lista vacía\n";
            return;
        }
        for (Nodo<T>* i = inicio; i != nullptr; i = i->getSiguiente()) {
            cout << i->getDato() << " ";
        }
        cout << "\n";
    }

    int getCantidad() const { return cant; }
};

// === Función auxiliar: verifica si un entero es primo ===
bool esPrimo(int n) {
    if (n < 2) return false;
    if (n % 2 == 0 && n != 2) return false;
    int limite = static_cast<int>(sqrt(n));
    for (int i = 3; i <= limite; i += 2)
        if (n % i == 0)
            return false;
    return true;
}

// === a) Cuenta primos en Lista<int> y muestra resultado ===
int contarPrimos(const Lista<int>& L) {
    int contador = 0;
    L.forEach([&](Nodo<int>* nodo){
        if (esPrimo(nodo->getDato()))
            contador++;
    });
    return contador;
}

// === b) Cuenta mayúsculas y minúsculas en Lista<char> ===
pair<int,int> contarMayusMinus(const Lista<char>& L) {
    int mayus = 0, minus = 0;
    L.forEach([&](Nodo<char>* nodo){
        char c = nodo->getDato();
        if (isupper(static_cast<unsigned char>(c)))
            mayus++;
        else if (islower(static_cast<unsigned char>(c)))
            minus++;
    });
    return {mayus, minus};
}

// === MAIN de prueba ===
int main() {
    // --- a) lista de enteros y conteo de primos ---
    Lista<int> Lint;
    int n;
    cout << "¿Cuántos números enteros desea cargar? ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cout << "Ingrese valor entero #" << i+1 << ": ";
        cin >> x;
        Lint.AgregarFinal(new Nodo<int>(x));
    }
    cout << "\nContenido de la lista de enteros:\n";
    Lint.MostrarLista();
    int primos = contarPrimos(Lint);
    cout << "Cantidad de números primos: " << primos << "\n\n";

    // --- b) lista de caracteres y conteo de mayúsculas/minúsculas ---
    Lista<char> Lchar;
    cout << "¿Cuántos caracteres desea cargar? ";
    cin >> n;
    cin.ignore(); // descartar '\n'
    for (int i = 0; i < n; i++) {
        char c;
        cout << "Ingrese caracter #" << i+1 << ": ";
        cin.get(c);
        cin.ignore(); // descartar '\n'
        Lchar.AgregarFinal(new Nodo<char>(c));
    }
    cout << "\nContenido de la lista de caracteres:\n";
    Lchar.MostrarLista();
    auto [mayus, minus] = contarMayusMinus(Lchar);
    cout << "Cantidad de mayúsculas: " << mayus << "\n";
    cout << "Cantidad de minúsculas: " << minus << "\n";

    return 0;
}
