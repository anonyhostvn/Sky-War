#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <string>
#include "modules/modules.h"
#include "Object/CameraMan/CameraMan.h" 
#include "Object/SpaceShip/SpaceShip.h"
#include <iostream> 
// #include "Object/SpaceShip/SpaceShip.h"

// const int ScreenWidth = 1000 , ScreenHeight = 1000 ;
// const int BigMapWidth = 2832 , BigMapHeight = 2000 ;  

SDL_Window* gMainWindow = NULL ; 
SDL_Renderer* gMainRenderer = NULL ; 
SDL_Texture* BigMap = NULL ;  

CoordVector MyVector(0,0) ; 

void process () {

    initVideo(gMainWindow , gMainRenderer , BigMap, ScreenWidth , ScreenHeight) ; 

    // SDL_RenderCopy(gMainRenderer , BigMap , NULL , NULL) ; 
    // SDL_RenderPresent(gMainRenderer) ;


    SpaceShip MainShip(gMainRenderer); 
    CameraMan MainCam(&MainShip.Position, BigMap , gMainRenderer) ;

    MainCam.RenderCamera() ; 
    MainShip.RenderSpaceShip() ;  

    SDL_RenderPresent(gMainRenderer) ; 
    SDL_Delay(2) ;

    bool quit = false ; 
    SDL_Event e ; 

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true ; 
            } 
        }


        printf("=========================== \n") ; 
        MainShip.MoveTowardMouse() ;
        MainCam.RenderCamera() ; 
        MainShip.RenderSpaceShip() ;
        printf("============================ \n") ; 

        // printf("%d %d \n" , x , y ) ; 
        SDL_RenderPresent(gMainRenderer) ;
        SDL_Delay(10) ; 

        // SDL_Delay(100) ; //!For Debug 

        // loadMedia("images/back-ground.bmp" , gMainRenderer) ;
    }

    closeProgram(gMainWindow , gMainRenderer) ; 

    std::cout << acos((double) 3 / 5) << std::endl << acos(-(double) 3 /5) << std::endl ; 
}

int main () {
    process() ; 

    return 0 ; 
}