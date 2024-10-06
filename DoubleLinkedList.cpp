#include <iostream>
#include <cmath>
using namespace std;

template <typename T>
struct Node {
    T data;      
    Node* next;
    Node* prev;
};

template <typename T>
class DLList {

    private:
    Node<T>* head; // Atributo head
    Node<T>* tail; // Atributo tail

    public:
    
    DLList() : head(NULL), tail(NULL) {} // Inicializo el head y tail como null 

    T front(){ // Retorna el elemento al comienzo
        if(head==NULL && tail==NULL){ // Verificar si la lista esta vacia
            cout<< "La lista esta vacia"<<endl;
            return T();
            }
        else{ // Ir a donde apunta head
            return head->data;
            }
    }

    T back(){ // Retorna el elemento al final
        if(tail==NULL && head==NULL){ // Verificar si la lista esta vacia
            cout<< "La lista esta vacia"<<endl;
            return T();
        }
        else{ // Ir a donde apunta tail
            return tail->data;
        }
    }

    void push_front(T valor){ // Agrega un elemento al comienzo

        Node<T>* nodo = new Node<T>;
        nodo->data=valor;
        nodo->next=head;
        nodo->prev=NULL;
        if(head!=NULL){
            head->prev=nodo; 
        }
        // Si era el primer elemento
        if(head==NULL && tail==NULL){
            tail=nodo;
        }
        head=nodo;
    }

    void push_back(T valor){ // Agrega un elemento al final
        Node<T>* nodo = new Node<T>;
        nodo->data = valor;
        nodo->next=NULL;
        nodo->prev=tail;
        
        if(tail!=NULL){
            tail->next=nodo;
        }
        // Si era el primer elemento
        if(head==NULL && tail==NULL){
            head=nodo;
        }
        tail=nodo;
    } 

    T pop_front() {// Remueve el elemento al comienzo
        if(head==NULL && tail==NULL ){ // Verificar si la lista esta vacia
            cout<< "Lista ya esta vacia"<<endl;
            return T();
        }
        else{
            Node<T>* temp = head;
            T valor = temp->data;
            head = head->next;
            if(head!=NULL){
                head->prev=NULL; // ver si no se traba aqui cuando la lista sea de un solo valor
                
            }else{
                tail=NULL; // Por si acaso, revisar que pasa si no pongo esto
            }
            delete temp;
            return valor;
        }
    }

    T pop_back() {// Remueve el elemento al final
        if(tail==NULL && head==NULL){ // Verificar si la lista esta vacia
            cout<< "Lista ya esta vacia"<<endl;
            return T();
        }
        else{
            Node<T>* temp = tail;
            T valor = temp->data;
            tail = tail->prev;
            
            if(tail!=NULL){
                tail->next=NULL; // ver si no se traba aqui cuando la lista sea de un solo valor
                
            }else{ // La lista esta vacia
                head=NULL; // Por si acaso, revisar que pasa si no pongo esto
            }
            delete temp;
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
        if(head==NULL && tail==NULL){ // Verificar si la lista esta vacia
            return true;
        }else{
            return false;
        }
    }

    int size(){// Retorna el tamaño de la lista
        if(head==NULL && tail==NULL){ // Verificar si la lista esta vacia
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
        tail=NULL; //Verificar si funciona bien sin esto o con esto 
    }
    
    // Para reversa solo swap head y tail

    void reverse(){ // Faltaria probar
        Node<T>*  temp = tail;
        tail=head;
        head=temp;

        while(temp!=NULL){
            Node<T>*  temp2 = temp->next;
            Node<T>*  temp3 = temp->prev;
            temp->prev=temp2;
            temp->next=temp3;
            temp=temp->next;   
        }
    }

    void insert(T valor, int pos){ //Inserta cualquier posicion //Falta condicionar para head y tail y estos extremos

        Node<T>*  nodo = new Node<T>;
        nodo->data=valor;

        Node<T>*  temp = head;
        int i=0;
        if(temp==NULL){
            head=nodo;
            nodo->next=NULL;
            nodo->prev=NULL;
            tail=nodo;
        } else if(pos==0){
            temp->prev=nodo;
            nodo->next=temp;
            head=head->prev;
            nodo->prev=NULL;
        }else{ // Esto es cuando puntero no sea head ni tail
            while (i++ < pos-1){ // Aqui hay pos incremento, despues de evaluar la condicion incrementa
            temp=temp->next;
            }
            if(temp==tail){ //Si llego a tail, es decir que llego a la ultima posicion y quiero ponerme de tail
                temp->next=nodo;
                nodo->prev=temp;
                tail=tail->next;
                nodo->next=NULL;
            } else{
                //Cuando se llegue a la posicion previa
                //Actualizo del puntero 
                nodo->next=temp->next;
                nodo->prev=temp;

                //Actualizo de la red
                temp->next->prev=nodo;
                temp->next=nodo; 

            }
                  
        }
    }

    void remove(int pos){ // Remueve en cualquier posicion
        Node<T>*  temp = head;
        for (int i = 0; i < pos; i++)
        {
            temp=temp->next;
        }

        if(temp!=head){
            temp->prev->next=temp->next;
        }

        if(temp!=tail){
            temp->next->prev=temp->prev;
        }

        if(temp==head){
            head=temp->next;
        }
        if(temp==tail){
            tail=temp->prev;
        }

        delete temp;


    }

    Node<T>* ghead(){
        return head;
    }

    Node<T>* gtail(){
        return tail;
    }

    void mtail(Node<T>* node){
        tail=node;
    }

    void mhead(Node<T>* node){
        head=node;
    }

};

int main(){
    DLList<int> LList; //que funcione con int double float y que mas
    cout<<"Elemento del comienzo: "<<LList.front()<<endl;
    cout<<"Tamano de la lista: "<<LList.size()<<endl;
    cout<<"Lista vacia?: "<<LList.empty()<< "\n"<<endl;
    LList.insert(2,0);
    LList.insert(3,0);
    LList.push_front(7);
    LList.push_back(5);
    cout<<"Tamano de la lista tras hacer insert de un elemento: "<<LList.size()<<endl;
    cout<<"Lista vacia?: "<<LList.empty()<< "\n"<<endl;
    LList.push_back(3);
    LList.insert(6,3);
    LList.push_back(1);
    LList.insert(8,6);
    LList.insert(9,8);
    
    cout<<"Lista despues hacer push: "<<endl;
    cout<<"Elemento 1: "<<LList[0]<<endl;
    cout<<"Elemento 2: "<<LList[1]<<endl;
    cout<<"Elemento 3: "<<LList[2]<<endl;
    cout<<"Elemento 4: "<<LList[3]<<endl;
    cout<<"Elemento 5: "<<LList[4]<<endl;
    cout<<"Elemento 6: "<<LList[5]<<endl;
    cout<<"Elemento 7: "<<LList[6]<<endl;
    cout<<"Elemento 8: "<<LList[7]<<endl;
    cout<<"Elemento 9: "<<LList[8]<< "\n"<<endl;

    cout<<"Elemento del comienzo: "<<LList.front()<<endl;
    cout<<"Elemento del final: "<<LList.back()<< "\n"<<endl;
    cout<<"Tamano de la lista: "<<LList.size()<<endl;

    LList.pop_front();
    LList.pop_back();

    cout<<"Lista despues hacer pop front y back: "<<endl;
    cout<<"Elemento 1: "<<LList[0]<<endl;
    cout<<"Elemento 2: "<<LList[1]<<endl;
    cout<<"Elemento 3: "<<LList[2]<<endl;
    cout<<"Elemento 4: "<<LList[3]<<endl;
    cout<<"Elemento 5: "<<LList[4]<<endl;
    cout<<"Elemento 6: "<<LList[5]<<endl;
    cout<<"Elemento 7: "<<LList[6]<<"\n"<<endl;

    cout<<"Elemento 1: "<<LList.front()<<endl;
    cout<<"Elemento 7: "<<LList.back()<< "\n"<<endl;
    cout<<"Tamano de la lista: "<<LList.size()<<endl;
    cout<<"Lista vacia?: "<<LList.empty()<< "\n"<<endl;

    cout<<"Anado elementos: "<<endl;
    LList.push_back(2);
    LList.push_back(1);
    LList.push_front(9);

    cout<<"Elemento 1: "<<LList[0]<<endl;
    cout<<"Elemento 2: "<<LList[1]<<endl;
    cout<<"Elemento 3: "<<LList[2]<<endl;
    cout<<"Elemento 4: "<<LList[3]<<endl;
    cout<<"Elemento 5: "<<LList[4]<<endl;
    cout<<"Elemento 6: "<<LList[5]<<endl;
    cout<<"Elemento 7: "<<LList[6]<<endl;
    cout<<"Elemento 8: "<<LList[7]<<endl;
    cout<<"Elemento 9: "<<LList[8]<<endl;
    cout<<"Elemento 10: "<<LList[9]<< "\n"<<endl;

    cout<<"Elemento 1: "<<LList.front()<<endl;
    cout<<"Elemento 10: "<<LList.back()<< "\n"<<endl;
    cout<<"Tamano de la lista: "<<LList.size()<<endl;
    cout<<"Lista vacia?: "<<LList.empty()<< "\n"<<endl;

   
    LList.reverse();
    cout<<"Elemento 1: "<<LList[0]<<endl;
    cout<<"Elemento 2: "<<LList[1]<<endl;
    cout<<"Elemento 3: "<<LList[2]<<endl;
    cout<<"Elemento 4: "<<LList[3]<<endl;
    cout<<"Elemento 5: "<<LList[4]<<endl;
    cout<<"Elemento 6: "<<LList[5]<<endl;
    cout<<"Elemento 7: "<<LList[6]<<endl;
    cout<<"Elemento 8: "<<LList[7]<<endl;
    cout<<"Elemento 9: "<<LList[8]<<endl;
    cout<<"Elemento 10: "<<LList[9]<< "\n"<<endl;

    cout<<"Elemento del comienzo: "<<LList.front()<<endl;
    cout<<"Elemento del final: "<<LList.back()<< "\n"<<endl;

    cout<<"Tamano de la lista: "<<LList.size()<<endl;
    cout<<"Lista vacia?: "<<LList.empty()<< "\n"<<endl;

    
    LList.insert(7,0);
    cout<<"Lista en con valor 7 en posicion 0: "<<endl;
    cout<<"Elemento 1: "<<LList[0]<<endl;
    cout<<"Elemento 2: "<<LList[1]<<endl;
    cout<<"Elemento 3: "<<LList[2]<<endl;
    cout<<"Elemento 4: "<<LList[3]<<endl;
    cout<<"Elemento 5: "<<LList[4]<<endl;
    cout<<"Elemento 6: "<<LList[5]<<endl;
    cout<<"Elemento 7: "<<LList[6]<<endl;
    cout<<"Elemento 8: "<<LList[7]<<endl;
    cout<<"Elemento 9: "<<LList[8]<<endl;
    cout<<"Elemento 10: "<<LList[9]<<endl;
    cout<<"Elemento 11: "<<LList[10]<< "\n"<<endl;

    cout<<"Elemento del comienzo: "<<LList.front()<<endl;
    cout<<"Elemento del final: "<<LList.back()<< "\n"<<endl;

    LList.remove(2);
    LList.remove(0);
    LList.remove(8);
    cout<<"Eliminar: "<<endl;

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

    LList.clear();
    cout<<"Lista vacia?: "<<LList.empty()<< "\n"<<endl;

    LList.insert(2,0);
    LList.insert(3,0);
    LList.push_front(7);
    LList.push_back(5);
    cout<<"Tamano de la lista tras hacer insert de un elemento: "<<LList.size()<<endl;
    cout<<"Lista vacia?: "<<LList.empty()<< "\n"<<endl;
    LList.push_back(3);
    LList.insert(6,3);
    LList.push_back(1);
    LList.insert(8,6);
    LList.insert(9,8);
    
    cout<<"Lista despues hacer push: "<<endl;
    cout<<"Elemento 1: "<<LList[0]<<endl;
    cout<<"Elemento 2: "<<LList[1]<<endl;
    cout<<"Elemento 3: "<<LList[2]<<endl;
    cout<<"Elemento 4: "<<LList[3]<<endl;
    cout<<"Elemento 5: "<<LList[4]<<endl;
    cout<<"Elemento 6: "<<LList[5]<<endl;
    cout<<"Elemento 7: "<<LList[6]<<endl;
    cout<<"Elemento 8: "<<LList[7]<<endl;
    cout<<"Elemento 9: "<<LList[8]<< "\n"<<endl;


    cout<<"Elemento del comienzo: "<<LList.front()<<endl;
    cout<<"Elemento del final: "<<LList.back()<< "\n"<<endl;

    cout<<"Tamano de la lista: "<<LList.size()<<endl;
    cout<<"Lista vacia?: "<<LList.empty()<< "\n"<<endl;

   
    return 0;


}

