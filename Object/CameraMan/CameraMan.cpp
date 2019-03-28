#include "CameraMan.h"

CameraMan::CameraMan (int* SpaceShipX , int* SpaceShipY , SDL_Texture* BigMap , SDL_Renderer* gRenderer) {

    CameraMan::SpaceShipX = SpaceShipX ; 
    CameraMan::SpaceShipY = SpaceShipY ; 
    CameraMan::BigMap = BigMap ; 
    CameraMan::gRenderer = gRenderer ; 
}

void CameraMan::RenderCamera() {
    int SpaceShipX = (*CameraMan::SpaceShipX) , SpaceShipY = (*CameraMan::SpaceShipY) ; 
    SpaceShipX += ShipWidth / 2 ;
    SpaceShipY += ShipHeight / 2 ; 
    
    int PosCamX = 0 , PosCamY = 0 ; 

    if (SpaceShipX + ScreenWidth / 2 > BigMapWidth) PosCamX = BigMapWidth - ScreenWidth ; 
    else if (SpaceShipX - ScreenWidth / 2 < 0) PosCamX = 0 ; 
    else PosCamX =  SpaceShipX - ScreenWidth / 2 ; 

    if (SpaceShipY + ScreenHeight / 2 > BigMapHeight) PosCamY = BigMapHeight - ScreenHeight ; 
    else if (SpaceShipY - ScreenHeight / 2 < 0) PosCamY = 0 ; 
    else PosCamY  = SpaceShipY - ScreenHeight / 2 ; 

    SDL_Rect SrcRect = makeRect(PosCamX , PosCamY , ScreenWidth , ScreenHeight) , 
             DesRect = makeRect(0 , 0 , ScreenWidth , ScreenHeight) ; 

    SDL_RenderCopyEx (gRenderer , BigMap , &SrcRect , &DesRect , NULL , NULL , SDL_FLIP_NONE) ; 
}