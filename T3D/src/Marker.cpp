#include "Marker.h"

Marker::Marker() {
}

Marker::~Marker(){
}


void Marker::setMarkerType(MarkerType type) {
        markerType = type;
}

MarkerType Marker::getMarkerType() {
        return markerType;
}
