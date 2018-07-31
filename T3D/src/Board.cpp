#include "Board.h"

Board::Board() {
  for (int i = 1; i <= 4; i++) {
    boardLayers.push_back(Layer(i));
  }
}

Board::~Board(){
}

Layer Board::getLayer(int layerID) {
      return boardLayers[layerID];
}
