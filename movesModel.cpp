#include "movesModel.h"

MovesModel::MovesModel(CubeFacesEnum face, int quantity, int wide) : 
    _face( face ),
    _quantity(quantity),
    _wide(wide) {
}

MovesModel::MovesModel(std::string str) :
    _quantity(1),
    _wide(1) {
    if(str[0] == 'F') {
        _face = CubeFacesEnum::FRONT;
    } else if(str[0] == 'B') {
        _face = CubeFacesEnum::BACK;
    } else if(str[0] == 'L') {
        _face = CubeFacesEnum::LEFT;
    } else if(str[0] == 'R') {
        _face = CubeFacesEnum::RIGHT;
    } else if(str[0] == 'U') {
        _face = CubeFacesEnum::UP;
    } else if(str[0] == 'D') {
        _face = CubeFacesEnum::DOWN;
    }

    if(str.back() == '\'') {
        _quantity = 3;
    } else if(str.back() == '2') {
        _quantity = 2;
    }

    if(str.find("w") != std::string::npos) {
        if (str[0] >= '1' && str[0] <= '9') {
            _wide = str[0] - '0';
        } else {
            _wide = 2;
        }
    }
}

int MovesModel::wide() {
    return _wide;
}

int MovesModel::quantity() {
    return _quantity;
}

CubeFacesEnum MovesModel::face() {
    return _face;
}

