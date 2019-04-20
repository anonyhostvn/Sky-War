#ifndef SpaceShip_EXIST
#define SpaceShip_EXIST

#include "../../modules/modules.h"
#include "../ObjectConst.h"
#include "../ControlEngine.h"

class SpaceShip {

     public: 
        SpaceShip(SDL_Renderer* &gRenderer) ; //? Constructor of Spaceship
        const int CenterPosX = ScreenWidth / 2 ,  
                  CenterPosY = ScreenHeight / 2 ; //? Center Position when spaceship not near the end of map

        bool GetExist () ;
        CoordPoint<float> GetPosition () ; 

        void Jump() ; //TODO Spaceship will 'hack' a distance when go into a 'magic cloud' 
        void Destroy() ; //TODO Destroy the Spaceship when being touch by bullet 
        void HandleEvent (SDL_Event& e) ; //? Handle Event Input of Player 
        void Move() ; //? Moving the Spaceship or change the position of spaceship arcording the velocity
        void RenderSpaceShip () ; //? Render Spaceship to screen
        void MoveTowardMouse()  ; //? An module where spaceship go toward the user's mouse

    private:
        CoordPoint<float> Position ; //? Position of SpaceShip
        bool Exist ; //? Status of Spaceship (only Bullet can change)
        // CoordVector<float> RecentVelocity ;  //? Recent Velocity in Decartes Coordinate (not use )
        PolarVector<float> PolarRecentVelocity ;  //? Recent Velocity in Polar Coordinate
        float OmegaPhi = 0 ; //? Angle Velocity of Spaceship
        float DeltaPhi = (float) pii / 50 ; //? The change of OmegaPhi when user press turn left/right
        const float Speed = 4 ;  //? Speed of Spaceship (always = 4)
        float DeltaR = 2 ; //? The 'VRadius' will increase when user press turn left/right
        float VRadius = 0 ;  //? The Velocity of Radius (max = 2 , min = 0)
        SDL_Renderer* gRenderer = NULL ; //? Renderer of Window
        SDL_Texture* SpaceShipImg = NULL ; //? Texture of Spaceship Image 
        SDL_Texture* SpaceShipImgDestroy = NULL ;  //? Texture when Spaceship is destroying 
}; 

#endif