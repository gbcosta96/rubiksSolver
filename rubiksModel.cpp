#include "rubiksModel.h"
#include <bits/stdc++.h> 
#include "colorMod.h"

RubiksModel::RubiksModel() {
    solvedCube();
}

void RubiksModel::solvedCube() {
    _centers = { UP, LEFT, FRONT, RIGHT, BACK, DOWN };
    _corners = {{UBL, OK}, {UBR, OK}, {UFR, OK}, {UFL, OK},
                {DBL, OK}, {DBR, OK}, {DFR, OK}, {DFL, OK}};
    _edges = {{UB, OK}, {UR, OK}, {UF, OK}, {UL, OK},
                {FR, OK}, {BR, OK}, {FL, OK}, {BL, OK},
                {DB, OK}, {DR, OK}, {DF, OK}, {DL, OK}};
}

void RubiksModel::printVoid() {
    for (int i = 0; i < SIZE; i++) {
        cout << Piece();
    }
}

void RubiksModel::printCube() {
    cout << endl;
    printVoid();
    cout << Piece(_corners[UBL], OK) << Piece(_edges[UB], OK) << Piece(_corners[UBR], OK) << endl << endl;
    printVoid();
    cout << Piece(_edges[UL], OK) << Piece(_centers[UP]) << Piece(_edges[UR], OK) << endl << endl;
    printVoid();
    cout << Piece(_corners[UFL], OK) << Piece(_edges[UF], OK) << Piece(_corners[UFR], OK) << endl << endl;

    cout << Piece(_corners[UBL], CW) << Piece(_edges[UL], CW) << Piece(_corners[UFL], CCW);
    cout << Piece(_corners[UFL], CW) << Piece(_edges[UF], CW) << Piece(_corners[UFR], CCW);
    cout << Piece(_corners[UFR], CW) << Piece(_edges[UR], CW) << Piece(_corners[UBR], CCW);
    cout << Piece(_corners[UBR], CW) << Piece(_edges[UB], CW) << Piece(_corners[UBL], CCW) << endl << endl;

    cout << Piece(_edges[BL], CW) << Piece(_centers[LEFT]) << Piece(_edges[FL], CW);
    cout << Piece(_edges[FL], OK) << Piece(_centers[FRONT]) << Piece(_edges[FR], OK);
    cout << Piece(_edges[FR], CW) << Piece(_centers[RIGHT]) << Piece(_edges[BR], CW);
    cout << Piece(_edges[BR], OK) << Piece(_centers[BACK]) << Piece(_edges[BL], OK) << endl << endl;

    cout << Piece(_corners[DBL], CCW) << Piece(_edges[DL], CW) << Piece(_corners[DFL], CW);
    cout << Piece(_corners[DFL], CCW) << Piece(_edges[DF], CW) << Piece(_corners[DFR], CW);
    cout << Piece(_corners[DFR], CCW) << Piece(_edges[DR], CW) << Piece(_corners[DBR], CW);
    cout << Piece(_corners[DBR], CCW) << Piece(_edges[DB], CW) << Piece(_corners[DBL], CW) << endl << endl;

    printVoid();
    cout << Piece(_corners[DFL], OK) << Piece(_edges[DF], OK) << Piece(_corners[DFR], OK) << endl << endl;
    printVoid();
    cout << Piece(_edges[DL], OK) << Piece(_centers[DOWN]) << Piece(_edges[DR], OK) << endl << endl;
    printVoid();
    cout << Piece(_corners[DBL], OK) << Piece(_edges[DB], OK) << Piece(_corners[DBR], OK) << endl << endl;
}

void RubiksModel::moveCube(string moveList) {
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

void RubiksModel::rotate(MovesModel move) {
    vector<pair<CornerPiecesEnum, PieceOrientation>> cornerSwap;
    vector<vector<pair<EdgePiecesEnum, PieceOrientation>>> edgeSwaps;
    vector<CubeFacesEnum> centerSwap;

    switch (move.face()) {
        case UP:
            cornerSwap = {{UBL, OK}, {UBR, OK}, {UFR, OK}, {UFL, OK}};
            edgeSwaps.push_back({{UB, OK}, {UR, OK}, {UF, OK}, {UL, OK}});
            if (move.wide() == 2) {
                edgeSwaps.push_back({{BR, CW}, {FR, CW}, {FL, CW}, {BL, CW}});
                centerSwap = {{BACK, RIGHT, FRONT, LEFT}};
            }
            break;

        case DOWN:
            cornerSwap = {{DBL, OK}, {DFL, OK}, {DFR, OK}, {DBR, OK}};
            edgeSwaps.push_back({{DB, OK}, {DL, OK}, {DF, OK}, {DR, OK}});
            if (move.wide() == 2) {
                edgeSwaps.push_back({{BR, CW}, {BL, CW}, {FL, CW}, {FR, CW}});
                centerSwap = {{BACK, LEFT, FRONT, RIGHT}};
            }
            break;

        case RIGHT:
            cornerSwap = {{UFR, CCW}, {UBR, CW}, {DBR, CCW}, {DFR, CW}};
            edgeSwaps.push_back({{FR, OK}, {UR, OK}, {BR, OK}, {DR, OK}});
            if (move.wide() == 2) {
                edgeSwaps.push_back({{UF, CW}, {UB, CW}, {DB, CW}, {DF, CW}});
                centerSwap = {{FRONT, UP, BACK, DOWN}};
            }
            break;

        case LEFT:
            cornerSwap = {{UFL, CW}, {DFL, CCW}, {DBL, CW}, {UBL, CCW}};
            edgeSwaps.push_back({{FL, OK}, {DL, OK}, {BL, OK}, {UL, OK}});
            if (move.wide() == 2) {
                edgeSwaps.push_back({{UF, CW}, {DF, CW}, {DB, CW}, {UB, CW}});
                centerSwap = {{FRONT, DOWN, BACK, UP}};
            }
            break;

        case FRONT:
            cornerSwap = {{UFR, CW}, {DFR, CCW}, {DFL, CW}, {UFL, CCW}};
            edgeSwaps.push_back({{UF, CW}, {FR, CW}, {DF, CW}, {FL, CW}});
            if (move.wide() == 2) {
                edgeSwaps.push_back({{UR, CW}, {DR, CW}, {DL, CW}, {UL, CW}});
                centerSwap = {{UP, RIGHT, DOWN, LEFT}};
            }
            break;

        case BACK:
            cornerSwap = {{UBR, CCW}, {UBL, CW}, {DBL, CCW}, {DBR, CW}};
            edgeSwaps.push_back({{UB, CW}, {BL, CW}, {DB, CW}, {BR, CW}});
            if (move.wide() == 2) {
                edgeSwaps.push_back({{UR, CW}, {UL, CW}, {DL, CW}, {DR, CW}});
                centerSwap = {{UP, LEFT, DOWN, RIGHT}};
            }
            break;
        
        default:
            break;
    }

    for(int i = 0; i < move.quantity(); i++) {
        vector<pair<CornerPiecesEnum, PieceOrientation>> originalCorners = _corners;
        vector<pair<EdgePiecesEnum, PieceOrientation>> originalEdges = _edges;
        vector<CubeFacesEnum> originalCenters = _centers;
        for(int j = 0; j < cornerSwap.size(); j++) {
            int aux = (j + 1) % cornerSwap.size();
            _corners[cornerSwap[aux].first].first = originalCorners[cornerSwap[j].first].first;
            _corners[cornerSwap[aux].first].second = static_cast<PieceOrientation>((originalCorners[cornerSwap[j].first].second + cornerSwap[j].second) % (CCW + 1));
        }
        for(vector<pair<EdgePiecesEnum, PieceOrientation>> edgeSwap : edgeSwaps) {
            for (int j = 0; j < edgeSwap.size(); j++) {
                int aux = (j + 1) % edgeSwap.size();
                _edges[edgeSwap[aux].first].first = originalEdges[edgeSwap[j].first].first;
                _edges[edgeSwap[aux].first].second = static_cast<PieceOrientation>((originalEdges[edgeSwap[j].first].second + edgeSwap[j].second) % (CW+ 1));
            }
        }
        for(int j = 0; j < centerSwap.size(); j++) {
            int aux = (j + 1) % cornerSwap.size();
            _centers[centerSwap[aux]] = originalCenters[centerSwap[j]];
        }
    }
}

void RubiksModel::solveCube() {
    solveCross();
    printCube();
    solveCorners();
    printCube();
}

void RubiksModel::solveCross() {
    auto it = find_if(_edges.begin(), _edges.end(), [](const auto& p) { return p.first == EdgePiecesEnum::DB;});
    switch(it - _edges.begin()) {
        case EdgePiecesEnum::UB: moveCube(it->second == OK ? "B2" : "U R B'"); break;
        case EdgePiecesEnum::UR: moveCube(it->second == OK ? "U' B2" : "R B'"); break;
        case EdgePiecesEnum::UF: moveCube(it->second == OK ? "U2 B2" : "U' R B'"); break;
        case EdgePiecesEnum::UL: moveCube(it->second == OK ? "U B2" : "L' B"); break;

        case EdgePiecesEnum::FR: moveCube(it->second == OK ? "R' D" : "F D2"); break;
        case EdgePiecesEnum::BR: moveCube(it->second == OK ? "R D" : "B'"); break;
        case EdgePiecesEnum::FL: moveCube(it->second == OK ? "L D'" : "F' D2"); break;
        case EdgePiecesEnum::BL: moveCube(it->second == OK ? "L' D'" : "B"); break;

        case EdgePiecesEnum::DB: if (it->second != OK) moveCube("D R' B'"); break;
        case EdgePiecesEnum::DR: moveCube(it->second == OK ? "D" : "R' B'"); break;
        case EdgePiecesEnum::DF: moveCube(it->second == OK ? "D2" : "F' R' D"); break;
        case EdgePiecesEnum::DL: moveCube(it->second == OK ? "D'" : "L B"); break;
    }

    it = find_if(_edges.begin(), _edges.end(), [](const auto& p) { return p.first == EdgePiecesEnum::DR;});
    switch(it - _edges.begin()) {
        case EdgePiecesEnum::UB: moveCube(it->second == OK ? "U' R2" : "B' R B"); break;
        case EdgePiecesEnum::UR: moveCube(it->second == OK ? "R2" : "R' D' F D"); break;
        case EdgePiecesEnum::UF: moveCube(it->second == OK ? "U' R2" : "F R' F'"); break;
        case EdgePiecesEnum::UL: moveCube(it->second == OK ? "U2 R2" : "L D F' D'"); break;

        case EdgePiecesEnum::FR: moveCube(it->second == OK ? "R'" : "D' F D"); break;
        case EdgePiecesEnum::BR: moveCube(it->second == OK ? "R" : "D B' D'"); break;
        case EdgePiecesEnum::FL: moveCube(it->second == OK ? "F2 R'" : "D' F' D"); break;
        case EdgePiecesEnum::BL: moveCube(it->second == OK ? "D2 L' D2" : "D B D'"); break;

        case EdgePiecesEnum::DR: if (it->second != OK) moveCube("R D' F D"); break;
        case EdgePiecesEnum::DF: moveCube(it->second == OK ? "F2 U' R2" : "F' R'"); break;
        case EdgePiecesEnum::DL: moveCube(it->second == OK ? "L2 U2 R2" : "L' D' F' D"); break;
    }

    it = find_if(_edges.begin(), _edges.end(), [](const auto& p) { return p.first == EdgePiecesEnum::DF;});
    switch(it - _edges.begin()) {
        case EdgePiecesEnum::UB: moveCube(it->second == OK ? "U2 F2" : "U' L F'"); break;
        case EdgePiecesEnum::UR: moveCube(it->second == OK ? "U F2" : "R' F R"); break;
        case EdgePiecesEnum::UF: moveCube(it->second == OK ? "F2" : "U L F'"); break;
        case EdgePiecesEnum::UL: moveCube(it->second == OK ? "U' F2" : "L F'"); break;

        case EdgePiecesEnum::FR: moveCube(it->second == OK ? "D R' D'" : "F"); break;
        case EdgePiecesEnum::BR: moveCube(it->second == OK ? "D R D'" : "R2 F R2"); break;
        case EdgePiecesEnum::FL: moveCube(it->second == OK ? "D' L D" : "F'"); break;
        case EdgePiecesEnum::BL: moveCube(it->second == OK ? "D' L' D" : "L2 F'"); break;

        case EdgePiecesEnum::DF: if (it->second != OK) moveCube("F' D R' D'");break;
        case EdgePiecesEnum::DL: moveCube(it->second == OK ? "L2 U' F2" : "L' F'"); break;
    }

    it = find_if(_edges.begin(), _edges.end(), [](const auto& p) { return p.first == EdgePiecesEnum::DL;});
    switch(it - _edges.begin()) {
        case EdgePiecesEnum::UB: moveCube(it->second == OK ? "U' L2" : "B L' B'"); break;
        case EdgePiecesEnum::UR: moveCube(it->second == OK ? "U2 L2" : "U F' L F"); break;
        case EdgePiecesEnum::UF: moveCube(it->second == OK ? "U L2" : "F' L F"); break;
        case EdgePiecesEnum::UL: moveCube(it->second == OK ? "L2" : "U' F' L F"); break;

        case EdgePiecesEnum::FR: moveCube(it->second == OK ? "D2 R' D2" : "D  F D'"); break;
        case EdgePiecesEnum::BR: moveCube(it->second == OK ? "D2 R D2" : "D' B' D"); break;
        case EdgePiecesEnum::FL: moveCube(it->second == OK ? "L" : "D F' D'"); break;
        case EdgePiecesEnum::BL: moveCube(it->second == OK ? "L'" : "D' B D"); break;

        case EdgePiecesEnum::DL: if (it->second != OK) moveCube("L' D F' D'"); break;
    }
}

void RubiksModel::solveCorners() {
    // try find easy corners
    while(true) {
        auto it = find_if(_corners.begin(), _corners.begin() + 4, [](const auto& p) {
            return p.first >= DBL;
        });

        if (it - _corners.begin() <= 3) {
            pair<CornerPiecesEnum, PieceOrientation> pair = (*it);
            int auf = (pair.first - (it - _corners.begin())) % 4;
            if (auf > 0) {
                rotate(MovesModel(CubeFacesEnum::UP, auf));
            }
            switch(pair.first) {
                case DBL: {pair.second == CCW ? moveCube(SEXYRL) : pair.second == CW ? moveCube(SEXYLB) : moveCube(SEXYRL + SEXYRL + SEXYRL); break;}
                case DBR: {pair.second == CCW ? moveCube(SEXYRB) : pair.second == CW ? moveCube(SEXYLR) : moveCube(SEXYRB + SEXYRB + SEXYRB); break;}
                case DFR: {pair.second == CCW ? moveCube(SEXYRR) : pair.second == CW ? moveCube(SEXYLF) : moveCube(SEXYRR + SEXYRR + SEXYRR); break;}
                case DFL: {pair.second == CCW ? moveCube(SEXYRF) : pair.second == CW ? moveCube(SEXYLL) : moveCube(SEXYRF + SEXYRF + SEXYRF); break;}
            }
        } else {
            // try find wrong bottom corners
            int i = DBL;
            for (; i <= DFL; i++) {
                if (_corners[i].first >= DBL && ((_corners[i].second != OK) || i != _corners[i].first)) {
                    switch(i) {
                        case DBL: moveCube(SEXYRL); break;
                        case DBR: moveCube(SEXYRB); break;
                        case DFR: moveCube(SEXYRR); break;
                        case DFL: moveCube(SEXYRF); break;
                    }
                    break;
                }
            }
            if (i > DFL) break;
        }
    }
}