#include "cubeModel.h"
#include "colorMod.h"

CubeModel::CubeModel(int size) :
    _size(size) {
    getSectors();
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

/*
    Get sectors clockwise (e. g. 4x4)
    0  1  2  3
    4  5  6  7
    8  9  10 11
    12 13 14 15

    Outer sectors:
    North = [0, 1, 2, 3]
    East = [3, 7, 11, 15]
    South = [15, 14, 13, 12]
    West = [12, 8, 4, 0]

    Inner sectors:
    North = [4, 5, 6, 7]
    East = [2, 6, 10, 14]
    South = [11, 10, 9, 8]
    West = [13, 9, 5, 1]
*/
void CubeModel::getSectors() {
    vector<vector<int>> stickerPosition;
    for(int i = 0; i < _size; i++) {
        vector<int> stickers;
        for(int j = 0; j < _size; j++) {
            stickers.push_back(i*_size + j);
        }
        stickerPosition.push_back(stickers);
    }

    for(int i = 0; i < (_size + 1)/2; i++) {
        vector<int> auxEast;
        vector<int> auxWest;
        vector<int> auxSouth;
        for(int j = 0; j < _size; j++) {
            auxEast.push_back(stickerPosition[j][_size - 1 - i]);
            auxWest.push_back(stickerPosition[_size - 1 - j][i]);
            auxSouth.push_back(stickerPosition[_size - 1 - i][_size - 1 - j]);
        }
        _sectors.push_back({
            {FaceSectorEnum::NORTH, stickerPosition[i]},
            {FaceSectorEnum::EAST, auxEast},
            {FaceSectorEnum::SOUTH, auxSouth },
            {FaceSectorEnum::WEST, auxWest}
        });
    }
}

void CubeModel::moveCube(string moveList) {
    if (moveList.back() != ' ') {
        moveList.append(" ");
    }
    int pos = 0;
    string token;
    while((pos = moveList.find(' ')) != string::npos) {
        token = moveList.substr(0, pos);
        rotate(token);
        moveList.erase(0, pos + 1);
    }
}

void CubeModel::rotate(MovesModel move) {
    vector<vector<pair<CubeFacesEnum, vector<int>>>> rotations;

    for(int i = 0; i < _sectors.size(); i++) {
        //rotate face stickers
        rotations.push_back({{
            {move.face(), vector<int>(_sectors[i][FaceSectorEnum::NORTH].begin() + i, _sectors[i][FaceSectorEnum::NORTH].end() - i )},
            {move.face(), vector<int>(_sectors[i][FaceSectorEnum::EAST].begin() + i, _sectors[i][FaceSectorEnum::EAST].end() - i )},
            {move.face(), vector<int>(_sectors[i][FaceSectorEnum::SOUTH].begin() + i, _sectors[i][FaceSectorEnum::SOUTH].end() - i )},
            {move.face(), vector<int>(_sectors[i][FaceSectorEnum::WEST].begin() + i, _sectors[i][FaceSectorEnum::WEST].end() - i )}
        }});

        if (i < move.wide()) {
            switch(move.face()) {
                case CubeFacesEnum::UP:
                    rotations.push_back({{
                        {CubeFacesEnum::FRONT, _sectors[i][FaceSectorEnum::NORTH]},
                        {CubeFacesEnum::LEFT, _sectors[i][FaceSectorEnum::NORTH]},
                        {CubeFacesEnum::BACK, _sectors[i][FaceSectorEnum::NORTH]},
                        {CubeFacesEnum::RIGHT, _sectors[i][FaceSectorEnum::NORTH]},
                    }});
                break;

                case CubeFacesEnum::DOWN:
                    rotations.push_back({{
                        {CubeFacesEnum::FRONT, _sectors[i][FaceSectorEnum::SOUTH]},
                        {CubeFacesEnum::RIGHT, _sectors[i][FaceSectorEnum::SOUTH]},
                        {CubeFacesEnum::BACK, _sectors[i][FaceSectorEnum::SOUTH]},
                        {CubeFacesEnum::LEFT, _sectors[i][FaceSectorEnum::SOUTH]},
                    }});
                break;

                case CubeFacesEnum::RIGHT:
                    rotations.push_back({{
                        {CubeFacesEnum::BACK, _sectors[i][FaceSectorEnum::WEST]},
                        {CubeFacesEnum::DOWN, _sectors[i][FaceSectorEnum::EAST]},
                        {CubeFacesEnum::FRONT, _sectors[i][FaceSectorEnum::EAST]},
                        {CubeFacesEnum::UP, _sectors[i][FaceSectorEnum::EAST]},
                    }});
                break;

                case CubeFacesEnum::LEFT:
                    rotations.push_back({{
                        {CubeFacesEnum::BACK, _sectors[i][FaceSectorEnum::EAST]},
                        {CubeFacesEnum::UP, _sectors[i][FaceSectorEnum::WEST]},
                        {CubeFacesEnum::FRONT, _sectors[i][FaceSectorEnum::WEST]},
                        {CubeFacesEnum::DOWN, _sectors[i][FaceSectorEnum::WEST]},
                    }});
                break;

                case CubeFacesEnum::FRONT:
                    rotations.push_back({{
                        {CubeFacesEnum::RIGHT, _sectors[i][FaceSectorEnum::WEST]},
                        {CubeFacesEnum::DOWN, _sectors[i][FaceSectorEnum::NORTH]},
                        {CubeFacesEnum::LEFT, _sectors[i][FaceSectorEnum::EAST]},
                        {CubeFacesEnum::UP, _sectors[i][FaceSectorEnum::SOUTH]},
                    }});
                break;

                case CubeFacesEnum::BACK:
                    rotations.push_back({{
                        {CubeFacesEnum::RIGHT, _sectors[i][FaceSectorEnum::EAST]},
                        {CubeFacesEnum::UP, _sectors[i][FaceSectorEnum::NORTH]},
                        {CubeFacesEnum::LEFT, _sectors[i][FaceSectorEnum::WEST]},
                        {CubeFacesEnum::DOWN, _sectors[i][FaceSectorEnum::SOUTH]},
                    }});
                break;
            }
        }
    }

    for(vector<pair<CubeFacesEnum, vector<int>>> rotation : rotations) {
        makeRotation(move.quantity(), rotation);
    } 
}

void CubeModel::makeRotation(int repetitions, vector<pair<CubeFacesEnum, vector<int>>> moves) {
    for(int k = 0; k < repetitions; k++) {
        vector<vector<CubeFacesEnum>> originalStickers = _stickers;
        for(int i = 0; i < moves.size(); i++) {
            int aux = (i + 1) % (moves.size());
            for(int j = 0; j < moves[0].second.size(); j++) {
                _stickers[moves[aux].first][moves[aux].second[j]] = originalStickers[moves[i].first][moves[i].second[j]]; 
            }
        }
    }
}



