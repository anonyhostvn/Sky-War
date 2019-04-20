#ifndef CAMERA_MAN_EXIST
#define CAMERA_MAN_EXIST

#include "../../modules/modules.h"
#include "../ObjectConst.h"
#include "../ControlEngine.h"
#include "../SpaceShip/SpaceShip.h"

class CameraMan {
    public:
        CameraMan (CoordPoint<float> *SpaceShipPosition, SDL_Texture* BigMap , SDL_Renderer* gRenderer) ; 
        CameraMan (SpaceShip* SpaceShip , SDL_Texture* BigMap , SDL_Renderer* gRenderer) ;
        void RenderCamera () ; 

    private:
        SpaceShip* MainSpaceShip ; 
        SDL_Texture* BigMap = NULL ; 
        SDL_Renderer* gRenderer = NULL ; 
} ; 

#endif
