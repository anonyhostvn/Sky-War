#include "CameraMan.h"

CameraMan::CameraMan (CoordPoint<float> *SpaceShipPosition, SDL_Texture* BigMap , SDL_Renderer* gRenderer){
    CameraMan::SpaceShipPosition = SpaceShipPosition ; 
    CameraMan::BigMap = BigMap ; 
    CameraMan::gRenderer = gRenderer ; 
}

void CameraMan::RenderCamera() {

    CoordPoint<float> RealPos = GetRealPosOfCam(*SpaceShipPosition) ;
    
    SDL_Rect SrcRect = makeRect(RealPos.GetX() , RealPos.GetY() , ScreenWidth , ScreenHeight) , 
             DesRect = makeRect(0 , 0 , ScreenWidth , ScreenHeight) ; 

    SDL_RenderCopyEx (gRenderer , BigMap , &SrcRect , &DesRect , NULL , NULL , SDL_FLIP_NONE) ; 
}