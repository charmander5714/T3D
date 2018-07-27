#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include <vector>

using namespace std;

class Game {
public:
Game();
~Game();

MarkerType getMarkerType(int layerID, int markerNumber);

void setMarkerType(int layerID, int markerNumber, MarkerType type);

Layer getLayer(int layerID);


private:

Board board;

bool gameInProgress;

bool playerTurn;

int gameResult;



};

#endif

//1234
//5678
//9101112
//13141516
