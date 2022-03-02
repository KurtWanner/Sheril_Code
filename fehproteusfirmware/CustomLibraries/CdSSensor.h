#ifndef CDSSENSOR_H
#define CDSSENSOR_H

#include "FEHIO.h"

class CdSSensor: public AnalogInputPin {
    using AnalogInputPin::AnalogInputPin;

    public:

    bool onBlueLight();
    bool onRedLight();
    bool onStartLight();

    int getLight(double value);

};


#endif