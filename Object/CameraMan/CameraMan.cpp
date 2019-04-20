#include "CameraMan.h"
CameraMan::CameraMan (SpaceShip* SpaceShip , SDL_Texture* BigMap , SDL_Renderer* gRenderer) {
    CameraMan::MainSpaceShip = SpaceShip ; 
    CameraMan::BigMap = BigMap ; 
    CameraMan::gRenderer = gRenderer ; 
}

void CameraMan::RenderCamera() {

    CoordPoint<float> SpaceShipPosition = MainSpaceShip->GetPosition() ; 
    CoordPoint<float> RealPos = GetRealPosOfCam(SpaceShipPosition) ;
    
    SDL_Rect SrcRect = makeRect(RealPos.GetX() , RealPos.GetY() , ScreenWidth , ScreenHeight) , 
             DesRect = makeRect(0 , 0 , ScreenWidth , ScreenHeight) ; 

    SDL_RenderCopyEx (gRenderer , BigMap , &SrcRect , &DesRect , NULL , NULL , SDL_FLIP_NONE) ; 
}