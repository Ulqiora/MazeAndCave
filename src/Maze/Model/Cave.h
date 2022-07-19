#ifndef CAVE_H
#define CAVE_H
#include <iostream>
#include <string>
#include <fstream>
#include <exception>
#include <sstream>
class Cave
{
public:
    enum CellState{DEAD=0,ALIVE};
    Cave();
    explicit Cave(std::string& filename,int _birth,int death);
    Cave(int rows, int cols, int chance,int _birth,int death);
    Cave(const Cave& other);
    Cave& operator=(const Cave& cave);
    int& operator()(int i, int j);
    int getRows();
    int getCols();
    void setBirth(int i);
    void setDeath(int i);
    virtual ~Cave();
    void update();
    void save(std::string& fileName);
private:
    void newMatrix();
    void clear();
    int findNeighbors(Cave& prev,int row,int col);
    void readSize(std::stringstream& ss);
    void readLine(std::stringstream& ss,int currentRow);
private:
    int** _matrix;
    int _rows;
    int _cols;
    int _birthLimit;
    int _deathLimit;
};

#endif // CAVE_H
