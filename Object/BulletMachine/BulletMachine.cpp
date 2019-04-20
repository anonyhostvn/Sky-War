#include "BulletMachine.h"


//? ================== Constructor ==============================================================
BulletMachine::BulletMachine (SDL_Renderer* gRenderer , SpaceShip* SpaceShip) {
    this->MainSpaceShip= SpaceShip ;
    this->gRenderer = gRenderer ;

    //* ================ Fire the first Bullet ========================
    this->FireNewBullet() ; 
    this->LastTimeFire = SDL_GetTicks() ; 
    //* ===============================================================   
}

//? ================================================================================================

void BulletMachine::Processing() {
    
    //* ====================Fire Bullet Arcording Time ===========
    unsigned int RecentTime = SDL_GetTicks() ; 
    if (RecentTime- this->LastTimeFire >= TimeBetweenBullet) {
        this->FireNewBullet() ; 
        this->LastTimeFire = RecentTime ; 
    }
    //* ==========================================================

    //? =============Fire Bullet Arcording the frame =============
    // if (!this->CountFrame) this->FireNewBullet() ; 
    // this->CountFrame ++ ; 
    // this->CountFrame %= this->FrameSpaceBetweenBullet ;
    //? =========================================================

    //* ================= Detecting the Collision ===============
    this->DetectCollision() ; 
    //* =========================================================

    //? = Destroying the Bullet which is not exist or being destroy ===
    std::vector<Bullet> DestroyingBullet ; 
    DestroyingBullet.clear() ; 

    for (Bullet &tmp : BulletContainer)
        if (tmp.StillAlive()) {
            tmp.Move() ; 
            tmp.Render() ; 
        }
        else {
            DestroyingBullet.push_back(tmp) ; 
            tmp.FreeMemory() ;
        }

    while (DestroyingBullet.size()) {
        BulletContainer.remove(DestroyingBullet.back()) ; 
        DestroyingBullet.pop_back() ; 
    }
    //? =================================================================


    //? If all Bullet die, fire a new bullet immediately
    if (BulletContainer.size() == 0) this->FireNewBullet() ; 

    //! For Debug
    printf("The Number of Bullet : %d \n" , this->BulletContainer.size()) ; 
}

void BulletMachine::FireNewBullet() {
    CountBulletFire ++ ; 
    // Bullet NewBullet(gRenderer , SpaceShipPosition , CountBulletFire) ;
    Bullet NewBullet(gRenderer , MainSpaceShip , CountBulletFire) ;
    this->BulletContainer.push_back(NewBullet) ;
}

void BulletMachine::DetectCollision() {
    for (Bullet &RecentBullet : BulletContainer) {
        for (Bullet OtherBullet : BulletContainer) if (! (RecentBullet == OtherBullet)) {
            if (RecentBullet.CollisionWith(OtherBullet)) {
                RecentBullet.Destroy() ; 
            } 
        }
    }
}
