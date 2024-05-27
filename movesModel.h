#ifndef MOVESMODEL_H
#define MOVESMODEL_H

#include <iostream>
#include "cubeFacesEnum.h"

class MovesModel {
 public:
    MovesModel(CubeFacesEnum face, int quantity = 1, int wide = 1);
    MovesModel(std::string str);

    int wide();
    int quantity();
    CubeFacesEnum face();

 private:
    int _wide;
    int _quantity;
    CubeFacesEnum _face;
};

#endif // MOVESMODEL_H