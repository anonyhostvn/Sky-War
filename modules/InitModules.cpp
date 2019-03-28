#include "modules.h"

const int BigMapWidth = 3547 ; 
const int BigMapHeight = 4730 ; 
const int ScreenWidth = 1000 ; 
const int ScreenHeight = 600 ; 

bool initVideo (SDL_Window* &gMainWindow , SDL_Renderer* &gRenderer , SDL_Texture* &BigMap,  int width , int height) {

    if (SDL_Init(SDL_INIT_VIDEO) == -1) {
        printf("Init SDL_VIDEO FAILED \n") ; 
        return false ; 
    }

    if (!IMG_Init(IMG_INIT_PNG)) {
        printf("Init PNG Failed \n") ; 
        return false ; 
    }

    gMainWindow = SDL_CreateWindow("Sky War" , SDL_WINDOWPOS_UNDEFINED , SDL_WINDOWPOS_UNDEFINED , width , height , SDL_WINDOW_SHOWN) ; 

    if (gMainWindow == NULL) {
        printf("Create Window Failed \n")  ; 
        return false ; 
    }

    gRenderer = SDL_CreateRenderer(gMainWindow , -1 , SDL_RENDERER_ACCELERATED) ; 

    if (gRenderer == NULL) {
        printf("Create Renderer from Window Failed \n") ; 
        return false ; 
    }

    BigMap = loadTexture("images/Big-Map.png" , gRenderer) ; 

    return true ; 

}

void closeProgram(SDL_Window* &gMainWindow , SDL_Renderer* &gMainRenderer) {
    SDL_DestroyRenderer(gMainRenderer) ; 
    SDL_DestroyWindow(gMainWindow) ; 
}

SDL_Rect makeRect(int x , int y , int w , int h) { 
    SDL_Rect resRect ; 
    resRect.x = x ; 
    resRect.y = y ; 
    resRect.w = w ; 
    resRect.h = h ; 

    return resRect ; 
}