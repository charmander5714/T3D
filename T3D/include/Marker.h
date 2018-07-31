//obsoleted by MarkerType.h

#ifndef MARKER_H
#define MARKER_H

#include "MarkerType.h"


class Marker {
public:
Marker();

~Marker();

void setMarkerType(MarkerType type);

private:

MarkerType markerType;

MarkerType getMarkerType();

};

#endif
