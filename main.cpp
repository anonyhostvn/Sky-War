#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <string>
#include "modules/modules.h"
#include "Object/CameraMan/CameraMan.h" 
#include "Object/SpaceShip/SpaceShip.h"
#include "Object/Bullet/Bullet.h"
#include "Object/BulletMachine/BulletMachine.h"
#include "Object/ExplosionEffect/ExplosionEffect.h"
#include "Object/Nature/Nature.h"
#include "Object/GUI/GUI.h"
#include <iostream> 

SDL_Window* gMainWindow = NULL ; 
SDL_Renderer* gMainRenderer = NULL ; 
SDL_Texture* BigMap = NULL ;  
bool IsLoser = false ; 
bool Pause = false ; 

CoordPoint<float>* POS_SPACESHIP = NULL ; 

void Initialize () {
    initVideo(gMainWindow , gMainRenderer , BigMap, ScreenWidth , ScreenHeight) ;
}

void Process () {

    auto end = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    logIfs << "Initialize " << std::ctime(&end_time) << "\n " ;  

    InitGame () ;

    Mix_PlayMusic(gBG_Sound , -1) ; 

    SpaceShip* MainShip = new SpaceShip; 

    Nature* GameNature = new Nature;
    ExplosionEffect* GameExplosionEffect = new ExplosionEffect ; 

    CameraMan* MainCam = new CameraMan ;
    BulletMachine* GameBulletMachine = new BulletMachine(GameExplosionEffect) ;
    GUI* GAMEGUI = new GUI() ;

    bool quit = false ; 
    SDL_Event e ; 
    int TimeDelay ; 
    unsigned int StartingFrameTime ;

    while (!quit) {
        // system("clear") ; 
        StartingFrameTime = SDL_GetTicks() ; 

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true ; 
            } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE) {
                Pause = !Pause;
            } else MainShip->HandleEvent(e) ; 
        }

        SDL_SetRenderDrawColor(gMainRenderer , 0xFF , 0xFF , 0xFF , 0xFF) ; 
        SDL_RenderClear(gMainRenderer) ; 

        //! For Debug 
        printf("=========================== \n") ; 
        MainShip->Move() ; 
        MainCam->RenderCamera() ; 
        GameNature->Process() ; 
        MainShip->RenderSpaceShip() ;
        GameBulletMachine->Processing() ; 
        GAMEGUI->Process() ; 
        printf("============================ \n") ; 

        //? _____________ Processing Loser ______________________
        if (RecentLife <= 0) {
            break ;
        }
        //? _____________________________________________________

        SDL_RenderPresent(gMainRenderer) ;

        TimeDelay = std::max((int) 15 - (int) SDL_GetTicks() + (int) StartingFrameTime , 1) ;

        SDL_Delay(TimeDelay) ;
    }


    delete(MainShip) ; 
    delete(MainCam) ; 
    delete(GameNature) ; 
    delete(GameExplosionEffect) ; 
    MainShip = NULL ; 
    MainCam = NULL ; 
    GameNature = NULL ; 
    GameExplosionEffect = NULL ; 
    Mix_HaltMusic() ; 
}

void testing () {
    int frame = 0 ;
    bool quit = false ; 
    SDL_Event e ; 

    SDL_SetRenderDrawColor(gMainRenderer , 0 , 0 , 0 , 0) ;
    SDL_RenderClear(gMainRenderer) ;
    SDL_Rect DesRect ; 
    DesRect.x = 0 ; 
    DesRect.y = 0 ; 
    DesRect.w = 100 ;  
    DesRect.h = 100 ; 

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true ; 
            }
        }

        std::cout << frame << "\n" ; 
        SDL_RenderCopy(gMainRenderer , gTrailEffect , &TrailRect[frame] , &DesRect) ;
        SDL_RenderPresent(gMainRenderer) ; 
        frame ++ ; DesRect.x += 10 ;
        if (DesRect.x >= ScreenWidth) DesRect.x = 0; 
        SDL_Delay(50) ; 
        SDL_RenderClear(gMainRenderer) ; 
        // if (frame == NumberOfTrail) {
        //     SDL_RenderClear(gMainRenderer) ; 
        //     SDL_RenderPresent(gMainRenderer) ; 
        //     SDL_Delay(2000) ; 
        // }
        if (frame >= NumberOfTrail) frame = 0 ; 
    }

    SDL_RenderClear(gMainRenderer) ; 
    SDL_RenderPresent(gMainRenderer) ; 
    SDL_Delay(1000) ;

    closeProgram(gMainWindow , gMainRenderer) ; 
}

int main () {
    Initialize() ; 
    Process() ; 

    // testing() ; 
    closeProgram(gMainWindow , gMainRenderer) ;  
    return 0 ; 
}