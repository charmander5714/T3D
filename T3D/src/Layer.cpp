#include "Layer.h"

using namespace std;

Layer::Layer() {
        for (int i = 0; i < 16; i++) {
                layerMarkers.push_back(Empty);
        }
}

Layer::Layer(int layerNumber) {
        for (int i = 0; i < 16; i++) {
                layerMarkers.push_back(Empty);
        }
        layerID = layerNumber;
}


Layer::~Layer(){
}

MarkerType Layer::getMarkerType(int markerNumber) {
        return layerMarkers[markerNumber];
}

void Layer::setMarkerType(int markerNumber, MarkerType type) {
        layerMarkers[markerNumber] = type;
}

int Layer::getLayerID() {
        return layerID;
}
