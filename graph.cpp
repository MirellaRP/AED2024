//Referencia: https://www.geeksforgeeks.org/cpp-linked-list/, chgpt, https://www.geeksforgeeks.org/introduction-to-graphs-data-structure-and-algorithm-tutorials/
#include <iostream>
#include <cmath>
using namespace std;

template <typename T>
struct Node {
    T data;      
    Node* next;
};

template <typename T>
class LinkedList {

    //private:
    Node<T>* head; // Atributo head

    public:
    
    LinkedList() : head(NULL) {} // Inicializo el head como null 

    
    T front(){ // Retorna el elemento al comienzo
        if(head==NULL){ // Verificar si la lista esta vacia
            cout<< "La lista esta vacia"<<endl;
            return T();
            }
        else{ // Ir a donde apunta head
            return head->data;
            }
    }

    T back(){ // Retorna el elemento al final
        if(head==NULL){ // Verificar si la lista esta vacia
            cout<< "Lista vacia"<<endl;
            return T();
        }
        else{
            Node<T>* temp = head;
            while (temp->next !=NULL)
                temp = temp->next;
            return temp->data;
        }
    } 

    void push_front(T valor){ // Agrega un elemento al comienzo
        Node<T>* nodo = new Node<T>;
        nodo->data=valor;
        nodo->next=head;
        head=nodo;
    }

    void push_back(T valor){ // Agrega un elemento al final
        Node<T>* nodo = new Node<T>;
        nodo->data = valor;
        nodo->next=NULL;
        Node<T>* temp = head;
        if(head==NULL){
            head=nodo;
        }
        else{
            while (temp->next!=NULL){
                temp = temp->next;
            }
            temp->next = nodo;
            nodo->next = NULL;
        }
        
    } 

    T pop_front() {// Remueve el elemento al comienzo
        if(head==NULL){ // Verificar si la lista esta vacia
            cout<< "Lista vacia"<<endl;
            return T();
        }
        else{
            Node<T>* temp = head;
            T valor = temp->data;
            head = head->next;
            delete temp;
            return valor;
        }
    }

    T pop_back() {// Remueve el elemento al comienzo
        if(head==NULL){ // Verificar si la lista esta vacia
            cout<< "Lista vacia"<<endl;
            return T();
        }else if (head->next==NULL)
        {
            T valor = head->data;
            delete head;
            head = NULL;
            return valor;
        }
        else{
            Node<T>* temp = head;
            while (temp->next->next !=NULL)
                temp = temp->next;
            T valor = temp->next->data;
            delete temp->next;
            temp->next=NULL;
            return valor;
        }
    }

    T operator[ ](int valor){// Retorna el elemento en la posición indicada
        Node<T>*  temp = head;
        for(int i=0; i<=valor-1; i++){ //dependiendo si quiero iniciar con 0 o con 1 y puede ser acotado mejor con el size
            temp = temp->next;
        } 
        return temp->data;
    }

    bool empty(){// Retorna si la lista está vacía o no
        if(head==NULL){ // Verificar si la lista esta vacia
            return true;
        }else{
            return false;
        }
    }

    int size(){// Retorna el tamaño de la lista
        if(head==NULL){ // Verificar si la lista esta vacia
            return 0;
        } else{
            int s = 1;
            Node<T>* temp = head;
            while (temp->next !=NULL){
                temp = temp->next;
                s++;
            }
            return s;
        }
    } 

    void clear(){ // Elimina todos los elementos de la lista
        // Si head es NULL ya la lista esta vacia asi que no se hace nada
        while(head != NULL){
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void reverse(){ // Revierte la lista
        // Luego poner lo de null de head
        if(head != NULL){
            Node<T>* temporal = NULL;
            Node<T>* actual = head;
            Node<T>* previo = NULL;

            while (actual->next !=NULL){ // tambien hasta que vuelvan a inicio
                temporal=actual->next; // B
                actual->next=previo;  //NULL
                previo=actual; // A
                actual=temporal;  // B
            }
            actual->next=previo;
            head=actual;
        }
    } 

    void sort(){ // Ordenar la lista - Bubble sort

        if(head != NULL){
            bool swap = true; // Uso una bandera para verificar si la lista esta ordenada
            // Inicializo todos en Null
            Node<T>* actual=NULL;
            Node<T>* ultimo=NULL;
            Node<T>* siguiente=NULL;

            while (swap==true){
                swap=false;
                actual=head;
                siguiente=actual->next;

                while (siguiente!=ultimo){ // ultimo de esta iteracion

                    if(siguiente->data < actual->data){
                        T temp=actual->data;
                        actual->data=siguiente->data;
                        siguiente->data=temp;
                        swap=true;

                    }
                    actual=siguiente;
                    siguiente=actual->next;
                }
                ultimo=actual;
            }
        }
    }

    void printear(){
        Node<T>* actual=head;
        while(actual != NULL){
            cout<< actual->data<< " ";
            actual=actual->next;
        }
    }    


};


template <typename T>
class Graph{
    const int size = 20;
    LinkedList<T> grafo[20];

    public:
    Graph(){}

    // Para grafo sin direccion, si es con direccion elimina grafo[b].push_back(a);
    void aristas(T a, T b){
        grafo[a].push_back(b);
        grafo[b].push_back(a);

    }

    void print(){
        for (int i = 0; i < size; i++)
        {
            cout<<i<<": ";
            grafo[i].printear();
            cout<<endl;
        }  
    }



};

int main(){

    Graph<int> grafo;
    grafo.aristas(0,1);
    grafo.aristas(2,3);
    grafo.aristas(5,6);
    grafo.aristas(5,7);
    grafo.aristas(8,5);
    grafo.print();

}




