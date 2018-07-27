#include "Board.h"

Board::Board() {
        for (int i = 1; i <= 4; i++) {
                layers.push_back(Layer(i));
        }
}

Board::~Board(){
}

Layer getLayer(int layerID) {
        return layers[layerID];
}
