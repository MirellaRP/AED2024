#include <iostream>
#include <cmath>
using namespace std;

#define MAX_STACK_SIZE 100

template <typename T>
class Stack {

    private:

    T list[MAX_STACK_SIZE]; // Aloco memoria para el array 
    int top;

    public:

    // Constructor
    Stack() : top(-1) {}

    bool isfull (){
        if (top >= MAX_STACK_SIZE - 1) // si top tiene mas que 99 es que esta lleno (va de 0 a 99)
            return true;
        return false;
    }

    bool isempty ()
    {
        if (top == -1) // Si top es -1 esta vacio
            return true; 
        return false; 
    }

    T gtop()
    {
        return list[top]; // Obtengo el ultimo valor de la lista de elementos 
    }

    void push(T e )
    {
        (top)++; // Aumento el valor de top
        list[top] = e; //Agrego el elemento a la lista
    }

    void pop()
    {
        (top)--;// A top le bajo el valor por lo que se reescribira la lista cuando se vuelva a usar
        // Nota: basicamente se baja el valor de la lista
    }

};


