#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

template <class T>
class Node {
public:
    T data;
    int pos_row;
    int pos_col;
    Node<T>* next_row;
    Node<T>* next_col;
    Node<T>* down; // Para la lista de filas (columnas)
    Node<T>* right; // Para la lista de columnas (filas)
};

template <class T>
class SparseMatrix {
private:
    Node<T>* header; // Nodo principal que maneja las filas y columnas
    int n_rows, n_cols;

public:
    SparseMatrix(int rows, int cols) : n_rows(rows), n_cols(cols) {
        // Crea el nodo "detalle" que manejará las filas y columnas
        header = new Node<T>;
        header->data = T();
        header->pos_row = -1;
        header->pos_col = -1;
        header->next_row = nullptr;
        header->next_col = nullptr;
        header->down = nullptr;
        header->right = nullptr;

        // Inicializar los encabezados de las filas y columnas
        Node<T>* prev_row = header;
        for (int i = 0; i < n_cols; ++i) {
            Node<T>* new_col_header = new Node<T>;
            new_col_header->data = T();
            new_col_header->pos_row = -1;
            new_col_header->pos_col = i;
            new_col_header->next_row = nullptr;
            new_col_header->next_col = nullptr;
            new_col_header->down = nullptr;
            new_col_header->right = prev_row->right;
            prev_row->right = new_col_header;
            prev_row = new_col_header;
        }

        Node<T>* prev_col = header;
        for (int i = 0; i < n_rows; ++i) {
            Node<T>* new_row_header = new Node<T>;
            new_row_header->data = T();
            new_row_header->pos_row = i;
            new_row_header->pos_col = -1;
            new_row_header->next_row = nullptr;
            new_row_header->next_col = nullptr;
            new_row_header->down = prev_col->down;
            new_row_header->right = nullptr;
            prev_col->down = new_row_header;
            prev_col = new_row_header;
        }
    }

    void insert(int i, int j, T value) {
        if (i < 0 || i >= n_rows || j < 0 || j >= n_cols) return;
        if (value == T()) return; // Evitar insertar valores cero

        Node<T>* newNode = new Node<T>;
        newNode->data = value;
        newNode->pos_row = i;
        newNode->pos_col = j;
        newNode->next_row = nullptr;
        newNode->next_col = nullptr;

        // Inserción por fila
        Node<T>* row = header->down;
        for (int k = 0; k < i; ++k) row = row->down;

        Node<T>* row_current = row;
        while (row_current->right != nullptr && row_current->right->pos_col < j) {
            row_current = row_current->right;
        }
        newNode->right = row_current->right;
        row_current->right = newNode;

        // Inserción por columna
        Node<T>* col = header->right;
        for (int k = 0; k < j; ++k) col = col->right;

        Node<T>* col_current = col;
        while (col_current->down != nullptr && col_current->down->pos_row < i) {
            col_current = col_current->down;
        }
        newNode->down = col_current->down;
        col_current->down = newNode;
    }

void erase(int row, int col) {
    // Verifica si los índices están dentro de los límites
    if (row < 0 || row >= n_rows || col < 0 || col >= n_cols) {
        throw out_of_range("Posición fuera de los límites de la matriz.");
    }

    // Encuentra la fila correspondiente
    Node<T>* prev_row = header;
    Node<T>* current_row = header->down;

    for (int i = 0; i < row; ++i) {
        if (!current_row) return;  // No hay nodos en esta fila
        prev_row = current_row;
        current_row = current_row->down;
    }

    // Si no hay nodos en la fila, salir
    if (!current_row) return;

    // Encuentra el nodo en la columna correspondiente
    Node<T>* prev_col = current_row;
    Node<T>* current_col = current_row->right;

    while (current_col && current_col->pos_col < col) {
        prev_col = current_col;
        current_col = current_col->right;
    }

    // Si el nodo está en la posición buscada, eliminarlo
    if (current_col && current_col->pos_col == col) {
        prev_col->right = current_col->right;  // Ajustar el puntero del nodo anterior
        delete current_col;  // Liberar la memoria
        cout << "Elemento en (" << row << ", " << col << ") eliminado correctamente." << endl;
        return;
    }

    cout << "Elemento en (" << row << ", " << col << ") no encontrado para eliminar." << endl;
}


    T find(int i, int j) const {
        if (i < 0 || i >= n_rows || j < 0 || j >= n_cols)
            throw out_of_range("Posición inválida.");

        // Buscar en la fila
        Node<T>* row = header->down;
        for (int k = 0; k < i; ++k) row = row->down;

        Node<T>* row_current = row;
        while (row_current->right != nullptr && row_current->right->pos_col < j) {
            row_current = row_current->right;
        }
        if (row_current->right && row_current->right->pos_col == j) {
            return row_current->right->data;
        }

        throw out_of_range("Elemento no encontrado.");
    }


    T operator()(int i, int j) const {
    if (i < 0 || i >= n_rows || j < 0 || j >= n_cols) {
        throw out_of_range("Posición inválida.");
    }

    Node<T>* row = header->down;
    for (int k = 0; k < i; ++k) row = row->down;

    Node<T>* current = row;
    while (current && current->right && current->right->pos_col < j) {
        current = current->right;
    }

    if (current && current->right && current->right->pos_col == j) {
        return current->right->data;
    }

    return T(); // Si no se encuentra, retorna el valor por defecto (0 para int).
}


    T& operator()(int i, int j) {
        if (i < 0 || i >= n_rows || j < 0 || j >= n_cols) {
            throw out_of_range("Posición inválida.");
        }

        Node<T>* row = header->down;
        for (int k = 0; k < i; ++k) row = row->down;

        Node<T>* row_current = row;
        while (row_current->right != nullptr && row_current->right->pos_col < j) {
            row_current = row_current->right;
        }

        if (row_current->right && row_current->right->pos_col == j) {
            return row_current->right->data;
        } else {
            insert(i, j, T()); // Inserta un valor por defecto si no existe
            return row_current->right->data;
        }
    }

SparseMatrix<T> operator+(const SparseMatrix<T>& other) const {
    if (n_rows != other.n_rows || n_cols != other.n_cols)
        throw invalid_argument("Las dimensiones no coinciden.");

    SparseMatrix<T> result(n_rows, n_cols);

    for (int i = 0; i < n_rows; ++i) {
        // Agregar los elementos de la primera matriz
        Node<T>* row_current = header->down;
        for (int k = 0; k < i; ++k) row_current = row_current->down;

        Node<T>* current = row_current->right;
        while (current != nullptr) {
            result.insert(i, current->pos_col, current->data);
            current = current->right;
        }

        // Agregar los elementos de la segunda matriz
        Node<T>* other_row = other.header->down;
        for (int k = 0; k < i; ++k) other_row = other_row->down;

        Node<T>* other_current = other_row->right;
        while (other_current != nullptr) {
            T current_value = T(); // Valor por defecto
            Node<T>* result_row = result.header->down;
            for (int k = 0; k < i; ++k) result_row = result_row->down;

            Node<T>* result_current = result_row->right;
            while (result_current != nullptr && result_current->pos_col < other_current->pos_col) {
                result_current = result_current->right;
            }

            if (result_current != nullptr && result_current->pos_col == other_current->pos_col) {
                current_value = result_current->data;
            }

            T sum = current_value + other_current->data;
            result.insert(i, other_current->pos_col, sum);

            other_current = other_current->right;
        }
    }

    return result;
}



SparseMatrix<T> operator-(const SparseMatrix<T>& other) const {
    if (n_rows != other.n_rows || n_cols != other.n_cols)
        throw invalid_argument("Las dimensiones no coinciden.");

    SparseMatrix<T> result(n_rows, n_cols);

    for (int i = 0; i < n_rows; ++i) {
        // Agregar los elementos de la primera matriz
        Node<T>* row_current = header->down;
        for (int k = 0; k < i; ++k) row_current = row_current->down;

        Node<T>* current = row_current->right;
        while (current != nullptr) {
            result.insert(i, current->pos_col, current->data);
            current = current->right;
        }

        // Sustraer los elementos de la segunda matriz
        Node<T>* other_row = other.header->down;
        for (int k = 0; k < i; ++k) other_row = other_row->down;

        Node<T>* other_current = other_row->right;
        while (other_current != nullptr) {
            T current_value = T(); // Valor por defecto
            Node<T>* result_row = result.header->down;
            for (int k = 0; k < i; ++k) result_row = result_row->down;

            Node<T>* result_current = result_row->right;
            while (result_current != nullptr && result_current->pos_col < other_current->pos_col) {
                result_current = result_current->right;
            }

            if (result_current != nullptr && result_current->pos_col == other_current->pos_col) {
                current_value = result_current->data;
            }

            T diff = current_value - other_current->data;
            result.insert(i, other_current->pos_col, diff);

            other_current = other_current->right;
        }
    }

    return result;
}


   
SparseMatrix<T> operator*(const SparseMatrix<T>& other) const {
    if (n_rows != other.n_rows || n_cols != other.n_cols)
        throw invalid_argument("Las dimensiones no coinciden para la multiplicación elemento a elemento.");

    SparseMatrix<T> result(n_rows, n_cols);

    Node<T>* current_row = header->down;
    for (int i = 0; i < n_rows && current_row != nullptr; ++i, current_row = current_row->down) {
        Node<T>* row_node = current_row->right;

        while (row_node != nullptr) {
            // Buscar el valor correspondiente en la otra matriz
            try {
                T other_value = other(row_node->pos_row, row_node->pos_col);
                T product = row_node->data * other_value;
                if (product != T()) {
                    result.insert(row_node->pos_row, row_node->pos_col, product);
                }
            } catch (const out_of_range&) {
                // Si no existe un valor en la otra matriz, considerarlo como cero (no hace nada)
            }
            row_node = row_node->right;
        }
    }

    return result;
}


    SparseMatrix<T> transpose() const {
        SparseMatrix<T> result(n_cols, n_rows);

        for (int i = 0; i < n_rows; ++i) {
            Node<T>* row_current = header->down;
            for (int k = 0; k < i; ++k) row_current = row_current->down;

            Node<T>* current = row_current->right;
            while (current != nullptr) {
                result.insert(current->pos_col, current->pos_row, current->data);
                current = current->right;
            }
        }

        return result;
    }


    void printMatrix() const {
    for (int i = 0; i < n_rows; ++i) {
        Node<T>* current_row = header->down;
        for (int k = 0; k < i; ++k) current_row = current_row->down;

        Node<T>* current = current_row->right;
        for (int j = 0; j < n_cols; ++j) {
            if (current != nullptr && current->pos_col == j) {
                cout << current->data << " ";
                current = current->right;
            } else {
                cout << "0 ";
            }
        }
        cout << endl;
    }
}

};


int main() {
    // Crear una matriz dispersa de 4 filas y 5 columnas
    SparseMatrix<int> mat(4, 5);

    // Insertar algunos valores en la matriz
    mat.insert(0, 0, 1);
    mat.insert(1, 2, 5);
    mat.insert(2, 3, 7);
    mat.insert(3, 4, 9);

    // Imprimir valores de la matriz (accediendo mediante operator() y find)
    cout << "Valor en (0,0): " << mat(0, 0) << endl;
    cout << "Valor en (1,2): " << mat.find(1, 2) << endl;
    cout << "Valor en (2,3): " << mat(2, 3) << endl;
    cout << "Valor en (3,4): " << mat.find(3, 4) << endl;

    // Borrar un valor de la matriz
    mat.erase(1, 2);
    cout << "Valor en (1,2) después de borrar: ";
    try {
        cout << mat.find(1, 2) << endl;
    } catch (const exception& e) {
        cout << e.what() << endl;  // Debería lanzar "Elemento no encontrado."
    }

    // Operaciones aritméticas con matrices
    SparseMatrix<int> mat2(4, 5);
    mat2.insert(0, 0, 1);
    mat2.insert(1, 1, 3);
    mat2.insert(1, 2, 2);
    mat2.insert(3, 3, 4);

    cout<<" Mat1 "<<endl;
    mat.printMatrix();
    cout<<" Mat2 "<<endl;
    mat2.printMatrix();

    SparseMatrix<int> sum = mat + mat2;
    SparseMatrix<int> diff = mat - mat2;
    SparseMatrix<int> product = mat * mat2;

    cout<<" Sum "<<endl;
    sum.printMatrix();
    cout<<" Diff "<<endl;
    diff.printMatrix();
    cout<<" Mult "<<endl;
    product.printMatrix();

    // Imprimir resultado de la suma
    cout << "\nResultado de la suma de matrices (mat + mat2):" << endl;
    cout << "Valor en (0,0): " << sum(0, 0) << endl;
    cout << "Valor en (1,1): " << sum(1, 1) << endl;
    cout << "Valor en (2,2): " << sum(2, 2) << endl;

    // Imprimir resultado de la resta
    cout << "\nResultado de la resta de matrices (mat - mat2):" << endl;
    cout << "Valor en (0,0): " << diff(0, 0) << endl;
    cout << "Valor en (1,1): " << diff(1, 1) << endl;
    cout << "Valor en (2,2): " << diff(2, 2) << endl;

    // Imprimir resultado de la multiplicación
    cout << "\nResultado de la multiplicación de matrices (mat * mat2):" << endl;
    cout << "Valor en (0,0): " << product(0, 0) << endl;
    //cout << product(1, 2) << endl;

    // Transponer la matriz
    SparseMatrix<int> transposeMat = mat.transpose();
    cout<<" transpose "<<endl;
    transposeMat.printMatrix();
    cout << "\nResultado de la transposición de la matriz (mat):" << endl;
    cout << "Valor en (0,0): " << transposeMat(0, 0) << endl;
    //cout << "Valor en (2,1): " << transposeMat(2, 1) << endl;

    return 0;
}
