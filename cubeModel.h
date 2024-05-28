#ifndef CUBEMODEL_H
#define CUBEMODEL_H

#include <vector>
#include <map>
#include <iostream>
#include "cubeFacesEnum.h"
#include "movesModel.h"

using namespace std;

class CubeModel {
 public:
    CubeModel(int size);

    int size();
    vector<vector<CubeFacesEnum>> stickers();
    void printCube();

    void solvedCube();
    void moveCube(string moveList);

 private:
    void getSectors();
    void rotate(MovesModel move);
    void makeRotation(int repetitions, vector<pair<CubeFacesEnum, vector<int>>> moves );

    int _size;
    vector<map<FaceSectorEnum, vector<int>>> _sectors;
    vector<vector<CubeFacesEnum>> _stickers;

};

#endif // CUBEMODEL_H