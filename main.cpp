#include <iostream>
#include "cubeModel.h"
#include "rubiksModel.h"

using namespace std;

int main( int argc, char* argv[] ) {
   /* CubeModel cube(3);
    cube.moveCube("R Uw2");
    cube.printCube();*/

    RubiksModel rubiks;
    rubiks.moveCube("B");
    rubiks.printCube();

    return 0;
}