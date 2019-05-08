#ifndef BULLET_MACHINE_EXIST
#define BULLET_MACHINE_EXIST

#include <list>
#include <vector> 

#include "../../modules/modules.h"
#include "../Bullet/AllBullet.h"
#include "../SpaceShip/SpaceShip.h"

static const int MaxLevel = 10 ;
static const int BulletEachLevel = 3 ;
static const int MaxBullet = MaxLevel ;
static const int InitialBullet = 3 ; 
static const int FrameBetweenBulletConst = 1200  ;  

class BulletMachine {
    protected:
        int RecentLevel = InitialBullet ; 
        int NumberOfBulletFire = 0 ;
        int Threshold = InitialBullet ; 
        // std::list<Bullet> BulletContainer ; //! List of Bullet in Game
        Bullet* BulletContainer[MaxBullet] ; //? All Bullet in game
        // const int FrameSpaceBetweenBullet = 300 ; //? Fire Bullet Arcoding Frame 
        int RecentFrame = 0 ; //? Fire Bullet Arcording Frame
        // int TimeBetweenBullet = 3500 ; //! The space of time for machine fire bullet 
        // int LastTimeFire = 0 ; //! The time mark that machine last fire a bullet 
        int FrameBetweenBullet ; 
        int CountBulletFire = 0 ; //! The number of bullet the machine has fire when start game
        ExplosionEffect* MainExplosionEffect ;

    public:
        BulletMachine (ExplosionEffect* MainExplosionEffect);  //! The constructor of bullet machine 
        void Processing () ; //! Processing each frame 
        void FireNewBullet() ;  //! Fire new bullet 
        void DetectCollision() ; //! Detect Collision between two bullet 
        void Render() ; //? Render object 
} ; 

#endif