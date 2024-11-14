//Referencia: https://www.geeksforgeeks.org/cpp-linked-list/, chagpt, https://www.geeksforgeeks.org/introduction-to-graphs-data-structure-and-algorithm-tutorials/, https://www.geeksforgeeks.org/introduction-to-dijkstras-shortest-path-algorithm/
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;
#define INF 0x3f3f3f3f



template <typename T>
class MinHeap {
    vector<T> Array;
    int nelements;

    public:
    
    MinHeap() : nelements(0) {} // Inicializo el root como null 

    void MinHeapify (int index){ // Usando el algoritmo de clase y ayuda de ChatGPT

        int e = 2 * index+1;
        int d = 2 * index+2;
        int menor=index;

        if(e<nelements && Array[e]<Array[index]){
            menor=e;
        }
        if(d<nelements && Array[d]<Array[menor]){
            menor=d;
        }

        if(menor!=index){
            swap(Array[index],Array[menor]);
            MinHeapify(menor);
        }
    }

    
    vector<T> BuildMinHeap(vector<T> v){ // Usando el algoritmo de clase y ayuda de ChatGPT
        vector<T> prev=Array;
        int prevne= nelements;
        Array=v;
        nelements=v.size();
        for(int i= v.size()/2 - 1; i>=0;i--){
            MinHeapify(i);
        }
        vector<T> result=Array;
        Array=prev;
        nelements=prevne;
        return result;
    }

    void insert(T value){ //  Obtenido de iapositivas y https://www.geeksforgeeks.org/introduction-to-heap/
        Array.push_back(value);
        nelements=Array.size(); // Puede optimizarse sumando 1
        int index=nelements-1;
        heapifyup(index);
    }

    void heapifyup(int index){ // Obtenido de https://www.geeksforgeeks.org/introduction-to-heap/
        while(index>0 && Array[(index-1)/2]>Array[index]){
            swap(Array[index],Array[(index-1)/2]);
            index=(index-1)/2;
        }
    }

    T pop(){
        swap(Array[0],Array[nelements-1]);
        T value = Array[nelements-1];
        Array.pop_back();
        nelements=Array.size();
        MinHeapify(0);
        return value;
    }

    vector<T> gArray(){
        return Array;
    }

    void mArray(vector<T> Arr){
        Array=Arr;
    }

    bool isempty(){
        if(nelements==0){
            return true;
        }
        return false;
    }

};

template <typename T>
struct Node {
    T data; 
    T w;     
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

    void push_front(T valor, T w){ // Agrega un elemento al comienzo
        Node<T>* nodo = new Node<T>;
        nodo->data=valor;
        nodo->w=w;
        nodo->next=head;
        head=nodo;
    }

    void push_back(T valor, T w){ // Agrega un elemento al final
        Node<T>* nodo = new Node<T>;
        nodo->data = valor;
        nodo->w=w;
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

    pair<T,T> operator[ ](int valor){// Retorna el elemento en la posición indicada
        Node<T>*  temp = head;
        for(int i=0; i<=valor-1; i++){ //dependiendo si quiero iniciar con 0 o con 1 y puede ser acotado mejor con el size
            temp = temp->next;
        } 
        return {temp->data,temp->w};
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
    int size;
    LinkedList<T>* nodo;
    vector<int> d;
    vector<int> padre;

    public:
    Graph(int t): size(t),nodo(new LinkedList<T>[t]),padre(t,-1),d(t,-1){}

    // Para nodo sin direccion, si es con direccion elimina nodo[b].push_back(a);
    void aristas(T a, T b, T w){
        nodo[a].push_back(b,w);
        nodo[b].push_back(a,w);
    }

    void printLA(){
        for (int i = 0; i < size; i++)
        {
            cout<<i<<": ";
            nodo[i].printear();
            cout<<endl;
        }  
    }

    void init_single_source(int s){
        for (int i = 0; i < size; i++)
        {
            d[i]=INF;
            padre[i]=-1; //nil
        }  
        d[s]=0;

    }

    void relax(int u, int v, int w){ // w es el peso de u a w
        if(d[v]>d[u]+w){
            d[v]=d[u]+w;
            padre[v]=u;
        }
    }


    pair<vector<int>,vector<int>> dijkstra(int s){

        init_single_source(s);

        vector<int> S;
        MinHeap<int> Q;

        for(int i=0; i<size; i++){ //Insertar min heap valores de todos los grafos
            Q.insert(i);
        }
       
        while(Q.isempty()!=true){
            int u = Q.pop();
            S.push_back(u);

            for(int i=0; i<nodo[u].size(); i++){
                pair<int,int> lau= nodo[u][i];
                relax(u,lau.first,lau.second);
            }
        }
        return{d,padre};
    }


    vector<int> getPadre(){
        return padre;
    }

    vector<int> getD(){
        return d;
    }


};

int main(){

    int size = 4;
    Graph<char> grafo(size);

    grafo.aristas(0,1,1);
    grafo.aristas(0,3,3);
    grafo.aristas(1,2,2);
    

    pair<vector<int>,vector<int>> valores=grafo.dijkstra(0);
    vector<int> d = valores.first;

    for(int i=0; i<size; i++){
        cout<<d[i]<<endl;
    }


}




