#include "CameraMan.h"

CameraMan::CameraMan (CoordPoint *SpaceShipPosition, SDL_Texture* BigMap , SDL_Renderer* gRenderer){
    CameraMan::SpaceShipPosition = SpaceShipPosition ; 
    CameraMan::BigMap = BigMap ; 
    CameraMan::gRenderer = gRenderer ; 
}

void CameraMan::RenderCamera() {

    CoordPoint RealPos = GetRealPosOfCam(*SpaceShipPosition) ;
    
    SDL_Rect SrcRect = makeRect(RealPos.GetX() , RealPos.GetY() , ScreenWidth , ScreenHeight) , 
             DesRect = makeRect(0 , 0 , ScreenWidth , ScreenHeight) ; 

    SDL_RenderCopyEx (gRenderer , BigMap , &SrcRect , &DesRect , NULL , NULL , SDL_FLIP_NONE) ; 
}