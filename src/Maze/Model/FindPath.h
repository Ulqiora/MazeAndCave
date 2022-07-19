#pragma once
#include "InitMaze.h"
#include <vector>
#include <qdebug.h>

namespace s21 {

struct roadPoint {
    int vert = -1;
    int horiz = -1;
};

class FindPath {
 private:
        InitMaze* FindModel;
        Matrix* path;
        int oldCount = 0;
        int newCount = 1;
        int roadCount = 0;
        bool isPathExists;
        std::vector<roadPoint>* roadPath;
        roadPoint checkRoad(const roadPoint& coord);
        void checkEnvironment(int i, int j);
        void findRoad(int xEnd, int yEnd);
 public:
        explicit FindPath(InitMaze* Model);
        ~FindPath();
        void fillPath(int xBegin, int yBegin);
        void waveAlhoritm(int vEnd, int hEnd);
        int& getPathValue(int i, int j);
        int& getRoadValueH(int pos);
        int& getRoadValueV(int pos);
        int& getNewCount();
        void printPath();  // DELETE
};
}  // namespace s21
