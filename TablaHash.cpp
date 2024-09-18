#include <iostream>
#include <cmath>
#include <random>
#include <set>
#include <vector>
#include <string>
#include <type_traits>
using namespace std;

#define MAX_SIZE 50

template <typename T, typename V>
struct Node {
    T key;
    V value;      
    Node* next;
};

template <typename T,typename V>
class LinkedList {

    //private:
    Node<T,V>* head; // Atributo head

    public:
    
    LinkedList() : head(NULL) {} // Inicializo el head como null 

    int push_front(T key, V valor){ // Agrega un elemento al comienzo

        Node<T,V>* temp = head;
        bool found=false;
        while(temp!=NULL && !found)
        {
            if(temp->key==key){
                temp->value=valor;
                found=true;
            }else{
                temp=temp->next;
            }
        }
        
        if(found==true){
            return 0;
        }else{
            Node<T,V>* nodo = new Node<T,V>;
            nodo->key=key;
            nodo->value=valor;
            nodo->next=head;
            head=nodo;
            return 1;
        }
  
    }

    T pop_front() {// Remueve el elemento al comienzo
        if(head==NULL){ // Verificar si la lista esta vacia
            return T();
        }
        else{
            Node<T,V>* temp = head;
            V valor = temp->value;
            T key = temp->key;
            head = head->next;
            delete temp;
            return key;
        }
    }

    V findKey(T key){
        Node<T,V>*  temp = head;
        bool flag = false;
        int i = 0;
        while(!flag && temp!=NULL){
            if(temp->key==key){
                flag=true;
            }else{
                temp = temp->next;
                i++;
            }
        }
        
        if(flag==true){
            return temp->value;
        }
        else{
            return V();
        }

    }

    void deleteKey(T key){ //
        Node<T,V>*  temp = head;
        Node<T,V>* prev=NULL;
        bool flag=false;

        while(temp!=NULL && flag==false){
            if(temp->key==key){
                if(temp==head){
                    head = head->next;
                    delete temp;
                }else if(temp->next==NULL){
                    prev->next=NULL;
                    delete temp;
                }else{
                    prev->next=temp->next;
                    delete temp;
                }
                flag=true;
            }else{
                prev=temp;
                temp=temp->next;
            }
        }
        

    }

    T operator[ ](int valor){// Retorna el elemento en la posición indicada
        Node<T,V>*  temp = head;
        for(int i=0; i<=valor-1; i++){ //dependiendo si quiero iniciar con 0 o con 1 y puede ser acotado mejor con el size
            temp = temp->next;
        } 
        return temp->key;
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
            Node<T,V>* temp = head;
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
            Node<T,V>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    Node<T,V>* gethead(){
        return head;
    }



};


template <typename T, typename V>
class TablaHash{
    int m=MAX_SIZE;
    LinkedList<T,V> LlistArray[MAX_SIZE];
    int nelements;
    int P=97;
    int maxCol=3;
    float fillfactor;
    int a;
    int b;
    

    public:
    // Constructor
    TablaHash() : nelements(0) {
        a  = getRandomNumber(1,P-1);
        b = getRandomNumber(0,P-1);

    }

    int getRandomNumber(int lower, int P) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(lower, P - 1);
        return distrib(gen);
    }

    int newkey(T key){
        int nkey;
        if constexpr (std::is_same_v<T, std::string>) {
            
            // Tenemos 
            nkey = 0;
            int size=0;
            for (char c : key) {
                size++;
            }

            for (char c:key)
            {
                nkey+=(static_cast<int>(c))*static_cast<int>(pow(2,size-1));
                size--;
            }
            return nkey;

        } else if constexpr (std::is_same_v<T, char>) {

            nkey=static_cast<int>(key);
            return nkey;

        } else if constexpr (std::is_same_v<T, int>) {
            nkey=key;
            return nkey;

        }  else {
        cout << "This type of variable is not considered" << endl;
        return -1;
        }

    }

    int hashingfunction(T key){
        int nkey=newkey(key);
        int index;
        index=(( a*nkey+b ) % P ) % m;
        return index;
    }

    void insert(T key, V value){ //ya actualiza
        int index;
        index=hashingfunction(key);
        if(LlistArray[index].size()>=maxCol){
            cout<<"Index lleno, excediste las colisiones permitidas"<<endl;
        }else{
            int i=LlistArray[index].push_front(key,value); //que pasa en actualizacion y como chequeo si llego al maximo de profundidad?
            nelements+=i;// Si encontro el key i es 0, si no lo encontro i es 1
            fillfactor=nelements/(maxCol*m);
            if(fillfactor<0.5){
            //rehash 
            }

        }
        
    }

    V search(T key){
        int index;
        V value;
        index=hashingfunction(key);
        value=LlistArray[index].findKey(key);
        return value;
    }

    bool empty(){
        if(nelements==0){
            return true;
        }else{
            return false;
        }
    }

    void Delete(T key){
        // Tengo que verificar si esta en la lista? porque creo que no seria necesario
        int index;
        index=hashingfunction(key);
        LlistArray[index].deleteKey(key);

    }

    void showLists(int key){
        int index;
        index=hashingfunction(key);
        Node<T,V>* head=LlistArray[index].gethead();

        Node<T,V>* temp=head;
        while(temp!=NULL){
            cout<<"\n"<<endl;
            cout<<"Key: "<<head->key<<endl;
            cout<<"Value: "<<head->value<<endl;
            temp=temp->next;
        }
        
    }
    
};



int main(){

    TablaHash<int,string> Hash;

    Hash.insert(2,"abc");


    
    
}
