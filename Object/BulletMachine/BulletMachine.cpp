#include "BulletMachine.h"

//? ================== Constructor ==============================================================
BulletMachine::BulletMachine (ExplosionEffect* MainExplosionEffect) {
    this->RecentLevel = 3 ; 
    this->FrameBetweenBullet = FrameBetweenBulletConst / InitialBullet ; 
    this->MainExplosionEffect = MainExplosionEffect ; 
    for (int i = 0 ; i < MaxBullet ; i ++) BulletContainer[i] = NULL ; 
}

//? ================================================================================================

void BulletMachine::Processing() {
    
    //* ====================Fire Bullet Arcording Time ===========
    // unsigned int RecentTime = SDL_GetTicks() ; 
    // if (RecentTime- this->LastTimeFire >= TimeBetweenBullet) {
    //     this->FireNewBullet() ; 
    //     this->LastTimeFire = RecentTime ; 
    // }
    // //* ==========================================================

    //* ================== Fire Bullet Arcording Frame ==========

    if (!this->RecentFrame) this->FireNewBullet() ;
    this->RecentFrame ++ ; 
    if (this->RecentFrame > this->FrameBetweenBullet) this->RecentFrame = 0 ;
    //* =========================================================

    //* Increase Level
    if (this->NumberOfBulletFire >= this->Threshold) {
        RecentLevel ++ ;
        this->Threshold += this->Threshold * 2 ; 
        this->FrameBetweenBullet = (float) FrameBetweenBulletConst / RecentLevel ; 
    }

    //? =============Fire Bullet Arcording the frame =============
    // if (!this->CountFrame) this->FireNewBullet() ; 
    // this->CountFrame ++ ; 
    // this->CountFrame %= this->FrameSpaceBetweenBullet ;
    //? =========================================================

    //* ================= Detecting the Collision ===============
    this->DetectCollision() ; 
    //* =========================================================

    //? = Destroying the Bullet which is not exist or being destroy ===

    for (int i = 0 ; i < MaxBullet ; i ++) 
        if (BulletContainer[i] != NULL) {
            if (BulletContainer[i]->StillAlive()) {
                BulletContainer[i]->Move() ;
                // BulletContainer[i]->Render() ; 
            } 

            if (!BulletContainer[i]->StillAlive()) {
                MainExplosionEffect->AddNewExplosion(BulletContainer[i]->GetPosition()) ; 
                delete(BulletContainer[i]) ;
                BulletContainer[i] = NULL ; 
            }
        }

    // MainExplosionEffect->ProcessRender() ;
    //? =================================================================

    std::cout << "Recent Level : " << this->RecentLevel 
              << " ; Number bullet fire : " << this->NumberOfBulletFire 
              << " ; Recent bullet in display : " << SumOfBullet
              << " ; Frame Between Bullet : " << this->FrameBetweenBullet 
              << " ; Threshold : " <<  this->Threshold
              << "\n" ; 
}

void BulletMachine::Render() {
    for (int i = 0 ; i < MaxBullet ; i ++) if (BulletContainer[i] != NULL) {
        BulletContainer[i]->Render() ; 
    }
    MainExplosionEffect->ProcessRender() ;
}

void BulletMachine::DetectCollision() {

    for (int i = 0 ; i < MaxBullet ; i ++) if (BulletContainer[i] != NULL) 
        for (int j = 0 ; j < MaxBullet ; j ++)
            if (BulletContainer[j] != NULL && i != j && BulletContainer[i]->CollisionWith(*BulletContainer[j])) {
                BulletContainer[i]->Destroy() ;
                logIfs << "Collision with other bullet \n" ;  
                this->RecentFrame = 0 ; 
            }
}

void BulletMachine::FireNewBullet() {

    srand(time(NULL)) ; 
    int Type = rand() % 2 ;

    for (int i = 0 ; i < MaxBullet ; i ++) if (BulletContainer[i] == NULL) {
        this->NumberOfBulletFire ++ ;
        if (Type) BulletContainer[i] = new BulletT1() ; 
        else BulletContainer[i] = new BulletT0() ; 
        return ;
    }
}