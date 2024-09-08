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
class ListaCircular{
private:
    Nodo<T>* head;
    int size;

public:
    ListaCircular() : head(nullptr), size(0) {};

    T front() {
        if(head==nullptr){
            cout<<"Lista vacía"<<endl;
        } else {
            return head->data;
        }
    }

    T back() {
        if(head==nullptr){
            cout<<"Lista vacía"<<endl;
        } else {
            return head->prev->data;
        }
    }

    void push_front(T value) {
        Nodo<T>* temp = new Nodo<T>(value);

        if(head==nullptr){
            head = temp;
            head->prev=head;
            head->next=head;
        } else {
            temp->next=head;
            head->prev=temp;
            temp->prev=head->prev;
            head->prev->next=temp;
            head=temp;
        }
        
        size=size+1;
    }

    void push_back(T value) {
        Nodo<T>* temp = new Nodo<T>(value);
        if (head==nullptr) {
            head = temp;
            head->prev = head;
            head->next = head;
        } else {
            temp->next=head;
            head->prev=temp;
            temp->prev=head->prev;
            head->prev->next=temp;
        }
        size++;
    }

    T pop_front() {
        Nodo<T>* temp = head;
        T delete_val = head->data;
        if(head==nullptr){
            cout<<"Lista vacía"<<endl;
        } else if(head->next!=head){
            head->next->prev=head->prev;
            head->prev->next=head->next;
            head=head->next;
            delete temp;
        } else {
            delete temp;
            head= nullptr;
        }
        size=size-1;
        return delete_val;
    }

    T pop_back() {
        Nodo<T>* temp = head->prev;
        T delete_val = head->prev->data;
        if(head==nullptr){
            cout<<"Lista vacía"<<endl;
        } else if(head->next!=head){
            head->prev=temp->prev;
            temp->prev->next=head;
            delete temp;
        } else {
            delete temp;
            head= nullptr;
        }
        size=size-1;
        return delete_val;
    }

    void insert(T val, int lugar) {
            if (lugar < 0 || lugar > size){
                cout<<"Entrada de posicion invalida"<<endl;
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
                    actual=actual+1;
                }
                n1->next = temp;
                n1->prev = temp->prev;
                temp->prev->next = n1;
                temp->prev = n1;
                size=size+1;
            }
        }

    void remove(int lugar) {
        if (lugar < 0 || lugar >= size) {
            cout << "Entrada invalida." << endl;
            return;
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
                actual=actual+1;
            }
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete temp;
            size=size-1;
        }
    }

    T operator[](int lugar) {
        if (lugar < 0 || lugar >= size){
            cout<<"Entrada invalida"<<endl;
        }
        Nodo<T>* temp = head;
        for (int i = 0; i < lugar; ++i) {
            temp = temp->next;
        }
        return temp->data;
    }

    bool empty() {
        if(head==nullptr){
            return true;
        } else {
            return false;
        }
    }

    int tam_list() {
        return size;
    }

    void clear() {
        while (head!=nullptr) {
            pop_front();
        }
    }

    void reverse() {
        if (head==nullptr){
            cout<<"Lista vacía"<<endl;
        }

        Nodo<T>* temp = nullptr;
        Nodo<T>* last = nullptr;
        Nodo<T>* actual = head;

        while (actual->next != head) {
            actual = actual->next;
        }
        last = actual;

        actual = head;
        while (true) {
            temp = actual->prev;
            actual->prev = actual->next;
            actual->next = temp;
            actual = actual->prev;

            if (actual == head) break;
        }
        head = last;
    }

};

