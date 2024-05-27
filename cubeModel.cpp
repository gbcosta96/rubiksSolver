#include "cubeModel.h"
#include "colorMod.h"

CubeModel::CubeModel(int size) :
    _size(size) {
    //getSectors();
    solvedCube();
}

int CubeModel::size() {
    return _size;
}

vector<vector<CubeFacesEnum>> CubeModel::stickers() {
    return _stickers;
}

void CubeModel::printCube() {
    
    for(int j = 0; j < _size*_size; j++) {
        if (j % _size == 0)
            for(int i = 0; i < _size; i++)
                cout << "   ";
        cout << Modifier(static_cast<CubeFacesEnum>(_stickers[CubeFacesEnum::UP][j])) << "  " << Modifier(CubeFacesEnum::END) << ' ';
        if (j % _size == _size - 1) cout << endl << endl;
    }

    for( int x = 0; x < _size; x++) {
        for (int i = CubeFacesEnum::LEFT; i <= CubeFacesEnum::BACK; i++) {
            for (int j = 0; j < _size; j++ ) {
                cout << Modifier(static_cast<CubeFacesEnum>(_stickers[i][x*_size + j])) << "  " << Modifier(CubeFacesEnum::END) << ' ';
            }
        }
        cout << endl << endl;
    }

    for(int j = 0; j < _size*_size; j++) {
        if (j % _size == 0)
            for(int i = 0; i < _size; i++)
                cout << "   ";
        cout << Modifier(static_cast<CubeFacesEnum>(_stickers[CubeFacesEnum::DOWN][j])) << "  " << Modifier(CubeFacesEnum::END) << ' ';
        if (j % _size == _size - 1) cout << endl << endl;
    }
}

void CubeModel::solvedCube() {
    _stickers = {};
    for (int i = 0; i < CubeFacesEnum::END; i++) {
        vector<CubeFacesEnum> face = {};
        for(int j = 0 ; j < _size*_size; j++) {
            face.push_back(static_cast<CubeFacesEnum>(i));
        }
        _stickers.push_back(face);
    }
}

void CubeModel::getSectors() {
    
}



