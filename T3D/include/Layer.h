#ifndef LAYER_H
#define LAYER_H

#include "Marker.h"
#include <vector>


using namespace std;


class Layer {
public:
Layer();
Layer(int layerNumber);
~Layer();

int getLayerID();

MarkerType getMarkerType(int markerNumber);

void setMarkerType(int markerNumber, MarkerType type);



private:

int layerID;

vector<MarkerType> layerMarkers;



};

#endif

//1234
//5678
//9101112
//13141516
