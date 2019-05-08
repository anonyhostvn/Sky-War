#ifndef BULLET_T1_EXIST
#define BULLET_T1_EXIST

#include "Bullet.h"

class BulletT1 : public Bullet {
    public:
        BulletT1() {
            this->Speed = BulletSpeedT1 ;
            this->Type = 1 ; 
            this->BulletHeight = BulletHeightConst[1] ; 
            this->BulletWidth = BulletWidthConst[1] ; 
            this->PolarRecentVelocity = {Speed, 0} ; //? Recent Polar Velocity 
            this->DeltaPhi = BulletDeltaPhiT1 ; 

            auto end = std::chrono::system_clock::now();
            std::time_t end_time = std::chrono::system_clock::to_time_t(end);
            logIfs << "----->>>>> Bullet Create At : " << std::ctime(&end_time) 
                   << " Have Position : " << this->Position.GetX() << "-" << this->Position.GetY() 
                   << "speed : " << this->Speed<< "\n" ;
        }
} ; 

#endif