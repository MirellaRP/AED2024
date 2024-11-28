#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

// Basado en https://www.geeksforgeeks.org/quad-tree/

class Punto{
    private:
    int x;
    int y;

    public:
    Punto(int xvalue, int yvalue):x(xvalue),y(yvalue){}
};

template<class T>
class NodoQuad{
    private:
    Punto punto;
    T dato;
    NodoQuad *NW, *NE, *SW, *SE;

    public:
    NodoQuad(int x, int y, T data): punto(new Punto(x,y)),dato(data), NW(NULL),NE(NULL),SE(NULL),SW(NULL){}
};

template<class T>
class QuadTree{

    NodoQuad* root;


    private:


    public:

};

