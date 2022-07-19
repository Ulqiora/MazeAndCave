#include "Controller.h"

namespace s21 {

    Controller::Controller(InitMaze* otherModel) : Model(otherModel) {
        myPath = new FindPath(otherModel);
    }

    Controller::~Controller() {
        delete myPath;
    }

    size_t Controller::getRight(int i, int j) {
        return Model->getRightValue(i, j);
    }

    size_t Controller::getBottom(int i, int j) {
        return Model->getBottomValue(i, j);
    }

    void Controller::initModel(std::string fName) {
        Model->initByFile(fName);
    }

    void Controller::generateMaze(int height, int width) {
        Model->ellersAlhoritm(height, width);
    }

    void Controller::saveToFile(QString& filePath) {
        Model->writeToFile(filePath);
    }

    InitMaze& Controller::getModel() {
        return *Model;
    }

    int& Controller::getCount() {
        return myPath->getNewCount();
    }

    int& Controller::getPValue(int i, int j) {
        return myPath->getPathValue(i, j);
    }

    int& Controller::getRoadValH(int pos) {
        return myPath->getRoadValueH(pos);
    }

    int& Controller::getRoadValV(int pos) {
        return myPath->getRoadValueV(pos);
    }

    int Controller::getMRows() {
        return Model->getMazeRows();
    }

    int Controller::getMCols() {
        return Model->getMazeCols();
    }

}  // namespace s21
