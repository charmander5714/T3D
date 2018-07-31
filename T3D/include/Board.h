#ifndef BOARD_H
#define BOARD_H

#include "Layer.h"
#include <vector>


class Board {
public:
Board();
~Board();


Layer getLayer(int layerID);


private:

vector<Layer> boardLayers;

};

#endif

//1234
//5678
//9101112
//13141516
