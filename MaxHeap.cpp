#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;


template <typename T>
class MaxHeap {
    
    NodeBT<T>* root;
    vector<T> Array;
    int nelements;

    public:
    
    MaxHeap() : root(NULL), nelements(0) {} // Inicializo el root como null 

    void MaxHeapify (int index){ // Usando el algoritmo de clase y ayuda de ChatGPT

        int e = 2 * index+1;
        int d = 2 * index+2;
        int mayor=index;

        if(e<=nelements && Array[e]>Array[index]){
            mayor=e;
        }
        if(d<=nelements && Array[d]>Array[mayor]){
            mayor=d;
        }

        if(mayor!=index){
            swap(Array[index],Array[mayor]);
            MaxHeapify(mayor);
        }
    }

    // void BuildMaxHeap(){ // Usando el algoritmo de clase y ayuda de ChatGPT
    //     nelements=Array.size();
    //     for(int i= nelements/2 - 1; i>=0;i--){
    //         MaxHeapify(i);
    //     }
    // }// Puedo usarlo para otro array que quiera ordenar independientemente

    
    vector<T> BuildMaxHeap(vector<T> v){ // Usando el algoritmo de clase y ayuda de ChatGPT
        vector<T> prev=Array;
        int prevne= nelements;
        Array=v;
        nelements=v.size();
        for(int i= v.size()/2 - 1; i>=0;i--){
            MaxHeapify(i);
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
        while(index>0 && Array[(index-1)/2]<Array[index]){
            swap(Array[index],Array[(index-1)/2]);
            index=(index-1)/2;
        }
    }

    T pop(){
        swap(Array[0],Array[nelements-1]);
        T value = Array[nelements-1];
        Array.pop_back();
        nelements=Array.size();
        MaxHeapify(0);
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

    MaxHeap<int> MH;

    vector<int> arr={44,42,35,33,31,19,27,10,26,14};

    for(int val:arr){
        MH.insert(val);
    }
    
    vector<int> ArrayFinal = MH.gArray();

    for(int val:ArrayFinal){
        cout<<val<<" ";
    }
    cout<<endl;

    // Si se quiere insertar de frente un vector y ordenarlo se usa BuilMaxHeap sin afectar al Array del sistema
    vector<int> arr2={4,1,3,2,16,9,10,14,8,7};
    
    vector<int> bmh=MH.BuildMaxHeap(arr2);
    for(int val:bmh){
        cout<<val<<" ";
    }
    cout<<endl;


    MH.pop();

    vector<int> a=MH.gArray();
    for(int val:a){
        cout<<val<<" ";
    }
    cout<<endl;


    


}
