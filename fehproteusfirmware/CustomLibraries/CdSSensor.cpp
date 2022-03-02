#include "CdSSensor.h"
#include "Constants.h"


bool CdSSensor::onBlueLight(){
    float value = this->Value();
    return value < BlueMax && value > BlueMin;
}
bool CdSSensor::onRedLight(){
    float value = this->Value();
    return value < RedMax && value > RedMin;
}
bool CdSSensor::onStartLight(){
    float value = this->Value();
    return value < StartLightMax && value > StartLightMin;
}

int CdSSensor::getLight(double value){
    if(value < BlueMax && value > BlueMin){
        return Blue;
    } else if(value < RedMax && value > RedMin){
        return Red;
    } else {
        return None;
    }
}