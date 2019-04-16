#ifndef CAMERA_MAN_EXIST
#define CAMERA_MAN_EXIST

#include "../../modules/modules.h"
#include "../ObjectConst.h"
#include "../ControlEngine.h"

class CameraMan {
    public:
        CameraMan (CoordPoint<float> *SpaceShipPosition, SDL_Texture* BigMap , SDL_Renderer* gRenderer) ; 
        void RenderCamera () ; 

    private:
        SDL_Texture* BigMap = NULL ; 
        CoordPoint<float>* SpaceShipPosition ;   
        SDL_Renderer* gRenderer = NULL ; 
} ; 

#endif
