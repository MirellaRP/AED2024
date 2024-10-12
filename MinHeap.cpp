#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

template <typename T>
class MinHeap {
    
    NodeBT<T>* root;
    vector<T> Array;
    int nelements;

    public:
    
    MinHeap() : root(NULL), nelements(0) {} // Inicializo el root como null 

    void MinHeapify (int index){ // Usando el algoritmo de clase y ayuda de ChatGPT

        int e = 2 * index+1;
        int d = 2 * index+2;
        int menor=index;

        if(e<=nelements && Array[e]<Array[index]){
            menor=e;
        }
        if(d<=nelements && Array[d]<Array[menor]){
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

};

int main(){

    MinHeap<int> MinH;

    vector<int> arr={10,14,19,26,31,42,27,44,35,33};

    for(int val:arr){
        MinH.insert(val);
    }
    
    vector<int> ArrayFinal = MinH.gArray();

    for(int val:ArrayFinal){
        cout<<val<<" ";
    }
    cout<<endl;

    // Si se quiere insertar de frente un vector y ordenarlo se usa BuilMaxHeap sin afectar al Array del sistema
    vector<int> arr2={13,75,79,54,2,3};
    
    vector<int> bmh=MinH.BuildMinHeap(arr2);
    for(int val:bmh){
        cout<<val<<" ";
    }
    cout<<endl;

    MinH.pop();

    vector<int> a=MinH.gArray();
    for(int val:a){
        cout<<val<<" ";
    }
    cout<<endl;


    


}
