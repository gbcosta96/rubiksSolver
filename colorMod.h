#ifndef COLORMOD_H
#define COLORMOD_H

#include <ostream>
#include <vector>

enum Code {
    BG_RED      = 41,
    BG_GREEN    = 42,
    BG_YELLOW   = 43,
    BG_BLUE     = 44,
    BG_MAGENTA  = 45,
    BG_WHITE    = 47,
    BG_DEFAULT  = 49,
};

static const std::vector<Code> colors = { BG_WHITE, BG_MAGENTA, BG_GREEN, BG_RED, BG_BLUE, BG_YELLOW, BG_DEFAULT };

class Modifier {
    CubeFacesEnum face;
public:
    Modifier(CubeFacesEnum face) : face(face) {}
    
    friend std::ostream&
    operator<<(std::ostream& os, const Modifier& mod) {
        return os << "\033[" << colors[mod.face] << "m";
    }
};

#endif // COLORMOD_H