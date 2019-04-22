#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <string>
#include "modules/modules.h"
#include "Object/CameraMan/CameraMan.h" 
#include "Object/SpaceShip/SpaceShip.h"
#include "Object/Bullet/Bullet.h"
#include "Object/BulletMachine/BulletMachine.h"
#include <iostream> 

SDL_Window* gMainWindow = NULL ; 
SDL_Renderer* gMainRenderer = NULL ; 
SDL_Texture* BigMap = NULL ;  

void process () {

    initVideo(gMainWindow , gMainRenderer , BigMap, ScreenWidth , ScreenHeight) ; 


    SpaceShip MainShip(gMainRenderer); 
    CameraMan MainCam(&MainShip, BigMap , gMainRenderer) ;
    BulletMachine GameBulletMachine(gMainRenderer , &MainShip) ;

    bool quit = false ; 
    SDL_Event e ; 
    int TimeDelay ; 
    unsigned int StartingFrameTime ; 

    while (!quit) {
        system("clear") ; 

        StartingFrameTime = SDL_GetTicks() ; 

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true ; 
            } 
            MainShip.HandleEvent(e) ; 
        }


        //! For Debug 
        printf("=========================== \n") ; 
        // MainShip.MoveTowardMouse() ; //! Move toward Mouse Mode 
        MainShip.Move() ; 
        MainCam.RenderCamera() ; 
        MainShip.RenderSpaceShip() ;
        GameBulletMachine.Processing() ; 
        printf("============================ \n") ; 

        //? _____________ Processing Loser ______________________
        if (!MainShip.GetExist()) {
            break ; 
        }
        //? _____________________________________________________

        SDL_RenderClear(gMainRenderer) ; 
        // printf("%d %d \n" , x , y ) ; 
        SDL_RenderPresent(gMainRenderer) ;

        TimeDelay = std::max((int) 8 - (int) SDL_GetTicks() + (int) StartingFrameTime , 1) ;

        SDL_Delay(TimeDelay) ;
    }

    closeProgram(gMainWindow , gMainRenderer) ;  
}

int main () {
    process() ; 

    return 0 ; 
}