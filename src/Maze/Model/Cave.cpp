#include "Cave.h"
Cave::Cave():_matrix(nullptr),_rows(0),_cols(0),_birthLimit(0),_deathLimit(0){
}

Cave::Cave(std::string& filename,int _birth,int death):_matrix(nullptr),_rows(0),_cols(0),_birthLimit(_birth),_deathLimit(death)
{
    std::ifstream file(filename);
    if(!file.is_open()){
        throw std::invalid_argument("Invalid argument, this file is not opened");
    } else {
        std::stringstream ss;
        std::string currentLine="fsda";
        int currentRow=0;
        std::getline(file,currentLine);
        ss.clear();
        ss.str(currentLine);
        try {
            readSize(ss);
            newMatrix();
            while(std::getline(file,currentLine)){
                ss.clear();
                ss.str(currentLine);
                readLine(ss,currentRow);
                currentRow++;
                if(currentRow==_rows){
                    break;
                }
            }
        }  catch (std::exception& e) {
            throw;
        }
    }
}
void Cave::readSize(std::stringstream& ss){
    ss>>_rows;
    if(ss.peek()==' '){
        ss.ignore();
    } else {
        throw std::invalid_argument("Invalid argument, wrong format file!1");
    }
    ss>>_cols;
    if(!ss.eof()){
        throw std::invalid_argument("Invalid argument, wrong format file!2");
    }
}

void Cave::readLine(std::stringstream& ss,int currentRow){
    for(int i=0;i<_cols;i++){
        if(ss.eof()){
            throw std::invalid_argument("Invalid argument, wrong format file!3");
        } else {
            ss>>_matrix[currentRow][i];
            std::cout<<_matrix[currentRow][i]<<" ";
            if(ss.peek()==' '){
                ss.ignore();
            } else if(!(ss.eof()&&i==(_cols-1))){
                throw std::invalid_argument("Invalid argument, wrong format file!4");
            }
        }
    }
    std::cout<<std::endl;
}

Cave::Cave(int rows, int cols, int chance,int _birth,int death):_matrix(nullptr),_rows(rows),_cols(cols),_birthLimit(_birth),_deathLimit(death){
    newMatrix();

    for(int i=0;i<_rows;i++){
        for(int j=0;j<_cols;j++){
            if (arc4random_uniform(100)<static_cast<unsigned int>(chance)) {
                _matrix[i][j]=1;
            }
        }
    }
}
Cave::Cave(const Cave& other):_matrix(nullptr),_rows(0),_cols(0),_birthLimit(0),_deathLimit(0){
    if(&other!=this){
        _rows=other._rows;
        _cols=other._cols;
        _birthLimit=other._birthLimit;
        _deathLimit=other._deathLimit;
        newMatrix();
        for(int i=0;i<_rows;i++){
            for(int j=0;j<_cols;j++){
                _matrix[i][j]=other._matrix[i][j];
            }
        }
    }
}

Cave& Cave::operator=(const Cave& other){
    if(this!=&other){
        if(_matrix!=nullptr) clear();
        _cols=other._cols;
        _rows=other._rows;
        _birthLimit=other._birthLimit;
        _deathLimit=other._deathLimit;
        newMatrix();
        for(int i=0;i<_rows;i++){
            for(int j=0;j<_cols;j++){
                _matrix[i][j]=other._matrix[i][j];
            }
        }
    }
    return *this;
}

void Cave::newMatrix(){
    _matrix=new int*[_rows];
    for(int i=0;i<_rows;i++){
        _matrix[i]=new int[_cols]();
    }
}

int& Cave::operator()(int i, int j){
    return _matrix[i][j];
}

int Cave::getRows(){
    return _rows;
}
int Cave::getCols(){
    return _cols;
}

void Cave::setBirth(int i)
{
    _birthLimit=i;
}

void Cave::setDeath(int i)
{
    _deathLimit=i;
}

void Cave::clear(){
    if(_matrix!=nullptr){
        for(int i=0;i<_rows;i++){
            delete[] _matrix[i];
        }
        delete[] _matrix;
    }
}

Cave::~Cave(){
    clear();
}

void Cave::update(){
    Cave previosCave(*this);
    for(int i=0;i<_rows;i++){
        for(int j=0;j<_cols;j++){
            int numOfNeighbours=findNeighbors(previosCave,i,j);
            if(_matrix[i][j]==DEAD){
                if(numOfNeighbours>_birthLimit){
                    _matrix[i][j] = ALIVE;
                }
            } else {
                if(numOfNeighbours<_deathLimit){
                    _matrix[i][j] = DEAD;
                }
            }
        }
    }
}

void Cave::save(std::string &fileName)
{
    std::ofstream file(fileName);
    if(!file.is_open()){
        throw std::invalid_argument("Invalid argument,failed saving to file!");
    }
    file << _rows << ' ' << _cols << '\n';
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            file << _matrix[i][j];
            if(j!=_cols-1){
                file<<" ";
            } else {
                file<<"\n";
            }
        }
    }
    file.close();
}

int Cave::findNeighbors(Cave& prev,int row,int col){
    int count=0;
    for(int i=-1;i<=1;++i){
        for(int j=-1;j<=1;++j){
            if(i!=0||j!=0){
                int indexICurrentCave=row+i;
                int indexJCurrentCave=col+j;
                if(indexICurrentCave<0||indexJCurrentCave<0||
                        indexICurrentCave>=prev.getRows()||indexJCurrentCave>=prev.getCols()){
                    count++;
                } else {
                    count+=prev._matrix[indexICurrentCave][indexJCurrentCave];
                }
            }
        }
    }
    return count;
}
