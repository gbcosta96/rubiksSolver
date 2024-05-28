#include <iostream>
#include "cubeModel.h"
#include "rubiksModel.h"

using namespace std;

int main( int argc, char* argv[] ) {
   /* CubeModel cube(3);
    cube.moveCube("R Uw2");
    cube.printCube();*/

    RubiksModel rubiks;
    rubiks.moveCube("D L2 U L2 U' R2 U' L' F R2 U2 L F' D2 U L' F");
    rubiks.printCube();

    rubiks.solveCube();

    return 0;
}