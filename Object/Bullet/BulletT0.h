#ifndef BULLET_T0_EXIST
#define BULLET_T0_EXIST

#include "Bullet.h"

class BulletT0 : public Bullet {
    public:
        BulletT0() {
            this->Speed = BulletSpeedT0 ;
            this->Type = 0 ;
            this->BulletHeight = BulletHeightConst[0] ; 
            this->BulletWidth = BulletWidthConst[0] ; 
            this->PolarRecentVelocity = {Speed, 0} ; //? Recent Polar Velocity 
            this->DeltaPhi = BulletDeltaPhiT0 ; 

            auto end = std::chrono::system_clock::now();
            std::time_t end_time = std::chrono::system_clock::to_time_t(end);
            logIfs << "----->>>>> Bullet Create At : " << std::ctime(&end_time) << " Have Position : " << this->Position.GetX() << "-" << this->Position.GetY() << "speed : " << this->Speed<< "\n" ;
        } 
} ; 

#endif