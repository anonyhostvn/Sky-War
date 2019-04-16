#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <string>
#include "modules/modules.h"
#include "Object/CameraMan/CameraMan.h" 
#include "Object/SpaceShip/SpaceShip.h"
#include "Object/Bullet/Bullet.h"
#include <iostream> 
// #include "Object/SpaceShip/SpaceShip.h"

// const int ScreenWidth = 1000 , ScreenHeight = 1000 ;
// const int BigMapWidth = 2832 , BigMapHeight = 2000 ;  

SDL_Window* gMainWindow = NULL ; 
SDL_Renderer* gMainRenderer = NULL ; 
SDL_Texture* BigMap = NULL ;  

// CoordVector MyVector(0,0) ; 

void process () {

    initVideo(gMainWindow , gMainRenderer , BigMap, ScreenWidth , ScreenHeight) ; 

    // SDL_RenderCopy(gMainRenderer , BigMap , NULL , NULL) ; 
    // SDL_RenderPresent(gMainRenderer) ;


    SpaceShip MainShip(gMainRenderer); 
    CameraMan MainCam(&MainShip.Position, BigMap , gMainRenderer) ;
    Bullet FirstBull(gMainRenderer , &MainShip.Position) ; 

    MainCam.RenderCamera() ; 
    MainShip.RenderSpaceShip() ;  

    SDL_RenderPresent(gMainRenderer) ; 
    SDL_Delay(2) ;

    bool quit = false ; 
    SDL_Event e ; 

    while (!quit) {
        system("clear") ; 

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true ; 
            } 
            MainShip.HandleEvent(e) ; 
        }


        //! For Debug 
        printf("=========================== \n") ; 
        // MainShip.MoveTowardMouse() ; //! Move toward Mouse Mode 
        FirstBull.Move() ;
        MainShip.Move() ; 
        MainCam.RenderCamera() ; 
        MainShip.RenderSpaceShip() ;
        FirstBull.Render() ; 
        printf("============================ \n") ; 

        // printf("%d %d \n" , x , y ) ; 
        SDL_RenderPresent(gMainRenderer) ;
        SDL_Delay(8) ;
        //! For Debug  

        // SDL_Delay(100) ; //!For Debug 

        // loadMedia("images/back-ground.bmp" , gMainRenderer) ;
    }

    closeProgram(gMainWindow , gMainRenderer) ;  
}

int main () {
    process() ; 

    return 0 ; 
}