#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

// Basado en https://www.geeksforgeeks.org/quad-tree/

class Punto{
    public:
    int x;
    int y;

    
    Punto(int xvalue, int yvalue):x(xvalue),y(yvalue){}
};

template<class T>
class NodoQuad{
    public:
    Punto punto;
    T dato;
    NodoQuad *NW, *NE, *SW, *SE;
    NodoQuad(int x, int y, T data): punto(Punto(x,y)),dato(data), NW(NULL),NE(NULL),SE(NULL),SW(NULL){}
};

template<class T>
class QuadTree{
    private:
    NodoQuad<T>* root;
    int limitX, limitY;

    public:
    QuadTree(int x, int y): limitX(x),limitY(y){}

    int compare(Punto R, Punto K){
        // Si retorna 1 es NW, si retorna 2 es NE, si es 3 SW, si es 4 es SE.

        if(     R.x>K.x    && R.y>K.y){
            return 1;
        }else if(R.x<K.x    && R.y>K.y){
            return 2;
        }else if(R.x>K.x   && R.y<K.y){
            return 3; 
        }else if(R.x<K.x    && R.y<K.y){
            return 4;
        }

        //si es 0 esta fuera del rango
        return 0;
        
    }


    void insertInTree(NodoQuad<T>* R, Punto K, T tag){

        int comp = compare(R->punto,K); // Si retorna 1 es NW, si retorna 2 es NE, si es 3 SW, si es 4 es SE, si es 0 esta fuera del rango.


        if(comp==1){
            // Si es NW entramos al cuadrante actual y verificamos si el cuadrante NW apunta a algo.
            //Si apunta a algo vamos a verificar ese cuadrante recursivamente
            if(R->NW!=NULL){
                insertInTree(R->NW,K,tag);
            }else{
                // Si no apunta a nada vamos a crear un nodo y realizamos la insercion
                NodoQuad<T>* nodo = new NodoQuad<T>(K.x,K.y,tag);
                R->NW=nodo;
            }
        }
        else if(comp==2){
            // Si es NE entramos al cuadrante actual y verificamos si el cuadrante NE apunta a algo.
            //Si apunta a algo vamos a verificar ese cuadrante recursivamente
            if(R->NE!=NULL){
                insertInTree(R->NE,K,tag);
            }else{
                // Si no apunta a nada vamos a crear un nodo y realizamos la insercion
                NodoQuad<T>* nodo = new NodoQuad<T>(K.x,K.y,tag);
                R->NE=nodo;
            }
        }
        else if(comp==3){
            // Si es SW entramos al cuadrante actual y verificamos si el cuadrante SW apunta a algo.
            //Si apunta a algo vamos a verificar ese cuadrante recursivamente
            if(R->SW!=NULL){
                insertInTree(R->SW,K,tag);
            }else{
                // Si no apunta a nada vamos a crear un nodo y realizamos la insercion
                NodoQuad<T>* nodo = new NodoQuad<T>(K.x,K.y,tag);
                R->SW=nodo;
            }
        }
        else if(comp==4){
            // Si es NE entramos al cuadrante actual y verificamos si el cuadrante NE apunta a algo.
            //Si apunta a algo vamos a verificar ese cuadrante recursivamente
            if(R->NE!=NULL){
                insertInTree(R->NW,K,tag);
            }else{
                // Si no apunta a nada vamos a crear un nodo y realizamos la insercion
                NodoQuad<T>* nodo = new NodoQuad<T>(K.x,K.y,tag);
                R->SE=nodo;
            }
        }

    }


    void insert(Punto K, T tag){

        if(root==NULL){
            root = new NodoQuad<T>(K.x, K.y, tag);
            cout<<"Arbol estaba vacio, insertando root"<<endl;
            return;
        }

        insertInTree(root,K, tag);

    }

    void getStruct(){

        cout<<"Raiz: "<<root->dato<<endl;
        cout<<"Raiz NW: "<<root->NW->dato<<endl;
        cout<<"Raiz NW NW: "<<root->NW->NW->dato<<endl;
        cout<<"Raiz NW SE: "<<root->NW->SE->dato<<endl;
        cout<<"Raiz SW: "<<root->SW->dato<<endl;
        cout<<"Raiz SE: "<<root->SE->dato<<endl;


    }




};


int main(){

    QuadTree<char> Quadtree(127,127);

    Punto A(70,70);
    Punto B(20,20);
    Punto C(100,100);
    Punto D(60,80);
    Punto E(5,5);
    Punto F(50,50);

    Quadtree.insert(A,'A');
    Quadtree.insert(B,'B');
    Quadtree.insert(C,'C');
    Quadtree.insert(D,'D');
    Quadtree.insert(E,'E');
    Quadtree.insert(F,'F');

    Quadtree.getStruct();



    return 0;







}

