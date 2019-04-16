//! Lỗi khi test : Khi đạn bay qua tàu thì nó chạy hình vòng tròn

#include "Bullet.h"

Bullet::Bullet (SDL_Renderer* &gRenderer , CoordPoint<float>* SpaceShipPos) {
    srand(time(NULL)) ; 

    this->gRenderer = gRenderer ; 
    this->SpaceShipPos = SpaceShipPos ; 
    this->BulletIMG = loadTexture("images/Bullet/Bullet.png" , gRenderer) ;

    int X = rand() & 1 , Y = rand() & 1 ; 
    // Position = {X ? 0 : BigMapWidth , Y ? 0 : BigMapHeight} ;
    Position = {BigMapWidth / 2 , BigMapHeight / 2} ; 
    // RecentVelocity = {0 , Speed} ;//! RecentVelocity is for the Decartes Coordinate

    // CoordPoint<float> TargetPoint = (*SpaceShipPos) ;
    // CoordVector<float> DecartesDirection = Position.MakeVector(TargetPoint) ; 
    // PolarVector<float> PolarDirection = DecartesDirection.ConvertToPolar() ; 

    this->RecentPolarVelocity = {Speed, 0} ; //! Recent Polar Velocity 
    this->OmegaPhi = 0 ; 
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
    CoordVector<float> Direction = Position.MakeVector(*SpaceShipPos) ; 
    PolarVector<float> PolarDirection = Direction.ConvertToPolar() ;

    if (abs(PolarDirection.GetPhi() - RecentPolarVelocity.GetPhi()) <= DeltaPhi / ErrorRate) return ; 

    
}

//! Move Bullet with Velocity in Polar Coordinate 
void Bullet::Move() {
    // CoordPoint<float> TargetPoint = (*SpaceShipPos) ;
    CoordVector<float> Direction = Position.MakeVector(*SpaceShipPos) ;

    PolarVector<float> PDirection =  Direction.ConvertToPolar() ; 

    if (RecentPolarVelocity.GetPhi() + DeltaPhi < PDirection.GetPhi()) {
        if (PDirection.GetPhi() - RecentPolarVelocity.GetPhi() < pii * 2 - PDirection.GetPhi() + RecentPolarVelocity.GetPhi()) {
            RecentPolarVelocity.SetPhi(RecentPolarVelocity.GetPhi() + DeltaPhi) ; 
        } else {
            RecentPolarVelocity.SetPhi(RecentPolarVelocity.GetPhi() - DeltaPhi) ; 
        }
    } else if (PDirection.GetPhi() + DeltaPhi < RecentPolarVelocity.GetPhi()) {
        if (RecentPolarVelocity.GetPhi() - PDirection.GetPhi() < pii * 2 - RecentPolarVelocity.GetPhi() + PDirection.GetPhi()) {
            RecentPolarVelocity.SetPhi(RecentPolarVelocity.GetPhi() - DeltaPhi) ; 
        } else {
            RecentPolarVelocity.SetPhi(RecentPolarVelocity.GetPhi() + DeltaPhi) ; 
        }
    }

    CoordVector<float> RecentDecartesVelocity = RecentPolarVelocity.ConvertToCoord() ; 

    Position.SetX(Position.GetX() + RecentDecartesVelocity.GetCoordX()) ; 
    Position.SetY(Position.GetY() + RecentDecartesVelocity.GetCoordY()) ; 

    //! For Debug ==============================================================
    std::cout << "Direction Vector Of First Bull In Descartes: " ; 
    Direction.print() ;  
    std::cout << "Direction Vector Of First Bull In Polar : " ; 
    PDirection.print() ; 
    std::cout << "Recent Velocity of First Bull In Polar : " ; 
    RecentPolarVelocity.print() ; 
    std::cout << "Recent Velocity of First Bull In Descartes : " ; 
    RecentDecartesVelocity.print() ; 
    std::cout << "First Bull Position : " ; 
    Position.print() ; 

    //! For Debug ================================================================
}

void Bullet::Render() {
    CoordPoint<float> PosCam = GetRealPosOfCam(*SpaceShipPos) ; 

    if (!(Position.GetX() >= PosCam.GetX() && Position.GetX() + BulletWidth <= PosCam.GetX() + ScreenWidth
        && Position.GetY() >= PosCam.GetY() && Position.GetY() + BulletHeight <= PosCam.GetY() + ScreenHeight)) return ; 

    printf("Bullet is rendered \n") ; 

    if (sqrt(Position.SqrDistanceTo(*SpaceShipPos)) <= (float) ShipHeight / 2 + BulletHeight / 2) return ; 

    CoordPoint<float> RealPoint ; 
    RealPoint.SetX(Position.GetX() - BulletWidth / 2) ; 
    RealPoint.SetY(Position.GetY() - BulletHeight / 2) ; 

    SDL_Rect DesRect = makeRect(Position.GetX() - PosCam.GetX() , Position.GetY() - PosCam.GetY() , BulletWidth , BulletHeight) ; 

    float angle = RecentPolarVelocity.GetPhi() * 180 / pii ;

    SDL_RenderCopyEx(gRenderer , BulletIMG , NULL , &DesRect , angle , NULL , SDL_FLIP_NONE) ;
}