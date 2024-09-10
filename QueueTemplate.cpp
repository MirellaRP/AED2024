#include <iostream>
#include <cmath>
using namespace std;

#define MAX_Q_SIZE 100

template <typename T>
class Queue {

    private:

    T list[MAX_Q_SIZE]; // Aloco memoria para el array 
    int front;
    int rear;

    public:

    // Constructor
    Queue() : front(0),rear(0) {}

    bool isfull ()
    {
        if (front == ((rear + 1) % MAX_Q_SIZE))
            return true;
        return false;
    }

    int isempty ()
    {
        if (front == rear)
            return true;
        return false;
    }

    T gfront()
    {
        return list[(front + 1) % MAX_Q_SIZE];
    }

    void enqueue(T e)
    {
        rear = (rear + 1)%MAX_Q_SIZE;
        list[rear] = e;
    }

    void dequeue()
    {
        front =(front + 1)%MAX_Q_SIZE;
    }
};



int main(){
    Queue<int> queue1;
    queue1.enqueue(6);

    int front = queue1.gfront();
    cout << "Front: " << front << endl;

    queue1.dequeue();

    cout << "Lista vacia: " << queue1.isempty() << endl;
}