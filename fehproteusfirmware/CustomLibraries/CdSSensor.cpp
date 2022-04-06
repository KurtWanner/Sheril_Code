#include "CdSSensor.h"
#include "Constants.h"


bool CdSSensor::onBlueLight(){
    float value = Value();
    return value < BlueMax && value > BlueMin;
}
bool CdSSensor::onRedLight(){
    float value = Value();
    return value < RedMax && value > RedMin;
}
bool CdSSensor::onStartLight(){
    float value = Value();
    return value < StartLightMax;
}

int CdSSensor::getLight(double value){
    /*if(value < BlueMax && value > BlueMin){
        return Blue;
    } else if(value < RedMax && value > RedMin){
        return Red;
    } else {
        return None;
    }*/
    if(value > BlueMin){
        return Blue;
    } else {
        return Red;
    }
}