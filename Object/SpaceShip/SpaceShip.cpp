#include "SpaceShip.h" 
#include <iostream> 


//? ======================= Init Module =============================================|
SpaceShip::SpaceShip(SDL_Renderer* &gRenderer) {
    SpaceShip::Position = {BigMapWidth / 2 , BigMapHeight / 2} ; 
    SpaceShipImg = loadTexture("images/SpaceShip/SpaceShip.png" , gRenderer) ;
    SpaceShip::gRenderer = gRenderer ;
    // this->RecentVelocity = { 0 , -this->Speed} ; //! Init Recent Velocity in Coordinate (use with Old HandleEvent and Old Moving SpaceShip and Render Modules with Decartes Velocity)
    this->Speed = ShipSpeed ; 
    this->PolarRecentVelocity = {this->Speed , -pii / 2} ;
    this->OmegaPhi = 0 ; 
    this->Exist = true ;
}

//?==================================================================================|


//? ===================== Old Render Module ==========================================|
// void SpaceShip::RenderSpaceShip () {
//     CoordPoint<float> RenderPosition = {ScreenWidth / 2 , ScreenHeight / 2} ;
//     CoordPoint<float> CamPosition = GetRealPosOfCam(SpaceShip::Position) ; 

//     if (CamPosition.GetX() == 0) RenderPosition.SetX(SpaceShip::Position.GetX()) ; 
//     else if (CamPosition.GetX() == BigMapWidth - ScreenWidth) RenderPosition.SetX(SpaceShip::Position.GetX() - CamPosition.GetX()) ;   

//     if (CamPosition.GetY() == 0) RenderPosition.SetY(SpaceShip::Position.GetY()) ; 
//     else if (CamPosition.GetY() == BigMapHeight - ScreenHeight) RenderPosition.SetY(SpaceShip::Position.GetY() - CamPosition.GetY()) ; 

//     SDL_Rect DesRect = makeRect(RenderPosition.GetX() - ShipWidth / 2, RenderPosition.GetY() - ShipHeight / 2 , ShipWidth , ShipHeight) ; 

//     printf("Recent Velocity in Render : ") ; RecentVelocity.print() ; 
//     double angle = (RecentVelocity.SqrLeng()) ? acos(-(double) RecentVelocity.GetCoordY() / sqrt((double) RecentVelocity.SqrLeng())) : 0 ; 

//     if (RecentVelocity.GetCoordX() < 0) angle = -angle ; 

//     angle = angle * 180 / pii ;
//     std::cout << "Angle : " << angle << std::endl ; 
//     SDL_RenderCopyEx(SpaceShip::gRenderer , SpaceShip::SpaceShipImg , NULL , &DesRect , angle , NULL , SDL_FLIP_NONE) ;  
// }

//? ==================================================================================|

//? ===================== New Render Modules =========================================|


//*--------------------------> Render Module with Decartes Coordinate Velocity 
// void SpaceShip::RenderSpaceShip () {
//     CoordPoint<float> RenderPosition = {ScreenWidth / 2 , ScreenHeight / 2} ;
//     CoordPoint<float> CamPosition = GetRealPosOfCam(SpaceShip::Position) ; 

//     if (CamPosition.GetX() == 0) RenderPosition.SetX(SpaceShip::Position.GetX()) ; 
//     else if (CamPosition.GetX() == BigMapWidth - ScreenWidth) RenderPosition.SetX(SpaceShip::Position.GetX() - CamPosition.GetX()) ;   

//     if (CamPosition.GetY() == 0) RenderPosition.SetY(SpaceShip::Position.GetY()) ; 
//     else if (CamPosition.GetY() == BigMapHeight - ScreenHeight) RenderPosition.SetY(SpaceShip::Position.GetY() - CamPosition.GetY()) ; 

//     SDL_Rect DesRect = makeRect(RenderPosition.GetX() - ShipWidth / 2, RenderPosition.GetY() - ShipHeight / 2 , ShipWidth , ShipHeight) ; 

//     printf("Recent Velocity in Render : ") ; RecentVelocity.print() ; 

//     PolarVector<float> PVelocity = RecentVelocity.ConvertToPolar() ;
//     std::cout << PVelocity.GetPhi() << "\n" ; 

//     float angle = (PVelocity.GetPhi()) * 180 / pii ;
//     std::cout << "Angle : " << angle << std::endl ; 
//     SDL_RenderCopyEx(SpaceShip::gRenderer , SpaceShip::SpaceShipImg , NULL , &DesRect , angle , NULL , SDL_FLIP_NONE) ;  
// }

//* ----------------------> Render Moudle with Polar Coordinate Velocity 

void SpaceShip::RenderSpaceShip () {
    CoordPoint<float> RenderPosition = {ScreenWidth / 2 , ScreenHeight / 2} ;
    CoordPoint<float> CamPosition = GetRealPosOfCam(SpaceShip::Position) ; 

    if (CamPosition.GetX() == 0) RenderPosition.SetX(SpaceShip::Position.GetX()) ; 
    else if (CamPosition.GetX() == BigMapWidth - ScreenWidth) RenderPosition.SetX(SpaceShip::Position.GetX() - CamPosition.GetX()) ;   

    if (CamPosition.GetY() == 0) RenderPosition.SetY(SpaceShip::Position.GetY()) ; 
    else if (CamPosition.GetY() == BigMapHeight - ScreenHeight) RenderPosition.SetY(SpaceShip::Position.GetY() - CamPosition.GetY()) ; 

    SDL_Rect DesRect = makeRect(RenderPosition.GetX() - ShipWidth / 2, RenderPosition.GetY() - ShipHeight / 2 , ShipWidth , ShipHeight) ; 

    printf("Recent Velocity in Render : ") ; PolarRecentVelocity.print() ; 

    float angle = (PolarRecentVelocity.GetPhi()) * 180 / pii ;
    std::cout << "Angle : " << angle << std::endl ; 
    SDL_RenderCopyEx(SpaceShip::gRenderer , SpaceShip::SpaceShipImg , NULL , &DesRect , angle , NULL , SDL_FLIP_NONE) ;  
}

//?===================================================================================|*

//? ========================== Move Toward Mouse Version =============================|

// void SpaceShip::MoveTowardMouse() {
//     int x , y ; 
//     SDL_GetMouseState(&x ,&y) ; 
//     CoordPoint<float> CamPosition = GetRealPosOfCam(SpaceShip::Position) ; 

//     CoordPoint<float> Mouse = {(float) x + CamPosition.GetX() , (float) y + CamPosition.GetY()} ;

//     printf("Mouse Pos : " ) ; Mouse.print() ; 
//     printf("Camera Pos : ") ; CamPosition.print() ; 

//     CoordVector<float> DimensionVector = {Mouse.GetX() - SpaceShip::Position.GetX() , 
//                                    Mouse.GetY() - SpaceShip::Position.GetY()} ;

//     printf("Dimension Vector") ; DimensionVector.print() ; 

//     CoordVector<float> Veloc = {0,0} ; 

//     if (DimensionVector.SqrLeng() > 0) 
//         Veloc = { DimensionVector.GetCoordX() * MaxVel / sqrt(DimensionVector.SqrLeng()) 
//                 , DimensionVector.GetCoordY() * MaxVel / sqrt(DimensionVector.SqrLeng()) } ;

//     CoordPoint<float> NewPostion = {(float) SpaceShip::Position.GetX() + Veloc.GetCoordX()
//                            , (float) SpaceShip::Position.GetY() + Veloc.GetCoordY() } ; 

//     printf("Recent Postion : ") ; this->Position.print() ; 
//     printf("Velocity : ") ; Veloc.print() ; 
//     printf("New Position : ") ; NewPostion.print() ; 
//     printf("\n" ) ; 

//     SpaceShip::RecentVelocity = Veloc ; 
//     SpaceShip::Position = {NewPostion.GetX() , NewPostion.GetY()} ;
// }

//?===================================================================================|

//? ================================== Move With Keyboard ============================|

//* ------------------------> Old Handle Event 
// void SpaceShip::HandleEvent (SDL_Event e) {
//     PolarVector<float> PVelocity = RecentVelocity.ConvertToPolar() ; 

//     if (e.key.keysym.sym == SDLK_LEFT) {
//         PVelocity.SetPhi(PVelocity.GetPhi() - DeltaPhi) ; 
//         RecentVelocity = PVelocity.ConvertToCoord() ; 
//     } else if (e.key.keysym.sym == SDLK_RIGHT) {
//         PVelocity.SetPhi(PVelocity.GetPhi() + DeltaPhi) ; 
//         RecentVelocity = PVelocity.ConvertToCoord() ; 
//     }   
// }

//*------------------------> New Handle Event 
void SpaceShip::HandleEvent(SDL_Event& e) {

    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym)
        {
        case SDLK_LEFT:
            this->OmegaPhi -= DeltaPhi ; 
            this->VRadius += DeltaR ; 
        break;

        case SDLK_RIGHT:
            this->OmegaPhi += DeltaPhi ; 
            this->VRadius += DeltaR ; 
        break ; 
        
        default:
            break;
        }
    } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch (e.key.keysym.sym)
        {
        case SDLK_LEFT:
            this->OmegaPhi += DeltaPhi ; 
            this->VRadius -= DeltaR ; 
        break;

        case SDLK_RIGHT:
            this->OmegaPhi -= DeltaPhi ; 
            this->VRadius -= DeltaR ;  
        break ; 
        
        default:
            break;
        }
    }
}

//?===================================================================================|

//? ====================Move the SpaceShip============================================|


//* -------------------> Old Moving SpaceShip
// void SpaceShip::Move() {
//     if (this->Position.GetX() == 0 || this->Position.GetX() > BigMapWidth) 
//         RecentVelocity.SetCoordX(-RecentVelocity.GetCoordX()) ; 
//     if (this->Position.GetY() == 0 || this->Position.GetY() > BigMapHeight)
//         RecentVelocity.SetCoordY(-RecentVelocity.GetCoordY()) ; 

//     CoordPoint<float> NewPosition ; 
//     NewPosition.SetX(this->Position.GetX() + RecentVelocity.GetCoordX()) ; 
//     NewPosition.SetY(this->Position.GetY() + RecentVelocity.GetCoordY()) ; 

//     if (NewPosition.GetX() < 0) NewPosition.SetX(0) ; 
//     else if (NewPosition.GetX() > BigMapWidth) NewPosition.SetX(BigMapWidth) ; 
//     if (NewPosition.GetY() < 0) NewPosition.SetY(0) ; 
//     else if (NewPosition.GetY() > BigMapHeight) NewPosition.SetY(BigMapHeight) ; 

//     this->Position = NewPosition ; 
// }

//*--------------------> New Moving SpaceShip
void SpaceShip::Move() {
    PolarRecentVelocity.SetPhi(PolarRecentVelocity.GetPhi() + OmegaPhi) ; 
    PolarRecentVelocity.SetR(Speed + VRadius) ; 

    CoordVector<float> DecartesRecentVelocity = PolarRecentVelocity.ConvertToCoord() ; 

    Position.SetX(Position.GetX() + DecartesRecentVelocity.GetCoordX()) ; 
    Position.SetY(Position.GetY() + DecartesRecentVelocity.GetCoordY()) ; 

    if (Position.GetX() < 0 || Position.GetX() > BigMapWidth) 
        DecartesRecentVelocity.SetCoordX(-DecartesRecentVelocity.GetCoordX()) ; 
    if (Position.GetY() < 0 || Position.GetY() > BigMapHeight) 
        DecartesRecentVelocity.SetCoordY( -DecartesRecentVelocity.GetCoordY()) ; 

    PolarRecentVelocity = DecartesRecentVelocity.ConvertToPolar() ; 
}
//? ==================================================================================|


//?===================================================================================|

//? =================== Status Processing ============================================|
void SpaceShip::Destroy() {
    this->Exist = false ; 
}
//? ==================================================================================|

//? =============== Some Get and Set Function ========================================|
bool SpaceShip::GetExist() {
    return this->Exist ; 
}

CoordPoint<float> SpaceShip::GetPosition () {
    return this->Position ; 
}
//? ==================================================================================|