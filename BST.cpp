#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

template <typename T>
struct NodeBT {
        T data;
        NodeBT* left;
        NodeBT* right;
    };


template <typename T>
class BSTree {
    
    NodeBT<T>* root;

    public:
    
    BSTree() : root(NULL) {} // Inicializo el root como null 


    // Realizo la busqueda de manera recursiva, pero necesito de entrada el root
    bool find(NodeBT<T>* node, T value){
        if(node == nullptr)
            return false;
        else if(value < node->data)
            return find(node->left, value);
        else if(value > node->data)
            return find(node->right, value);
        else 
            return true;
    }

    bool search(T value){
        return find(root, value);
    }

    void insert(NodeBT<T>* node, T value){
        if(node==NULL){
            // Si es el caso del HEAD es NULL, entra aqui
            NodeBT<T>* nuevo= new NodeBT<T>;
            nuevo->data=value;
            nuevo->left=NULL;
            nuevo->right=NULL;
            root=nuevo;
        }
        else if(value < node->data){
            if(node->left==NULL){
                NodeBT<T>* nuevo = new NodeBT<T>;
                nuevo->data=value;
                nuevo->left=NULL;
                nuevo->right=NULL;
                node->left=nuevo;
            }else{
                insert(node->left, value);
            }

        }else if(value > node->data){
            if(node->right==NULL){
                NodeBT<T>* nuevo = new NodeBT<T>;
                nuevo->data=value;
                nuevo->left=NULL;
                nuevo->right=NULL;
                node->right=nuevo;
            }else{
                insert(node->right, value);
            }
        }
    }


    NodeBT<T>* findNode(NodeBT<T>* node,T value){
        if(node == nullptr)
            return NULL;
        else if(value < node->data)
            return findNode(node->left, value);
        else if(value > node->data)
            return findNode(node->right, value);
        else 
            return node;   
    }

    //Logica Basada en EnoyAlgorithms
    //https://www.enjoyalgorithms.com/blog/inorder-predecessor-binary-search-tree
    NodeBT<T>* findPredecesor(T value){
       
        if(root==NULL){
            // Si tu arbol esta vacio se entrega
            return NULL;
        }

        NodeBT<T>* temp = root;
        NodeBT<T>* predecesor = NULL;
        bool flag=false;

        while(temp!=NULL && flag!=true){
            // Voy a buscar el nodo que tiene el valor
            if(value<temp->data){ // Si el valor es menor que el valor del nodo, voy a la izquierda
                temp=temp->left;
            }
            else if(value>temp->data){ //Si el valor es mayor que el valor del nodo, voy a la guardo que el predecesor puede ser ese y voy a la derecha
                predecesor = temp;
                temp=temp->right;
            }else{
                //Si llega al valor pero si tiene un nodo izquierdo, en ese lado si o si esta su predecesor
                // Aqui se hace lo de clase
                if(temp->left!=NULL){
                    temp=temp->left;
                    while(temp->right!=NULL){
                        temp=temp->right;
                    }
                    predecesor=temp;
                }
                // Si no tiene algo a la izquierda en anterior predecesor queda como el predecesor
                //Rompemos el while
                flag=true;
            }
        }

        return predecesor;
    
    }
    
    //Logica Basada en EnoyAlgorithms
    //https://www.enjoyalgorithms.com/blog/inorder-successor-in-binary-search-tree
    NodeBT<T>* findSuccessor(T value){

        NodeBT<T>* temp = findNode(root,value);
        NodeBT<T>* successor = NULL;
        bool flag=false;
       
        if(root==NULL){
            // Si tu arbol esta vacio se entrega
            cout<<"Root vacio"<<endl;
            return NULL;
        }

        //Si llega al valor pero si tiene un nodo izquierdo, en ese lado si o si esta su predecesor
        // Aqui se hace lo de clase
        if(temp->right!=NULL){
            temp=temp->right;
            while(temp->left!=NULL){
                temp=temp->left;
            }
            successor=temp;
            flag=true;
        }

        temp=root;
        while(temp!=NULL && flag!=true){
            // Voy a buscar el nodo que tiene el valor
            if(value<temp->data){ // Si el valor es menor que el valor del nodo, voy a la guardo que el predecesor puede ser ese y voy a la izquierda
                successor = temp;
                temp=temp->left;
            }
            else if(value>temp->data){ //Si el valor es mayor que el valor del nodo, voy a la derecha
                temp=temp->right;
            }else{
                // Si no tiene algo a la izquierda en anterior predecesor queda como el predecesor
                //Rompemos el while
                flag=true;
            }
        }

        return successor;
    
    }

    // Aqui saco el root
    NodeBT<T>* getroot(){
        return root;
    }

    // Codigo basado en geek for geeks
    //https://www.geeksforgeeks.org/deletion-in-binary-search-tree/


    NodeBT<T>* deleteinTree(NodeBT<T>* node, T value)
    {
        // Caso base
        if (node == NULL)
            return node;

        if (node->data > value)
            node->left = deleteinTree(node->left, value);
        else if (node->data < value)
            node->right = deleteinTree(node->right, value);

        
        else { //Si lo encuentra

            
            if (node->left == NULL) {
                NodeBT<T>* temp = node->right;
                delete node;
                return temp;
            }

            if (node->right == NULL) {
                NodeBT<T>* temp = node->left;
                delete node;
                return temp;
            }

            // Cuando ambos hijos estan pasa esto
            NodeBT<T>* successor = findSuccessor(node->data);
            if(successor==NULL){
                successor=findPredecesor(node->data);
            }
            node->data = successor->data;
            node->right = deleteinTree(node->right, successor->data);
        }
        return node;
    }

    void deleteNode(T value){
        root=deleteinTree(root,value);
    }

    void insertNode(T value){
        insert(root,value);
    }


    // Funcion para visualizar mi arbol binario
    // Funcion generada por chatgpt solo para visualizacion
    void imprimirarbol(NodeBT<T>* node, int space) const {
        if (node == nullptr) {
            return;
        }

        space += 5;

        imprimirarbol(node->right, space);

        cout << endl;
        for (int i = 5; i < space; i++) {
            cout << " "; 
        }
        cout << node->data << "\n";
        imprimirarbol(node->left, space);
    }

    void visualizararbol() const {
        imprimirarbol(root, 0);
    }

    void inorder(NodeBT<T>* node, vector<T>& vector){
        if (node == NULL) {
            return; 
        }
        inorder(node->left,vector);
        vector.push_back(node->data);
        inorder(node->right,vector);
    }

    vector<T> inordertree(){
        vector<int> vector;
        inorder(root,vector);
        return vector;
    }

    void preorder(NodeBT<T>* node, vector<T>& vector){
        if (node == NULL) {
            return; 
        }
        vector.push_back(node->data);
        preorder(node->left,vector);
        preorder(node->right,vector);
    }

    vector<T> preordertree(){
        vector<int> vector;
        preorder(root,vector);
        return vector;
    }

    void posorder(NodeBT<T>* node, vector<T>& vector){
        if (node != NULL) {
            posorder(node->left,vector);
            posorder(node->right,vector);
            vector.push_back(node->data);
        }
        
        
    }

    vector<int> posordertree(){
        vector<int> vector;
        posorder(root,vector);
        return vector;
    }

};

int main(){
    BSTree<int> BST;
    BST.insertNode(2);
    BST.insertNode(8);
    BST.insertNode(3);
    BST.insertNode(4);
    BST.insertNode(6);
    BST.insertNode(10);
    BST.insertNode(1);
    BST.insertNode(5);
    BST.insertNode(7);
    BST.insertNode(9);

    cout<<"Root: "<<BST.getroot()<<endl; //Aqui muestra que apunta a algo
    cout<<"Left Child: "<<BST.getroot()->left->data<<endl;
    cout<<"Right Child: "<<BST.getroot()->right->data<<endl;
    cout<<"Right Child 's Left Child: "<<BST.getroot()->right->left->data<<endl;
    cout<<"Right Child 's Right Child: "<<BST.getroot()->right->right->data<<endl;

    // Search
    cout<<"Found 4?: "<<BST.search(4)<<endl;
    cout<<"Found 11?: "<<BST.search(11)<<endl;

    // Encontrar predecesor y sucesor
    cout<<"Predecesor of 2: "<<BST.findPredecesor(2)->data<<endl;
    cout<<"Successor of 2: "<<BST.findSuccessor(2)->data<<endl;

    // Visualizar arbol
    cout<<"Arbol anterior: "<<endl;
    BST.visualizararbol();
    // Eliminar nodo
    BST.deleteNode(2);
    // Visualizar arbol
    cout<<"Arbol nuevo: "<<endl;
    BST.visualizararbol();
    BST.inordertree();

    // Inorder
    vector<int> inorder=BST.inordertree();

    for(int nodo:inorder){
        cout<<nodo<<" , "; 
    }
    cout<<endl;

    // Preorder
    vector<int> preorder=BST.preordertree();

    for(int nodo:preorder){
        cout<<nodo<<" , "; 
    }
    cout<<endl;

    // Posorder
    vector<int> posorder=BST.posordertree();

    for(int nodo:posorder){
        cout<<nodo<<" , "; 
    }
    cout<<endl;
    
    // Encontrar algo detallado de un arbol
    cout<<BST.findNode(BST.getroot(),8)->left->data<<endl;
}
