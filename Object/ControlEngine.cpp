#include "ControlEngine.h"

CoordVector TurningVector[16] = {{0 , -4} , {1.5,-3.7} , {2.8 , -2.8}  , {3.7 , -1.5} , {4 , 0} , 
                                        {3.7,1.5} , {2.8,2.8} , {1.5 , 3.7} , {0,4} , {-1.5,3.7} , 
                                        {-2.8,2.8} , {-3.7 , 1.5} , {-4,0} , {-3.7,-1.5} , {-2.8,-2.8} , 
                                        {-1.5,-3.7} } ; 


const int NumDirection = 16;

CoordPoint GetRealPosOfCam (CoordPoint SpaceShipPos) {
    CoordPoint res(0 , 0) ; 

    int SpaceShipX = SpaceShipPos.GetX() , 
        SpaceShipY = SpaceShipPos.GetY() ; 
    
    int PosCamX = 0 , PosCamY = 0 ; 

    if (SpaceShipX + ScreenWidth / 2  > BigMapWidth) PosCamX = BigMapWidth - ScreenWidth ; 
    else if (SpaceShipX - ScreenWidth / 2  < 0) PosCamX = 0 ; 
    else PosCamX =  SpaceShipX - ScreenWidth / 2 ;

    if (SpaceShipY + ScreenHeight / 2 > BigMapHeight) PosCamY = BigMapHeight - ScreenHeight ; 
    else if (SpaceShipY - ScreenHeight / 2 < 0) PosCamY = 0 ; 
    else PosCamY  = SpaceShipY - ScreenHeight / 2 ; 

    return {PosCamX , PosCamY} ; 
}