#include "InitMaze.h"

namespace s21 {

InitMaze::InitMaze()
    : rightSide(new Matrix)
    , bottomSide(new Matrix)
    , mazeLine(new std::vector<size_t>)
    , varietyCount(0) {
}

InitMaze::~InitMaze() {
    delete rightSide;
    delete bottomSide;
    delete mazeLine;
}

void InitMaze::initByFile(std::string fileName) {
    std::ifstream F(fileName);
    if (!F.is_open()) {
        throw std::invalid_argument("ERROR::Could not open file.");
    } else {
        std::string number;
        F >> number;
        int rows = std::stoi(number);
        F >> number;
        int columns = std::stoi(number);
        if (rows < 0 || rows > 50 || columns < 0 || columns > 50) {
            throw std::invalid_argument("ERROR::Incorrect file!");
        }
        Matrix right_tmp(rows, columns);
        Matrix bottom_tmp(rows, columns);
        int i, j;
        size_t checkZeroOne;
        for (i = 0; i < rows; i++) {
            for (j = 0; j < columns; j++) {
                F >> number;
                checkZeroOne = std::stoul(number);
                if (checkZeroOne > 1) {
                    throw std::invalid_argument("ERROR::Incorrect file!");
                } else {
                    right_tmp(i, j) = std::stoul(number);
                }
            }
        }
        for (i = 0; i < rows; i++) {
            for (j = 0; j < columns; j++) {
                F >> number;
                checkZeroOne = std::stoul(number);
                if (checkZeroOne > 1) {
                    throw std::invalid_argument("ERROR::Incorrect file!");
                } else {
                    bottom_tmp(i, j) = std::stoul(number);
                }
            }
        }
        *rightSide = right_tmp;
        *bottomSide = bottom_tmp;
        F.close();
    }
}

void InitMaze::writeToFile(QString& filePath) {
    std::ofstream wFile;
    wFile.open(filePath.toStdString());
    if (!wFile.is_open()) {
        throw std::invalid_argument("ERROR::Failed saving to file");
    } else {
        wFile << getMazeRows() << ' ' << getMazeCols() << '\n';
        int i, j;
        for (i = 0; i < getMazeRows(); i++) {
            for (j = 0; j < getMazeCols(); j++) {
                wFile << getRightValue(i, j) << ' ';
            }
            wFile << '\n';
        }
        wFile << '\n';
        for (i = 0; i < getMazeRows(); i++) {
            for (j = 0; j < getMazeCols(); j++) {
                wFile << getBottomValue(i, j) << ' ';
            }
            wFile << '\n';
        }
    }
    wFile.close();
}

void InitMaze::setVariety() {
    for (size_t i = 0; i < mazeLine->size(); i++) {
        if (mazeLine->data()[i] == 0) {
            varietyCount++;
            mazeLine->data()[i] = varietyCount;
        }
    }
}

void InitMaze::makeRightWalls(int i, Matrix& right) {
    for (int j = 0; j < right.getCols() - 1; j++) {
        if (mazeLine->data()[j] == mazeLine->data()[j+1]) {
            right(i, j) = 1;
        } else {
            bool randomChoice = arc4random_uniform(100) % 2;
            if (randomChoice) {
                right(i, j) = 1;
            } else {
                right(i, j) = 0;
                uniteVarieties(mazeLine->data()[j], mazeLine->data()[j+1]);
            }
        }
    }
    right(i, right.getCols() - 1) = 1;
}

void InitMaze::uniteVarieties(size_t _new, size_t _old) {
    for (size_t i = 0; i < mazeLine->size(); i++) {
        if (mazeLine->data()[i] == _old)
            mazeLine->data()[i] = _new;
    }
}

bool InitMaze::isCellUnique(int position) {
    bool result = true;
    size_t pos = position;
    for (size_t i = 0; i < mazeLine->size(); i++) {
        if (i != pos && mazeLine->data()[i] == mazeLine->data()[pos])
            result = false;
    }
    return result;
}

int InitMaze::countVarieties(int varietyNum) {
    int countVar = 0;
    int size = mazeLine->size();
    for (int i = 0; i < size; i++) {
        if (i != varietyNum && mazeLine->data()[i] == mazeLine->data()[varietyNum]) {
            countVar++;
        }
    }
    return countVar;
}

void InitMaze::checkBottomWalls(int i, Matrix& bottom) {
    for (int j = 0; j < bottom.getCols(); j++) {
        int count = 0;
        for (int k = 0; k < bottom.getCols(); k++) {
            if (mazeLine->data()[j] == mazeLine->data()[k] && bottom(i, k) == 1) {
                count++;
            }
        }
        if (countVarieties(j) <= count) {
            bottom(i, j) = 0;
        }
    }
}

void InitMaze::makeBottomWalls(int i, Matrix& bottom) {
    for (int j = 0; j < bottom.getCols(); j++) {
        if (isCellUnique(j)) {
            bottom(i, j) = 0;
        } else {
            bool randomChoice = arc4random_uniform(100) % 2;
            if (randomChoice) {
                bottom(i, j) = 1;
            } else {
                bottom(i, j) = 0;
            }
        }
    }
}

void InitMaze::makeNewLine(int row, Matrix& bottom) {
    for (size_t i = 0; i < mazeLine->size(); i++) {
        if (bottom(row, i) == 1)
            mazeLine->data()[i] = 0;
    }
}

void InitMaze::makeLastLine(Matrix& right, Matrix& bottom) {
    for (int i = 0; i < bottom.getCols(); i++) {
        bottom(bottom.getRows() - 1, i) = 1;
    }
    for (int j = 0; j < right.getCols() - 1; j++) {
        if (mazeLine->data()[j] != mazeLine->data()[j+1]) {
            right(right.getRows() - 1, j) = 0;
            uniteVarieties(mazeLine->data()[j], mazeLine->data()[j+1]);
        }
    }
}

void InitMaze::ellersAlhoritm(int rowsMaze, int colsMaze) {
    varietyCount = 0;
    mazeLine->clear();
    Matrix rightMazeWalls(rowsMaze, colsMaze);
    Matrix bottomMazeWalls(rowsMaze, colsMaze);
    for (int k = 0; k < colsMaze; k++) {
        mazeLine->push_back(varietyCount);
    }
    for (int i = 0; i < rowsMaze; i++) {
        setVariety();
        makeRightWalls(i, rightMazeWalls);
        makeBottomWalls(i, bottomMazeWalls);
        checkBottomWalls(i, bottomMazeWalls);
        if (i < rowsMaze - 1) {
            makeNewLine(i, bottomMazeWalls);
        } else {
            makeLastLine(rightMazeWalls, bottomMazeWalls);
        }
    }
    *rightSide = rightMazeWalls;
    *bottomSide = bottomMazeWalls;
}

int& InitMaze::getRightValue(int i, int j) {
    return rightSide->getValue(i, j);
}

int InitMaze::getBottomValue(int i, int j) {
    return bottomSide->getValue(i, j);
}

int InitMaze::getMazeRows() {
    return rightSide->getRows();
}

int InitMaze::getMazeCols() {
    return rightSide->getCols();
}

}  // namespace s21
