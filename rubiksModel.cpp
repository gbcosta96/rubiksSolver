#include "rubiksModel.h"
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
