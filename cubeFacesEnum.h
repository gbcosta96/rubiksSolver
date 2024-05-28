#ifndef CUBEENUMS_H
#define CUBEENUMS_H

enum CubeFacesEnum {
    UP,
    LEFT,
    FRONT,
    RIGHT,
    BACK,
    DOWN,
    END,
};

enum CornerPiecesEnum {
    UBL,
    UBR,
    UFR,
    UFL,
    DFL,
    DFR,
    DBR,
    DBL,
};

enum EdgePiecesEnum {
    UB,
    UR,
    UF,
    UL,
    FR,
    BR,
    FL,
    BL,
    DB,
    DR,
    DF,
    DL,
};

enum PieceOrientation {
    OK,
    CW,
    CCW,
};

enum FaceSectorEnum {
    NORTH,
    EAST,
    SOUTH,
    WEST,
};


#endif // CUBEENUMS_H