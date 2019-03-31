#ifndef SpaceShip_EXIST
#define SpaceShip_EXIST

#include "../../modules/modules.h"
#include "../ObjectConst.h"
#include "../ControlEngine.h"

class SpaceShip {

     public: 
        CoordPoint Position ; 
        SpaceShip(SDL_Renderer* &gRenderer) ;
        const int CenterPosX = ScreenWidth / 2 , 
                  CenterPosY = ScreenHeight / 2 ; 

        void Jump() ; 
        void Destroy() ; 
        void HandleEvent (SDL_Event e) ;
        void Move() ;
        void RenderSpaceShip () ; 
        void MoveTowardMouse()  ; 

    private:
        CoordVector RecentVelocity ; 
        const int MaxVel = 6 ;
        SDL_Renderer* gRenderer = NULL ; 
        SDL_Texture* SpaceShipImg = NULL ; 
        SDL_Texture* SpaceShipImgDestroy = NULL ;  
}; 

#endif