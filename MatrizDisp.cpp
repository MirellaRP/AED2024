#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

// Se implemento con chatpgt como se indico que se podia

template <class T>
class Node {
    public:
    T data;
    int pos_row;
    int pos_col;
    Node<T>* next_row;
    Node<T>* next_col;
};

template <class T>
class SparseMatrix {
    private:
    vector<Node<T>*> rows;
    vector<Node<T>*> cols;
    int n_cols;
    int n_rows;


    public:

    SparseMatrix(int rows_count, int cols_count): rows(rows_count, nullptr), cols(cols_count, nullptr), n_cols(cols_count), n_rows(rows_count) {}
    

    void insert(int i, int j, T valor){

        // Verifico si esta entre los rangos de valores
        if (i < 0 || i >= n_rows || j < 0 || j >= n_cols) {
            return;
        }

        // Si por algun motivo ingresa un 0 no se le permite ingresarlo en la matriz
        if (valor == 0) {
            return;
        }

        // Se crea el nuevo nodo y se inicializa las propiedades
        Node<T>* nodo = new Node<T>;
        nodo->data = valor;
        nodo->pos_row = i;
        nodo->pos_col = j;
        nodo->next_row = NULL;
        nodo->next_col = NULL;

        // Insercion por fila
        // Si esta vacia, se apunta hacia el nodo, siendo su primer valor
        if (rows[i]==NULL) {
            rows[i] = nodo;
        } else {

            Node<T>* current = rows[i];
            Node<T>* prev = NULL;

            // Se camina hasta la poscion indicada
            while (current && current->pos_col < j) {
                prev = current;
                current = current->next_row;
            }

            // Si el nodo existe se actualiza el valor
            if (current && current->pos_col == j) {
                current->data = valor;
                delete nodo;
                return;
            }

            // Si no existe se inserta el nodo despues del anterior
            if (prev) {
                prev->next_row = nodo;
            } else {
                rows[i] = nodo;
            }
            // Se conecta
            nodo->next_row = current;
        }

        // Si esta vacia, se apunta hacia el nodo, siendo su primer valor
        if (cols[j]==NULL) {
            cols[j] = nodo;
        } else {
            Node<T>* current = cols[j];
            Node<T>* prev = NULL;
            // Se camina hasta la poscion indicada
            while (current && current->pos_row < i) {
                prev = current;
                current = current->next_col;
            }
            // Si el nodo existe se retorna, pues ya se actualizo
            if (current && current->pos_row == i) {
                return;
            }

            // Si no existe se inserta el nodo despues del anterior
            if (prev) {
                prev->next_col = nodo;
            } else {
                cols[j] = nodo;
            }
            // Se conecta
            nodo->next_col = current;
        }

    }

    void erase(int i, int j) {

        // Se verifica los rangos de valores en la matriz
        if (i < 0 || i >= n_rows || j < 0 || j >= n_cols) {
            return; 
        }

        // FILA
        // Primero nos posicionamos en la fila
        Node<T>* current = rows[i];
        Node<T>* prev = NULL;

        // Se avanza hasta la columna j
        while (current && current->pos_col < j) {
            prev = current; 
            current = current->next_row;
        }

        // Cuando se encuentre se desconecta 
        if (current && current->pos_col == j) { 
            if (prev) {
                // Se desconecta y se conecta el previo con el siguiente
                prev->next_row = current->next_row;
            } else {
                // Si no existe previo es porque esta al inicio, asi que se conecta al siguiente
                rows[i] = current->next_row; 
            }
        }

        // COLUMNA
        // Basicamente lo mismo de arriba pero para la columna
        current = cols[j];
        prev = NULL;

        while (current && current->pos_row < i) {
            prev = current;
            current = current->next_col;
        }

        if (current && current->pos_row == i) { 
            if (prev) {
                prev->next_col = current->next_col;
            } else {
                cols[j] = current->next_col;
            }
        }
        // Se elimina el nodo
        delete current;
    }

    T find(int i, int j) const {
        if (i < 0 || i >= n_rows || j < 0 || j >= n_cols) {
            throw out_of_range("Esta poscion no existe");
        }

        // Se inicia la busqueda en i
        Node<T>* current = rows[i];

        // Se camina hasta j
        while (current && current->pos_col < j) {
            current = current->next_row; 
        }

        // Si se encuentra se se devuelve el valor
        if (current && current->pos_col == j) {
            return current->data;
        }

        // Si no se encuentra sale el mensaje
        throw out_of_range("El elemento no existe");
    }


    T operator()(int i, int j) const {
        return find(i, j);
    }

    T& operator()(int i, int j) {
    if (i < 0 || i >= n_rows || j < 0 || j >= n_cols) {
        throw out_of_range("Índices fuera de rango");
    }

    Node<T>* current = rows[i];
    Node<T>* prev = nullptr;

    while (current && current->pos_col < j) {
        prev = current;
        current = current->next_row;
    }

    if (!current || current->pos_col != j) {
        // Crear y conectar el nodo si no existe
        Node<T>* nodo = new Node<T>;
        nodo->data = 0;  // Inicializar con 0
        nodo->pos_row = i;
        nodo->pos_col = j;
        nodo->next_row = current;

        if (prev) {
            prev->next_row = nodo;
        } else {
            rows[i] = nodo;
        }

        // Ahora manejar la conexión en la columna
        current = cols[j];
        prev = nullptr;

        while (current && current->pos_row < i) {
            prev = current;
            current = current->next_col;
        }

        nodo->next_col = current;
        if (prev) {
            prev->next_col = nodo;
        } else {
            cols[j] = nodo;
        }

        current = nodo;  // Actualizar current al nodo recién creado
    }

    return current->data;
}



    SparseMatrix<T> operator+(const SparseMatrix<T>& other) const {
        if (n_rows != other.n_rows || n_cols != other.n_cols) {
            throw invalid_argument("Las dimensiones no coinciden.");
        }

        SparseMatrix<T> result(n_rows, n_cols);

        for (int i = 0; i < n_rows; ++i) {
            Node<T>* current = rows[i];
            while (current) {
                result.insert(current->pos_row, current->pos_col, current->data);
                current = current->next_row;
            }

            current = other.rows[i];
            while (current) {
                result.insert(current->pos_row, current->pos_col, 
                    result(current->pos_row, current->pos_col) + current->data);
                current = current->next_row;
            }
        }

        return result;
    }

    SparseMatrix<T> operator-(const SparseMatrix<T>& other) const {
        if (n_rows != other.n_rows || n_cols != other.n_cols) {
            throw invalid_argument("Las dimensiones no coinciden.");
        }

        SparseMatrix<T> result(n_rows, n_cols);

        for (int i = 0; i < n_rows; ++i) {
            Node<T>* current = rows[i];
            while (current) {
                result.insert(current->pos_row, current->pos_col, current->data);
                current = current->next_row;
            }

            current = other.rows[i];
            while (current) {
                result.insert(current->pos_row, current->pos_col, 
                    result(current->pos_row, current->pos_col) - current->data);
                current = current->next_row;
            }
        }

        return result;
    }

    SparseMatrix<T> transpose() const {

        SparseMatrix<T> result(n_cols, n_rows);
        for (int i = 0; i < n_rows; ++i) {
            Node<T>* current = rows[i];
            while (current) {
                result.insert(current->pos_col, current->pos_row, current->data);
                current = current->next_row;
            }
        }
        return result;
    }

    // SparseMatrix<T> operator*(const SparseMatrix<T>& other) const {
    //     if (n_cols != other.n_rows) {
    //         throw invalid_argument("Las dimensiones no permiten multiplicación.");
    //     }

    //     SparseMatrix<T> result(n_rows, other.n_cols);

    //     for (int i = 0; i < n_rows; ++i) {
    //         for (int j = 0; j < other.n_cols; ++j) {
    //             T sum = 0;
    //             Node<T>* row_current = rows[i];
    //             while (row_current) {
    //                 Node<T>* col_current = other.cols[j];
    //                 while (col_current && col_current->pos_row < row_current->pos_col) {
    //                     col_current = col_current->next_col;
    //                 }
    //                 if (col_current && col_current->pos_row == row_current->pos_col) {
    //                     sum += row_current->data * col_current->data;
    //                 }
    //                 row_current = row_current->next_row;
    //             }
    //             if (sum != 0) {
    //                 result.insert(i, j, sum);
    //             }
    //         }
    //     }

    //     return result;
    // }

    SparseMatrix<T> operator*(const SparseMatrix<T>& other) const {
    if (n_rows != other.n_rows || n_cols != other.n_cols) {
        throw invalid_argument("Las dimensiones no coinciden para la multiplicación elemento a elemento.");
    }

    SparseMatrix<T> result(n_rows, n_cols);

    // Recorrer filas de la matriz actual
    for (int i = 0; i < n_rows; ++i) {
        Node<T>* current = rows[i];

        while (current) {
            // Buscar el valor correspondiente en la otra matriz
            try {
                T other_value = other(current->pos_row, current->pos_col);
                T product = current->data * other_value;

                if (product != 0) {
                    result.insert(current->pos_row, current->pos_col, product);
                }
            } catch (const out_of_range&) {
                // Si no hay elemento en la otra matriz, el producto es 0 y no hacemos nada.
            }
            current = current->next_row;
        }
    }

    return result;
}


    void printMatrix() const {
    for (int i = 0; i < n_rows; ++i) {
        for (int j = 0; j < n_cols; ++j) {
            Node<T>* current = rows[i];
            bool found = false;

            // Buscar si hay un nodo en la posición actual
            while (current) {
                if (current->pos_col == j) {
                    cout << current->data << " ";
                    found = true;
                    break;
                }
                current = current->next_row;
            }

            // Si no hay nodo en esta posición, imprimir 0
            if (!found) {
                cout << "0 ";
            }
        }
        cout << endl;  // Cambiar de fila
    }
}


    
};


int main() {
    SparseMatrix<int> matriz1(3, 3);
    SparseMatrix<int> matriz2(3, 3);

    // Insertamos valores
    matriz1(0, 1) = 10;
    matriz1(1, 2) = 20;

    matriz2(0, 1) = 5;
    matriz2(1, 2) = -10;

    // Mostrar matriz1
    cout << "Matriz 1:" << endl;
    matriz1.printMatrix();

    // Mostrar matriz2
    cout << "Matriz 2:" << endl;
    matriz2.printMatrix();

    // Suma
    auto suma = matriz1 + matriz2;
    cout << "Suma de Matriz 1 y Matriz 2:" << endl;
    suma.printMatrix();

    // Transpuesta
    auto transpuesta = matriz1.transpose();
    cout << "Transpuesta de Matriz 1:" << endl;
    transpuesta.printMatrix();

    // Multiplicación
    auto multiplicacion = matriz1 * matriz2;
    cout << "Multiplicación de Matriz 1 y Matriz 2:" << endl;
    multiplicacion.printMatrix();

    return 0;
}
