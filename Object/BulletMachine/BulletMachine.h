#ifndef BULLET_MACHINE_EXIST
#define BULLET_MACHINE_EXIST

#include <list>
#include <vector> 

#include "../../modules/modules.h"
#include "../Bullet/Bullet.h"
#include "../SpaceShip/SpaceShip.h"

class BulletMachine {
    private:
        std::list<Bullet> BulletContainer ; //! List of Bullet in Game
        // const int FrameSpaceBetweenBullet = 300 ; //? Fire Bullet Arcoding Frame 
        // int CountFrame = 0 ; //? Fire Bullet Arcording Frame
        int TimeBetweenBullet = 3500 ; //! The space of time for machine fire bullet 
        int LastTimeFire = 0 ; //! The time mark that machine last fire a bullet 
        int CountBulletFire = 0 ; //! The number of bullet the machine has fire when start game
        SDL_Renderer* gRenderer ; //! The renderer of window 

    public:
        BulletMachine (SDL_Renderer* gRenderer , SpaceShip* SpaceShip);  //! The constructor of bullet machine 
        void Processing () ; //! Processing each frame 
        void FireNewBullet() ;  //! Fire new bullet 
        void DetectCollision() ; //! Detect Collision between two bullet 
        SpaceShip* MainSpaceShip ; //! Pointer to the SpaceShip instance
} ; 

#endif