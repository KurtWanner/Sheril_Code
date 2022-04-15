#ifndef CDSSENSOR_H
#define CDSSENSOR_H

#include "FEHIO.h"

// FEH Analog input pin with additional methods
class CdSSensor: public AnalogInputPin {
    using AnalogInputPin::AnalogInputPin;

    public:

    bool onBlueLight();
    bool onRedLight();
    bool onStartLight();

    int getLight(double value);

};

#endif