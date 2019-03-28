#include "SpaceShip.h" 

static CoordVector Velocity ;

SpaceShip::SpaceShip(SDL_Renderer* &gRenderer) {
    Velocity.CoordY = CustomVelY ; 
    Velocity.CoordX = CustomVelX ; 
    SpaceShipImg = loadTexture("images/SpaceShip/SpaceShip.png" , gRenderer) ;
    SpaceShip::gRenderer = gRenderer ;
}

void SpaceShip::RenderSpaceShip () {
    int PosXInScreen = CenterPosX , PosYInScreen = CenterPosY ; 
    if (SpaceShip::PosX - CenterPosX < 0) PosXInScreen = SpaceShip::PosX ; 
    else if (SpaceShip::PosX + (ScreenWidth + ShipWidth) / 2 > BigMapWidth) PosXInScreen = SpaceShip::PosX - (BigMapWidth - ScreenWidth) ; 

    if (SpaceShip::PosY - CenterPosY < 0) PosYInScreen = SpaceShip::PosY ; 
    else if (SpaceShip::PosY + (ScreenHeight + ShipHeight) / 2 > BigMapHeight) PosYInScreen = SpaceShip::PosY - (BigMapHeight - ScreenHeight) ; 

    SDL_Rect DesRect = makeRect(PosXInScreen, PosYInScreen , ShipWidth , ShipHeight) ; 
    SDL_RenderCopy(SpaceShip::gRenderer , SpaceShip::SpaceShipImg , NULL , &DesRect) ;  
}

void SpaceShip::HandleEvent (SDL_Event e) {
    if (e.type == SDL_KEYDOWN) {

        switch (e.key.keysym.sym)
        {
            case SDLK_LEFT:
                Velocity = Velocity + Turning(Velocity , TurningRate , TurnLeft) ; 
                break;

            case SDLK_RIGHT:
                Velocity = Velocity + Turning(Velocity , TurningRate , TurnRight) ;

            default:
                break;
        }

    } 
}

void SpaceShip::Move () {
    // if (!(PosX + VelX < 0 || PosX + VelX + ShipWidth > BigMapWidth)) PosX += VelX ; 

    // if (!(PosY + VelY < 0 || PosY + VelY + ShipHeight > BigMapHeight)) PosY += VelY ; 

    if ((PosX + VelX < 0 || PosX + VelX + ShipWidth > BigMapWidth) 
            || (PosY + VelY < 0 || PosY + VelY + ShipHeight > BigMapHeight)) 
                VelX = -VelX , VelY = -VelY ; 

    PosX += VelX ; PosY += VelY ; 

    printf("%d - %d \n" , PosX , PosY) ; 
}