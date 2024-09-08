#include <iostream>
using namespace std;

template <typename T>
struct Nodo {
    T data;
    Nodo* next;
    Nodo* prev;
    Nodo(T data) : data(data), next(nullptr), prev(nullptr) {}
};

template <typename T>
class ListaCircular {
private:
    Nodo<T>* head;
    int size;

public:
    ListaCircular() : head(nullptr), size(0) {}

    //Retorna el elemento que está al inicio
    T front() {
        if (head == nullptr) {
            throw runtime_error("Lista vacía");
        } else {
            return head->data;
        }
    }

    //Retorna el elemento que está al final
    T back() {
        if (head == nullptr) {
            throw runtime_error("Lista vacía");
        } else {
            return head->prev->data;
        }
    }

    //Agrega un elemento al comienzo
    void push_front(T value) {
        Nodo<T>* temp = new Nodo<T>(value);

        if (head == nullptr) {
            head = temp;
            head->prev = head;
            head->next = head;
        } else {
            temp->next = head;
            temp->prev = head->prev;
            head->prev->next = temp;
            head->prev = temp;
            head = temp;
        }

        size++;
    }

    // Agrega un elemento al final
    void push_back(T value) {
        Nodo<T>* temp = new Nodo<T>(value);
        if (head == nullptr) {
            head = temp;
            head->prev = head;
            head->next = head;
        } else {
            temp->next = head;
            temp->prev = head->prev;
            head->prev->next = temp;
            head->prev = temp;
        }
        size++;
    }

    //Remueve el elemento al comienzo
    T pop_front() {
        if (head == nullptr) {
            throw runtime_error("Lista vacía");
        }
        Nodo<T>* temp = head;
        T delete_val = head->data;
        if (head->next != head) {
            head->next->prev = head->prev;
            head->prev->next = head->next;
            head = head->next;
            delete temp;
        } else {
            delete temp;
            head = nullptr;
        }
        size--;
        return delete_val;
    }

    //Remueve el elemento al final
    T pop_back() {
        if (head == nullptr) {
            throw runtime_error("Lista vacía");
        }
        Nodo<T>* temp = head->prev;
        T delete_val = temp->data;
        if (head->next != head) {
            head->prev = temp->prev;
            temp->prev->next = head;
            delete temp;
        } else {
            delete temp;
            head = nullptr;
        }
        size--;
        return delete_val;
    }

    //Insertar un dato en la posición entregada
    void insert(T val, int lugar) {
        if (lugar < 0 || lugar > size) {
            throw out_of_range("Entrada de posicion invalida");
        }
        if (lugar == 0) {
            push_front(val);
        } else if (lugar == size) {
            push_back(val);
        } else {
            Nodo<T>* n1 = new Nodo<T>(val);
            Nodo<T>* temp = head;
            int actual = 0;
            while (actual < lugar) {
                temp = temp->next;
                actual++;
            }
            n1->next = temp;
            n1->prev = temp->prev;
            temp->prev->next = n1;
            temp->prev = n1;
            size++;
        }
    }

    //Remueve en cualquier posición
    void remove(int lugar) {
        if (lugar < 0 || lugar >= size) {
            throw out_of_range("Entrada invalida.");
        }

        if (lugar == 0) {
            pop_front();
        } else if (lugar == size - 1) {
            pop_back();
        } else {
            Nodo<T>* temp = head;
            int actual = 0;
            while (actual < lugar) {
                temp = temp->next;
                actual++;
            }
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete temp;
            size--;
        }
    }

    //Retorna el elemento en la posición indicada
    T operator[](int lugar) {
        if (lugar < 0 || lugar >= size) {
            throw out_of_range("Entrada invalida");
        }
        Nodo<T>* temp = head;
        for (int i = 0; i < lugar; ++i) {
            temp = temp->next;
        }
        return temp->data;
    }

    //Retorna si la lista está vacía o no
    bool empty() const {
        return head == nullptr;
    }

    //Retorna el tamaño de la lista
    int tam_list() const {
        return size;
    }

    // Elimina todos los elementos de la lista
    void clear() {
        while (head != nullptr) {
            pop_front();
        }
    }

    //Iniverte el orden de los elementos en la lista
    void reverse() {
        if (head == nullptr) {
            cout << "Lista vacía" << endl;
            return;
        }

        Nodo<T>* current = head;
        Nodo<T>* temp = nullptr;
        do {
            // Intercambiar next y prev para cada nodo
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;

            // Mover al siguiente nodo que ahora está en prev
            current = current->prev;
        } while (current != head);

        // Ajustar la nueva cabeza
        head = temp->prev;
    }

    void print() const {
        if (head == nullptr) {
            cout << "Lista vacía" << endl;
            return;
        }
        Nodo<T>* temp = head;
        do {
            cout << temp->data << " ";
            temp = temp->next;
        } while (temp != head);
        cout << endl;
    }
};

int main() {
    ListaCircular<int> lista;

    // Probando push_front y front
    lista.push_front(10);
    lista.print();
    lista.push_front(20);
    lista.print();
    lista.push_front(30);
    lista.print();
    cout << "El primer elemento es: " << lista.front() << endl;

    // Probando push_back y back
    lista.push_back(40);
    lista.print();
    lista.push_back(50);
    lista.print();
    cout << "El último elemento es: " << lista.back() << endl;

    // Probando pop_front
    cout << "Eliminando el primer elemento: " << lista.pop_front() << endl;
    lista.print();
    cout << "El nuevo primer elemento es: " << lista.front() << endl;

    // Probando pop_back
    cout << "Eliminando el último elemento: " << lista.pop_back() << endl;
    lista.print();
    cout << "El nuevo último elemento es: " << lista.back() << endl;

    // Probando insert
    lista.insert(25, 1);
    lista.print();
    cout << "El elemento en la posición 1 es: " << lista[1] << endl;

    // Probando remove
    lista.remove(1);
    lista.print();
    cout << "El nuevo elemento en la posición 1 es: " << lista[1] << endl;

    // Probando empty
    cout << "La lista está vacía: " << (lista.empty() ? "Sí" : "No") << endl;

    // Probando tam_list
    cout << "El tamaño de la lista es: " << lista.tam_list() << endl;

    // Probando clear
    lista.clear();
    lista.print();
    cout << "La lista está vacía después de clear: " << (lista.empty() ? "Sí" : "No") << endl;

    // Probando reverse
    lista.push_front(60);
    lista.print();
    lista.push_front(70);
    lista.print();
    lista.push_front(80);
    lista.print();
    lista.reverse();
    lista.print();
    cout << "El primer elemento después de revertir es: " << lista.front() << endl;
    cout << "El último elemento después de revertir es: " << lista.back() << endl;

    return 0;
}
