#ifndef SpaceShip_EXIST
#define SpaceShip_EXIST

#include "../../modules/modules.h"
#include "../ObjectConst.h"
#include "../ControlEngine.h"

class SpaceShip {

     public: 
        CoordPoint<float> Position ; 
        SpaceShip(SDL_Renderer* &gRenderer) ;
        const int CenterPosX = ScreenWidth / 2 , 
                  CenterPosY = ScreenHeight / 2 ; 

        void Jump() ; 
        void Destroy() ; 
        void HandleEvent (SDL_Event& e) ;
        void Move() ;
        void RenderSpaceShip () ; 
        void MoveTowardMouse()  ; 

    private:
        // CoordVector<float> RecentVelocity ;  //! Recent Velocity in Decartes Coordinate (not use )
        PolarVector<float> PolarRecentVelocity ;  //! Recent Velocity in Polar Coordinate
        float OmegaPhi = 0 ; 
        float DeltaPhi = (float) pii / 50 ; 
        const float Speed = 4 ;  //! always = 4
        float DeltaR = 2 ;
        float VRadius = 0 ;  //! max = 2 , min = 0
        SDL_Renderer* gRenderer = NULL ; 
        SDL_Texture* SpaceShipImg = NULL ; 
        SDL_Texture* SpaceShipImgDestroy = NULL ;  
}; 

#endif