#include "Matrix.h"

namespace s21 {

int** Matrix::new_matrix(int rows, int columns) {
    int** _matrix = new int*[rows];
    for (int i = 0; i < _rows; i++)
        _matrix[i] = new int[columns];
    return _matrix;
}

Matrix::Matrix() : _rows(4), _cols(4) {
    _matrix = new_matrix(4, 4);
}

Matrix::Matrix(int rows, int columns) : _rows(rows), _cols(columns) {
    if (rows <= 0 || columns <= 0) {
        throw std::out_of_range(
        "ERROR::matrices should have positive size");
    }
    _matrix = new_matrix(rows, columns);
}

Matrix::~Matrix() {
    if (_matrix) {
        for (int i = 0; i < _rows; i++)
            delete[] _matrix[i];
        delete[] _matrix;
    }
    _rows = 0;
    _cols = 0;
}

int& Matrix::operator()(int row, int col) {
    if (row > _rows || col > _cols || row < 0 || col < 0) {
        throw std::out_of_range("ERROR::Incorrect input");
    }
    return _matrix[row][col];
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (_rows != other._rows || _cols != other._cols) {
        this->~Matrix();
        _rows = other._rows;
        _cols = other._cols;
        _matrix = new_matrix(other._rows, other._cols);
    }
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            _matrix[i][j] = other._matrix[i][j];
        }
    }
    return *this;
}

int& Matrix::getValue(int i, int j) {
    if (i < 0 || j < 0 || i > _rows || j > _cols) {
        throw std::out_of_range("ERROR::Incorrect matrix index");
    }
    return _matrix[i][j];
}

int Matrix::getRows() {
    return _rows;
}

int Matrix::getCols() {
    return _cols;
}


// УДАЛИТЬ!!
void Matrix::print_value() {
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            std::cout << _matrix[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

}  // namespace s21
