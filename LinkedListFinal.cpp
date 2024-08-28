//Referencia: https://www.geeksforgeeks.org/cpp-linked-list/ y chgpt
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


};


int main(){

    LinkedList<int> LList; //que funcione con int double float y que mas
    cout<<"Elemento del comienzo: "<<LList.front()<<endl;
    cout<<"Lista vacia?: "<<LList.empty()<< "\n"<<endl;
    LList.push_front(5);
    LList.push_back(2);
    LList.push_back(1);
    LList.push_back(7);
    LList.push_back(9);
    LList.push_back(8);
    LList.push_front(1);
    LList.push_front(3);

    cout<<"Lista despues hacer push: "<<endl;
    cout<<"Elemento 1: "<<LList[0]<<endl;
    cout<<"Elemento 2: "<<LList[1]<<endl;
    cout<<"Elemento 3: "<<LList[2]<<endl;
    cout<<"Elemento 4: "<<LList[3]<<endl;
    cout<<"Elemento 5: "<<LList[4]<<endl;
    cout<<"Elemento 6: "<<LList[5]<<endl;
    cout<<"Elemento 7: "<<LList[6]<<endl;
    cout<<"Elemento 8: "<<LList[7]<< "\n"<<endl;

    cout<<"Elemento del comienzo: "<<LList.front()<<endl;
    cout<<"Elemento del final: "<<LList.back()<< "\n"<<endl;

    LList.pop_front();
    LList.pop_back();

    cout<<"Lista despues hacer pop front y back: "<<endl;
    cout<<"Elemento 1: "<<LList[0]<<endl;
    cout<<"Elemento 2: "<<LList[1]<<endl;
    cout<<"Elemento 3: "<<LList[2]<<endl;
    cout<<"Elemento 4: "<<LList[3]<<endl;
    cout<<"Elemento 5: "<<LList[4]<<endl;
    cout<<"Elemento 6: "<<LList[5]<< "\n"<<endl;

    cout<<"Elemento del comienzo: "<<LList.front()<<endl;
    cout<<"Elemento del final: "<<LList.back()<< "\n"<<endl;

    cout<<"Tamano de la lista: "<<LList.size()<<endl;
    cout<<"Lista vacia?: "<<LList.empty()<< "\n"<<endl;
    
    LList.reverse();
    cout<<"Lista tal cual: "<<endl;
    cout<<"Elemento 1: "<<LList[0]<<endl;
    cout<<"Elemento 2: "<<LList[1]<<endl;
    cout<<"Elemento 3: "<<LList[2]<<endl;
    cout<<"Elemento 4: "<<LList[3]<<endl;
    cout<<"Elemento 5: "<<LList[4]<<endl;
    cout<<"Elemento 6: "<<LList[5]<< "\n"<<endl;

    LList.sort();
    cout<<"Ordenado: "<<endl;
    cout<<"Elemento 1: "<<LList[0]<<endl;
    cout<<"Elemento 2: "<<LList[1]<<endl;
    cout<<"Elemento 3: "<<LList[2]<<endl;
    cout<<"Elemento 4: "<<LList[3]<<endl;
    cout<<"Elemento 5: "<<LList[4]<<endl;
    cout<<"Elemento 6: "<<LList[5]<< "\n"<<endl;

    LList.reverse();
    cout<<"Lista tal cual: "<<endl;
    cout<<"Elemento 1: "<<LList[0]<<endl;
    cout<<"Elemento 2: "<<LList[1]<<endl;
    cout<<"Elemento 3: "<<LList[2]<<endl;
    cout<<"Elemento 4: "<<LList[3]<<endl;
    cout<<"Elemento 5: "<<LList[4]<<endl;
    cout<<"Elemento 6: "<<LList[5]<< "\n"<<endl;

    LList.clear();
    cout<<"Lista vacia?: "<<LList.empty()<< "\n"<<endl;


    
    return 0;
}
