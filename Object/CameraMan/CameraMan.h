#ifndef CAMERA_MAN_EXIST
#define CAMERA_MAN_EXIST

#include "../../modules/modules.h"
#include "../ObjectConst.h"

class CameraMan {
    public:
        CameraMan (int* SpaceShipX , int* SpaceShipY , SDL_Texture* BigMap , SDL_Renderer* gRenderer) ; 
        void RenderCamera () ; 

    private:
        SDL_Texture* BigMap = NULL ; 
        int* SpaceShipX = NULL ; 
        int* SpaceShipY = NULL ;  
        int posX = 0 ; 
        int posY = 0 ; 
        SDL_Renderer* gRenderer = NULL ; 
} ; 

#endif
