#pragma once
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

namespace s21 {

class Matrix {
 private:
    int _rows, _cols;
    int** _matrix;
    int** new_matrix(int rows, int columns);

 public:
    Matrix();
    Matrix(int rows, int columns);
    ~Matrix();
    int& operator()(int row, int col);
    Matrix& operator=(const Matrix& other);
    int& getValue(int i, int j);
    int getRows();
    int getCols();
    void print_value();  // УДАЛИТЬ!!
};

void initByFile(std::string fileName);

}  // namespace s21
