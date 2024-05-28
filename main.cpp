#include <iostream>
#include "cubeModel.h"

using namespace std;

int main( int argc, char* argv[] ) {
    CubeModel rubiks(3);
    rubiks.moveCube("R Uw2");
    rubiks.printCube();

    return 0;
}