#ifndef RUBIKSMODEL_H
#define RUBIKSMODEL_H

#include <vector>
#include <map>
#include <iostream>
#include "cubeFacesEnum.h"
#include "movesModel.h"

using namespace std;

constexpr int SIZE = 3;

class RubiksModel {
 public:
    RubiksModel();

    void printCube();

    void solvedCube();
    void moveCube(string moveList);

    vector<pair<CornerPiecesEnum, PieceOrientation>> _corners;
    vector<pair<EdgePiecesEnum, PieceOrientation>> _edges;
    vector<CubeFacesEnum> _centers;

 private:
    void printVoid();
    void rotate(MovesModel move);

};

#endif // RUBIKSMODEL_H