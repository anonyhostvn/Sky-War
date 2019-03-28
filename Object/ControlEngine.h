#ifndef ENGINECONTROL_EXIST
#define ENGINECONTROL_EXIST

#include "../modules/modules.h" 

enum Dimension {TurnLeft , TurnRight} ; 

CoordVector Turning (CoordVector A , int TurningRate , int Dimension) ; 

#endif