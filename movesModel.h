#ifndef MOVESMODEL_H
#define MOVESMODEL_H

#include <iostream>
#include "cubeFacesEnum.h"

static std::string SEXYRR = "R U R' U' ";
static std::string SEXYRF = "F U F' U' ";
static std::string SEXYRL = "L U L' U' ";
static std::string SEXYRB = "B U B' U' ";

static std::string SEXYLR = "R' U' R U ";
static std::string SEXYLF = "F' U' F U ";
static std::string SEXYLL = "L' U' L U ";
static std::string SEXYLB = "B' U' B U ";

class MovesModel {
 public:
    MovesModel(CubeFacesEnum face, int quantity = 1, int wide = 1);
    MovesModel(std::string str);

    int wide();
    int quantity();
    CubeFacesEnum face();
    std::string toString();

 private:
    int _wide;
    int _quantity;
    CubeFacesEnum _face;
};

#endif // MOVESMODEL_H