#include "Bullet.h"

Bullet::Bullet() {
    
}

//? ===================== Constructor ====================================================
Bullet::Bullet (SDL_Renderer* &gRenderer , SpaceShip* SpaceShipPointer , int ID) {
    srand(time(NULL)) ; 
    this->ID = ID ; 
    this->Exist = true ; 
    this->InitialTime = SDL_GetTicks() ; 

    this->gRenderer = gRenderer ;
    this->MainSpaceShip = SpaceShipPointer ; 
    this->BulletIMG = loadTexture("images/Bullet/Bullet.png" , gRenderer) ;

    int X = rand() & 1 , Y = rand() & 1 ; 
    this->Position = {X ? 0 : BigMapWidth , Y ? 0 : BigMapHeight} ; //? Random Starting Position 
    // Position = {BigMapWidth / 2 , BigMapHeight / 2} ; //? Starting Position in center of map 

    this->Speed = BulletSpeed ;
    this->PolarRecentVelocity = {Speed, 0} ; //? Recent Polar Velocity 
    this->OmegaPhi = 0 ; 
}
//?=================================================================================================

bool Bullet::operator == (const Bullet& Other) {
    return this->ID == Other.ID ; 
}

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
    CoordPoint<float> SpaceShipPosition = MainSpaceShip->GetPosition() ; 
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

    if (SDL_GetTicks() - this->InitialTime >= TimeExist) Destroy() ; 
} 

void Bullet::Render() {
    CoordPoint<float> SpaceShipPosition = MainSpaceShip->GetPosition() ; 
    CoordPoint<float> PosCam = GetRealPosOfCam(SpaceShipPosition) ; 

    if (!(Position.GetX() >= PosCam.GetX() && Position.GetX() + BulletWidth <= PosCam.GetX() + ScreenWidth
        && Position.GetY() >= PosCam.GetY() && Position.GetY() + BulletHeight <= PosCam.GetY() + ScreenHeight)) return ; 

    printf("Bullet is rendered \n") ; 

    // if (sqrt(Position.SqrDistanceTo(SpaceShipPosition)) <= (float) ShipHeight / 2 + BulletHeight / 2) return ; 
    if (this->DetectCollisionWithSpaceShip()) {
        this->Destroy() ; 
        return ; 
    }

    CoordPoint<float> RealPoint ; 
    RealPoint.SetX(Position.GetX() - BulletWidth / 2) ; 
    RealPoint.SetY(Position.GetY() - BulletHeight / 2) ; 

    SDL_Rect DesRect = makeRect(Position.GetX() - PosCam.GetX() , Position.GetY() - PosCam.GetY() , BulletWidth , BulletHeight) ; 

    float angle = PolarRecentVelocity.GetPhi() * 180 / pii ;

    SDL_RenderCopyEx(gRenderer , BulletIMG , NULL , &DesRect , angle , NULL , SDL_FLIP_NONE) ;
}

//? ============================== Status Processing =======================================
void Bullet::Destroy() {
    this->Exist = false ;
}

bool Bullet::StillAlive() {
    return this->Exist ; 
}

void Bullet::FreeMemory() {
    SDL_DestroyTexture(this->BulletIMG) ; 
    this->BulletIMG = NULL ; 
}

bool Bullet::CollisionWith (Bullet& Other) {
    CoordPoint<float> OtherPosition = Other.GetPosition() ; 
    return this->Position.SqrDistanceTo(OtherPosition) <= BulletWidth * BulletWidth / 4 ; 
}

bool Bullet::DetectCollisionWithSpaceShip() {
    bool Collision = false ; 

    CoordPoint<float> SpaceShipPosition = MainSpaceShip->GetPosition() ;  

    if (sqrt(Position.SqrDistanceTo(SpaceShipPosition)) <= (float) ShipHeight / 2 + BulletHeight / 2) Collision = true ;

    if (Collision) MainSpaceShip->Destroy() ; 
    return Collision ; 
}

//? ========================================================================================

//? ============================ Some Get and Set Function =================================
int Bullet::GetID() {
    return this->ID ; 
}

CoordPoint<float> Bullet::GetPosition () {
    return this->Position ; 
}

//? ========================================================================================
