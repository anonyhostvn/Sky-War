#ifndef SpaceShip_EXIST
#define SpaceShip_EXIST

#include "../../modules/modules.h"
#include "../ObjectConst.h"
#include "../ControlEngine.h"

class SpaceShip {

     public: 
        CoordVector Velocity ;
        const int CenterPosX = (ScreenWidth - ShipWidth) / 2 , CenterPosY = (ScreenHeight - ShipHeight) / 2 ; 
        int PosX = BigMapWidth / 2, PosY = BigMapHeight / 2 , VelX = 0 , VelY = 3 ;   
        SpaceShip(SDL_Renderer* &gRenderer) ;
        void Jump() ; 
        void Destroy() ; 
        void HandleEvent (SDL_Event e) ;
        void Move() ;
        void RenderSpaceShip () ; 

    private:
        const int AccelerationX = 1  , AccelerationY = 1 , CustomVelY = -4 , CustomVelX = 0 ,  TurningRate = 2;
        SDL_Renderer* gRenderer = NULL ; 
        SDL_Texture* SpaceShipImg = NULL ; 
        SDL_Texture* SpaceShipImgDestroy = NULL ;  
}; 

#endif