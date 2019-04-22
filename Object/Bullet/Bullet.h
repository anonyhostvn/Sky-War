#ifndef BULLET_EXIST
#define BULLET_EXIST

#include "../../modules/modules.h"
#include "../ObjectConst.h" 
#include "../ControlEngine.h"
#include "../SpaceShip/SpaceShip.h"
#include "../MachineObject/MachineObject.h"

class Bullet : MachineObject {
    public:
        Bullet() ; 
        Bullet (SDL_Renderer* &gRenderer , SpaceShip* SpaceShipPointer , int ID) ; 

        void DetectingTarget () ; //? Detect the SpaceShip and justify the Velocity of Bullet 
        void Move () ;  //? Moving the SpaceShip (Change to Position arcording to Velocity)
        void Render() ; //? Display the Bullet (Arcording to the Position)
        void Destroy () ; //? Destroy the Bullet (Change the status or exist variable)
        bool StillAlive () ; //? Check if the bullet still alive  
        void FreeMemory() ;  //? Free the memory of texture of bullet 
        bool operator == (const Bullet& Other) ; //? define == operator 
        int GetID() ;  //? Get the ID of Bullet 
        bool CollisionWith (Bullet& Other) ;  //? Check if 'this' Bullet have collision with other  
        CoordPoint<float> GetPosition () ;  //? Get Position of Bullet
        bool DetectCollisionWithSpaceShip() ; 

    private:
        int ID ; //? Unique ID of Bullet 
        bool Exist ; //? Status of Bullet (is the Bullet Destroy ? )
        unsigned int InitialTime ; //? The Time Bullet is appear
        float DeltaPhi = pii / 80 ; //? The angle of Bullet when turning
        float ErrorRate = 10 ; //? means 0.1 or 10% 
        // float OmegaPhi ; //? The Recent Omega 
        // float Speed = 6.5 ; //? max = 9 , min = 7 
        float TimeExist = 15000 ; //? Time for bullet until self-destroy
        SDL_Texture* BulletIMG = NULL ; //? texture of bullet 
        // CoordPoint<float> Position ; //? Position of Bullet
        SpaceShip* MainSpaceShip ; //? Pointer to the instance of Spaceship 
        //// CoordVector<float> RecentVelocity ;  
        // PolarVector<float> RecentPolarVelocity ; //? Velocity of Bullet in Polar Coordinate 
        SDL_Renderer* gRenderer ; //? Renderer of Game
} ;

#endif