#include "FindPath.h"

namespace s21 {
FindPath::FindPath(InitMaze* Model) : FindModel(Model) {
    path = new Matrix(Model->getMazeRows(), Model->getMazeCols());
    roadPath = new std::vector<roadPoint>;
    isPathExists = false;
}

FindPath::~FindPath() {
    delete path;
    delete roadPath;
}

void FindPath::fillPath(int vBegin, int hBegin) {
    for (int i = 0; i < path->getRows(); i++) {
        for (int j = 0; j < path->getCols(); j++) {
            path->getValue(i, j) = -1;
        }
    }
    path->getValue(vBegin, hBegin) = 0;
}


void FindPath::checkEnvironment(int i, int j) {
    if (FindModel->getRightValue(i, j) == 0 && path->getValue(i, j+1) == -1) {
        path->getValue(i, j+1) = newCount;
        isPathExists = true;
    }
    if (FindModel->getBottomValue(i, j) == 0 && path->getValue(i+1, j) == -1) {
        path->getValue(i+1, j) = newCount;
        isPathExists = true;
    }
    if (j > 0 && FindModel->getRightValue(i, j-1) == 0 && path->getValue(i, j-1) == -1) {
        path->getValue(i, j-1) = newCount;
        isPathExists = true;
    }
    if (i > 0 && FindModel->getBottomValue(i-1, j) == 0 && path->getValue(i-1, j) == -1) {
        path->getValue(i-1, j) = newCount;
        isPathExists = true;
    }
}

roadPoint FindPath::checkRoad(const roadPoint& coord) {
    roadPoint newPoint;
    if (FindModel->getRightValue(coord.vert, coord.horiz) == 0
            && getPathValue(coord.vert, coord.horiz + 1) == roadCount) {
        newPoint.vert = coord.vert;
        newPoint.horiz = coord.horiz + 1;
    } else if (FindModel->getBottomValue(coord.vert, coord.horiz) == 0
               && getPathValue(coord.vert+1, coord.horiz) == roadCount) {
        newPoint.vert = coord.vert + 1;
        newPoint.horiz = coord.horiz;
    } else if (coord.horiz > 0 && FindModel->getRightValue(coord.vert, coord.horiz-1) == 0
               && getPathValue(coord.vert, coord.horiz-1) == roadCount) {
        newPoint.vert = coord.vert;
        newPoint.horiz = coord.horiz - 1;
    } else if (coord.vert > 0 && FindModel->getBottomValue(coord.vert-1, coord.horiz) == 0
               && getPathValue(coord.vert-1, coord.horiz) == roadCount) {
        newPoint.vert = coord.vert - 1;
        newPoint.horiz = coord.horiz;
    }
    return newPoint;
}

void FindPath::findRoad(int vEnd, int hEnd) {
    roadPath->clear();
    roadCount = oldCount - 1;
    roadPoint firstPoint;
    firstPoint.vert = vEnd;
    firstPoint.horiz = hEnd;
    roadPath->push_back(firstPoint);
    for (int i = 0; i < newCount; i++) {
        roadPath->push_back(checkRoad(roadPath->data()[i]));
        roadCount--;
    }
}

void FindPath::waveAlhoritm(int vEnd, int hEnd) {
    while (path->getValue(vEnd, hEnd) == -1) {
        isPathExists = false;
        for (int i = 0; i < path->getRows(); i++) {
            for (int j = 0; j < path->getCols(); j++) {
                if (path->getValue(i, j) == oldCount) {
                    checkEnvironment(i, j);
                }
            }
        }
        oldCount = newCount;
        newCount++;
        if (!isPathExists) {
            throw std::out_of_range("ERROR::There is no way out!");
        }
    }
    findRoad(vEnd, hEnd);
}

int& FindPath::getPathValue(int i, int j) {
    return path->getValue(i, j);
}

int& FindPath::getRoadValueH(int pos) {
    return roadPath->data()[pos].horiz;
}

int& FindPath::getRoadValueV(int pos) {
    return roadPath->data()[pos].vert;
}

int& FindPath::getNewCount() {
    return newCount;
}

void FindPath::printPath() {
    path->print_value();
}

}  // namespace s21
