#ifndef BULLET_EXIST
#define BULLET_EXIST

#include "../../modules/modules.h"
#include "../ObjectConst.h" 
#include "../ControlEngine.h"

class Bullet {
    public:
        Bullet (SDL_Renderer* &gRenderer , CoordPoint<float>* SpaceShipPos) ;
        void DetectingTarget () ; 
        void Move () ; 
        void Render() ; 

    private:
        float DeltaPhi = pii / 80 ; 
        float ErrorRate = 10 ; //! means 0.1 or 10% 
        float OmegaPhi ; 
        float Speed = 7 ; //! max = 9 , min = 7 
        SDL_Texture* BulletIMG = NULL ; 
        CoordPoint<float> Position ; 
        CoordPoint<float>* SpaceShipPos ; 
        // CoordVector<float> RecentVelocity ; 
        PolarVector<float> RecentPolarVelocity ; 
        SDL_Renderer* gRenderer ; 
} ;

#endif