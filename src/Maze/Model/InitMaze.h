#pragma once
#include "Matrix.h"
#include <time.h>
#include <QString>
#include <fstream>

namespace s21 {

class InitMaze {
 private:
    Matrix* rightSide;
    Matrix* bottomSide;
    std::vector<size_t>* mazeLine;
    size_t varietyCount;
 public:
    InitMaze();
    ~InitMaze();
    void initByFile(std::string fileName);
    void writeToFile(QString& filePath);
    void setVariety();
    void makeRightWalls(int i, Matrix& right);
    void uniteVarieties(size_t _new, size_t _old);
    bool isCellUnique(int position);
    int countVarieties(int varietyNum);
    void checkBottomWalls(int i, Matrix& bottom);
    void makeBottomWalls(int i, Matrix& bottom);
    void makeNewLine(int row, Matrix& bottom);
    void makeLastLine(Matrix& right, Matrix& bottom);
    void ellersAlhoritm(int rowsMaze, int colsMaze);
    int& getRightValue(int i, int j);
    int getBottomValue(int i, int j);
    int getMazeRows();
    int getMazeCols();
};

}  // namespace s21
