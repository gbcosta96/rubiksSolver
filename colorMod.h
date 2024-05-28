#ifndef COLORMOD_H
#define COLORMOD_H

#include <ostream>
#include <vector>
#include <map>

enum Code {
    BG_RED      = 41,
    BG_GREEN    = 42,
    BG_YELLOW   = 43,
    BG_BLUE     = 44,
    BG_MAGENTA  = 45,
    BG_WHITE    = 47,
    BG_DEFAULT  = 49,
};

static map<CubeFacesEnum, Code> centerColors = {
    {UP, BG_WHITE},
    {LEFT, BG_MAGENTA},
    {FRONT, BG_GREEN},
    {RIGHT, BG_RED},
    {BACK, BG_BLUE},
    {DOWN, BG_YELLOW},
};

static map<CornerPiecesEnum, vector<Code>> cornerColors = {
    {UBL, {BG_WHITE, BG_MAGENTA, BG_BLUE}},
    {UBR, {BG_WHITE, BG_BLUE, BG_RED}},
    {UFR, {BG_WHITE, BG_RED, BG_GREEN}},
    {UFL, {BG_WHITE, BG_GREEN, BG_MAGENTA}},
    {DFL, {BG_YELLOW, BG_MAGENTA, BG_GREEN}},
    {DFR, {BG_YELLOW, BG_GREEN, BG_RED}},
    {DBR, {BG_YELLOW, BG_RED, BG_BLUE}},
    {DBL, {BG_YELLOW, BG_BLUE, BG_MAGENTA}},
};

static map<EdgePiecesEnum, vector<Code>> edgeColors = {
    {UB, {BG_WHITE, BG_BLUE}},
    {UR, {BG_WHITE, BG_RED}},
    {UF, {BG_WHITE, BG_GREEN}},
    {UL, {BG_WHITE, BG_MAGENTA}},
    {FR, {BG_GREEN, BG_RED}},
    {BR, {BG_BLUE, BG_RED}},
    {FL, {BG_GREEN, BG_MAGENTA}},
    {BL, {BG_BLUE, BG_MAGENTA}},
    {DB, {BG_YELLOW, BG_BLUE}},
    {DR, {BG_YELLOW, BG_RED}},
    {DF, {BG_YELLOW, BG_GREEN}},
    {DL, {BG_YELLOW, BG_MAGENTA}},
};

class Piece {
    Code code;
public:
    Piece(CubeFacesEnum face) {
        code = centerColors[face];
    }

    Piece(pair<CornerPiecesEnum, PieceOrientation> corner, PieceOrientation position) {
        code = cornerColors[corner.first][(position + corner.second) % cornerColors[corner.first].size()];
    }

    Piece(pair<EdgePiecesEnum, PieceOrientation> edge, PieceOrientation position) {
        code = edgeColors[edge.first][(position + edge.second) % edgeColors[edge.first].size()];
    }

    Piece() : code(BG_DEFAULT) {}
    
    friend std::ostream&
    operator<<(std::ostream& os, const Piece& piece) {
        return os << "\033[49m " << "\033[" << piece.code << "m   " << "\033[49m ";
    }
};

#endif // COLORMOD_H