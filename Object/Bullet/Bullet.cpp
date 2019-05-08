#include "Bullet.h"

//? ===================== Constructor ====================================================
Bullet::Bullet () {
    SumOfBullet ++ ;

    srand(time(NULL)) ; 
    this->Exist = true ;
    // this->InitialTime = SDL_GetTicks() ; 

    // this->BulletIMG = loadTexture("images/Effect/Trail-Effect.png" , gRenderer) ;

    float RandPhi = (float) (rand() % 618) / 10 ;
    PolarVector<float> RandomVector(1.5 * ScreenWidth , RandPhi) ;
    CoordVector<float> RandomVtr = RandomVector.ConvertToCoord() ;
    int X = POS_SPACESHIP->GetX() + RandomVtr.GetCoordX() , Y = POS_SPACESHIP->GetY() + RandomVtr.GetCoordY() ; 
    this->Position = {X , Y } ; //? Random Starting Position 

    this->OmegaPhi = 0 ;

    // TrailEffect temp {gRenderer , 5 , 300 , BulletWidth , BulletHeight} ; 
    float Angle = this->PolarRecentVelocity.GetPhi() ; 
    this->BulletTrailEffect = new TrailEffect(this->Position , Angle) ;
}
//?=================================================================================================

// void Bullet::Move() {
//     CoordPoint<float> TargetPoint = (*SpaceShipPos) ; 
//     CoordVector<float> Direction = Position.MakeVector(TargetPoint) ;

//     float k = (float) Speed / sqrt(Direction.SqrLeng()) ; 
//     CoordVector<float> Velocity = Direction * k ;

//     Position.SetX(Position.GetX() + Velocity.GetCoordX()) ; 
//     Position.SetY(Position.GetY() + Velocity.GetCoordY()) ; 

//     //! For debug 
//     printf("First Bull Position : " ) ; 
//     Position.print() ; 
//     //!=================
// }

//! Move Bullet with Velocity is in Decartes Coordinate
// void Bullet::Move() {
//     CoordPoint<float> TargetPoint = (*SpaceShipPos) ;
//     CoordVector<float> Direction = Position.MakeVector(TargetPoint) ;


//     PolarVector<float> PDirection , PVelocity ; 
//     PDirection = Direction.ConvertToPolar() ; 
//     PVelocity = RecentVelocity.ConvertToPolar() ; 

//     if (PVelocity.GetPhi() + DeltaPhi < PDirection.GetPhi()) {
//         if (PDirection.GetPhi() - PVelocity.GetPhi() < pii * 2 - PDirection.GetPhi() + PVelocity.GetPhi()) {
//             PVelocity.SetPhi(PVelocity.GetPhi() + DeltaPhi) ; 
//         } else {
//             PVelocity.SetPhi(PVelocity.GetPhi() - DeltaPhi) ; 
//         }
//     } else if (PDirection.GetPhi() + DeltaPhi < PVelocity.GetPhi()) {
//         if (PVelocity.GetPhi() - PDirection.GetPhi() < pii * 2 - PVelocity.GetPhi() + PDirection.GetPhi()) {
//             PVelocity.SetPhi(PVelocity.GetPhi() - DeltaPhi) ; 
//         } else {
//             PVelocity.SetPhi(PVelocity.GetPhi() + DeltaPhi) ; 
//         }
//     }

//     // PVelocity.SetPhi(PVelocity.GetPhi() - pii / 300) ; 


//     RecentVelocity = PVelocity.ConvertToCoord() ; 

//     Position.SetX(Position.GetX() + RecentVelocity.GetCoordX()) ; 
//     Position.SetY(Position.GetY() + RecentVelocity.GetCoordY()) ; 

//     // For Debug ==============================================================
//     std::cout << "Direction Vector Of First Bull In Descartes: " ; 
//     Direction.print() ;  
//     std::cout << "Direction Vector Of First Bull In Polar : " ; 
//     PDirection.print() ; 
//     std::cout << "Recent Velocity of First Bull In Polar : " ; 
//     PVelocity.print() ; 
//     std::cout << "Recent Velocity of First Bull In Descartes : " ; 
//     RecentVelocity.print() ; 
//     std::cout << "First Bull Position : " ; 
//     Position.print() ; 

//     // For Debug ================================================================
// }

//! Detecting Target and justify the Velocity 
void Bullet::DetectingTarget () { 
    CoordPoint<float> SpaceShipPosition = *POS_SPACESHIP ; 
    CoordVector<float> Direction = Position.MakeVector(SpaceShipPosition) ; 
    PolarVector<float> PDirection = Direction.ConvertToPolar() ;

    if (abs(PDirection.GetPhi() - PolarRecentVelocity.GetPhi()) <= DeltaPhi / ErrorRate) return ; 

    if (PolarRecentVelocity.GetPhi() + DeltaPhi < PDirection.GetPhi()) {
        if (PDirection.GetPhi() - PolarRecentVelocity.GetPhi() < pii * 2 - PDirection.GetPhi() + PolarRecentVelocity.GetPhi()) {
            PolarRecentVelocity.SetPhi(PolarRecentVelocity.GetPhi() + DeltaPhi) ; 
        } else {
            PolarRecentVelocity.SetPhi(PolarRecentVelocity.GetPhi() - DeltaPhi) ; 
        }
    } else if (PDirection.GetPhi() + DeltaPhi < PolarRecentVelocity.GetPhi()) {
        if (PolarRecentVelocity.GetPhi() - PDirection.GetPhi() < pii * 2 - PolarRecentVelocity.GetPhi() + PDirection.GetPhi()) {
            PolarRecentVelocity.SetPhi(PolarRecentVelocity.GetPhi() - DeltaPhi) ; 
        } else {
            PolarRecentVelocity.SetPhi(PolarRecentVelocity.GetPhi() + DeltaPhi) ; 
        }
    }
    

    //! For Debug 
    std::cout << "Direction Vector Of First Bull In Descartes: " ; 
    Direction.print() ;  
    std::cout << "Direction Vector Of First Bull In Polar : " ; 
    PDirection.print() ; 
}

//! Move Bullet with Velocity in Polar Coordinate 
void Bullet::Move() {
    if (Pause) return ; 

    this->DetectingTarget() ; 


    CoordVector<float> RecentDecartesVelocity = PolarRecentVelocity.ConvertToCoord() ; 

    Position.SetX(Position.GetX() + RecentDecartesVelocity.GetCoordX()) ; 
    Position.SetY(Position.GetY() + RecentDecartesVelocity.GetCoordY()) ; 

    //! For Debug ==============================================================
 
    std::cout << "Recent Velocity of First Bull In Polar : " ; 
    PolarRecentVelocity.print() ; 
    std::cout << "Recent Velocity of First Bull In Descartes : " ; 
    RecentDecartesVelocity.print() ; 
    std::cout << "First Bull Position : " ; 
    Position.print() ; 

    //! For Debug ================================================================
    this->RecentFrame ++ ;  
    if (this->RecentFrame >= this->FrameExist) {
    logIfs << "Destroy because end of frame " << this->RecentFrame << FrameExist << "\n" ; 
        Destroy() ;
    }
} 

void Bullet::Render() {
    CoordPoint<float> PosCam = GetRealPosOfCam() ; 

    float Phi = PolarRecentVelocity.GetPhi() ; 
    BulletTrailEffect->Process(this->Position , Phi) ;

    if (!(Position.GetX() >= PosCam.GetX() && Position.GetX() + BulletWidth <= PosCam.GetX() + ScreenWidth
        && Position.GetY() >= PosCam.GetY() && Position.GetY() + BulletHeight <= PosCam.GetY() + ScreenHeight)) return ; 

    printf("Bullet is rendering \n") ; 

    //// if (sqrt(Position.SqrDistanceTo(SpaceShipPosition)) <= (float) ShipHeight / 2 + BulletHeight / 2) return ; 

    if (this->DetectCollisionWithSpaceShip()) {
        this->Destroy() ; 
        RecentLife -= DamageBullet[this->Type] ;
        return ; 
    }

    CoordPoint<float> RealPoint ; 
    // RealPoint.SetX(Position.GetX() - BulletWidth / 2) ; 
    // RealPoint.SetY(Position.GetY() - BulletHeight / 2) ;
    RealPoint.SetX(Position.GetX() - PosCam.GetX()) ; 
    RealPoint.SetY(Position.GetY() - PosCam.GetY()) ;

    SDL_Rect DesRect = makeRect(Position.GetX() - PosCam.GetX() , Position.GetY() - PosCam.GetY() , BulletWidth , BulletHeight) ; 

    float angle = PolarRecentVelocity.GetPhi() * 180 / pii ;

    // SDL_RenderCopyEx(gMainRenderer , gBulletTextureType1 , NULL , &DesRect , angle , NULL , SDL_FLIP_NONE) ;
    SDL_RenderCopyEx(gMainRenderer , gBulletTexture[this->Type] , NULL , &DesRect , angle , NULL , SDL_FLIP_NONE) ;   
}

//? ============================== Status Processing =======================================
void Bullet::Destroy() {
    SumOfBullet -- ; 

    RecentScore += ScoreBullet[this->Type] ;
    this->Exist = false ;
}

bool Bullet::StillAlive() {
    return this->Exist ; 
}

void Bullet::FreeMemory() {
    (*BulletTrailEffect).FreeMemory() ;
}

bool Bullet::CollisionWith (Bullet& Other) {
    CoordPoint<float> OtherPosition = Other.GetPosition() ; 
    return this->Position.SqrDistanceTo(OtherPosition) <= BulletWidth * BulletWidth / 4 ; 
}

bool Bullet::DetectCollisionWithSpaceShip() {
    bool Collision = false ; 

    CoordPoint<float> SpaceShipPosition = *POS_SPACESHIP ;  

    if (sqrt(Position.SqrDistanceTo(SpaceShipPosition)) <= (float) ShipHeight / 2 + BulletHeight / 2) Collision = true ;

    if (Collision) logIfs << "Collision spaceship " 
                          << " == Velocity of bullet " << this->PolarRecentVelocity.GetR() << "--" << this->PolarRecentVelocity.GetPhi() 
                          << " Position of bullet " << this->Position.GetX() << " -- " << this->Position.GetY() 
                          << "\n" ; 

    return Collision ; 
}

//? ========================================================================================

//? ============================ Some Get and Set Function =================================

CoordPoint<float> Bullet::GetPosition () {
    return this->Position ; 
}

int Bullet::GetType() {
    return this->Type ; 
}

//? ========================================================================================
