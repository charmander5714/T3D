#include "Game.h"

using namespace std;

Game::Game() {
        board = Board();

        gameInProgress = false;

}

Game::~Game(){
}

MarkerType Game::getMarkerType(int layerID, int markerNumber) {
        return board.getLayer(layerID).getMarkerType(markerNumber);
}

void Game::setMarkerType(int layerID, int markerNumber, MarkerType type) {
        board.getLayer(layerID).setMarkerType(markerNumber, type);
}

Layer Game::getLayer(int layerID) {
        return board.getLayer(layerID);
}
