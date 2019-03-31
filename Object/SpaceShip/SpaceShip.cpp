#include "SpaceShip.h" 
#include <iostream> 

SpaceShip::SpaceShip(SDL_Renderer* &gRenderer) {
    SpaceShip::Position = {BigMapWidth / 2 , BigMapHeight / 2} ; 
    SpaceShipImg = loadTexture("images/SpaceShip/SpaceShip.png" , gRenderer) ;
    SpaceShip::gRenderer = gRenderer ;
}

void SpaceShip::RenderSpaceShip () {
    CoordPoint RenderPosition = {ScreenWidth / 2 , ScreenHeight / 2} ;
    CoordPoint CamPosition = GetRealPosOfCam(SpaceShip::Position) ; 

    if (CamPosition.GetX() == 0) RenderPosition.SetX(SpaceShip::Position.GetX()) ; 
    else if (CamPosition.GetX() == BigMapWidth - ScreenWidth) RenderPosition.SetX(SpaceShip::Position.GetX() - CamPosition.GetX()) ;   

    if (CamPosition.GetY() == 0) RenderPosition.SetY(SpaceShip::Position.GetY()) ; 
    else if (CamPosition.GetY() == BigMapHeight - ScreenHeight) RenderPosition.SetY(SpaceShip::Position.GetY() - CamPosition.GetY()) ; 

    SDL_Rect DesRect = makeRect(RenderPosition.GetX() - ShipWidth / 2, RenderPosition.GetY() - ShipHeight / 2 , ShipWidth , ShipHeight) ; 

    printf("Recent Velocity in Render : ") ; RecentVelocity.print() ; 
    double angle = (RecentVelocity.SqrLeng()) ? acos(-(double) RecentVelocity.GetCoordY() / sqrt((double) RecentVelocity.SqrLeng())) : 0 ; 

    if (RecentVelocity.GetCoordX() < 0) angle = -angle ; 

    angle = angle * 180 / pii ;
    std::cout << "Angle : " << angle << std::endl ; 
    SDL_RenderCopyEx(SpaceShip::gRenderer , SpaceShip::SpaceShipImg , NULL , &DesRect , angle , NULL , SDL_FLIP_NONE) ;  
}

void SpaceShip::MoveTowardMouse() {
    int x , y ; 
    SDL_GetMouseState(&x ,&y) ; 
    CoordPoint CamPosition = GetRealPosOfCam(SpaceShip::Position) ; 

    CoordPoint Mouse = {x + CamPosition.GetX() , y + CamPosition.GetY()} ;

    printf("Mouse Pos : " ) ; Mouse.print() ; 
    printf("Camera Pos : ") ; CamPosition.print() ; 

    CoordVector DimensionVector = {Mouse.GetX() - SpaceShip::Position.GetX() , 
                                   Mouse.GetY() - SpaceShip::Position.GetY()} ;

    printf("Dimension Vector") ; DimensionVector.print() ; 

    CoordVector Veloc = {0,0} ; 

    if (DimensionVector.SqrLeng() > 0) 
        Veloc = { DimensionVector.GetCoordX() * MaxVel / sqrt(DimensionVector.SqrLeng()) 
                , DimensionVector.GetCoordY() * MaxVel / sqrt(DimensionVector.SqrLeng()) } ;

    CoordPoint NewPostion = {(double) SpaceShip::Position.GetX() + Veloc.GetCoordX()
                           , (double) SpaceShip::Position.GetY() + Veloc.GetCoordY() } ; 

    printf("Recent Postion : ") ; this->Position.print() ; 
    printf("Velocity : ") ; Veloc.print() ; 
    printf("New Position : ") ; NewPostion.print() ; 
    printf("\n" ) ; 

    SpaceShip::RecentVelocity = Veloc ; 
    SpaceShip::Position = {NewPostion.GetX() , NewPostion.GetY()} ;
}