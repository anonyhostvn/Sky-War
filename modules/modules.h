#ifndef PRIVATE_MODULES
#define PRIVATE_MODULES

#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <string> 
#include <algorithm> 

extern const int BigMapWidth ; 
extern const int BigMapHeight ;  
extern const int ScreenWidth ; 
extern const int ScreenHeight  ;
//! ==================================================================================================
struct CoordVector  {
    int CoordX , CoordY ; 

    CoordVector() ; 
    CoordVector(int x , int y) {
        CoordX = x ;    
        CoordY = y ; 
    }

    CoordVector operator + (const CoordVector &other) {
        
    }

    int operator ^ (const CoordVector &other) {
        return (CoordX * other.CoordY) - (CoordY * other.CoordX) ; 
    }

    int operator * (const CoordVector &other) {
        return CoordX * other.CoordX + CoordY * other.CoordY ; 
    }

    void print() {
        printf("%d %d \n" , CoordX , CoordY) ; 
    }
} ; 

struct CoordPoint {
    int CoordX , CoordY ; 
} ; 

//! ===================================================================================================

bool initVideo (SDL_Window* &gMainWindow , SDL_Renderer* &gRenderer , SDL_Texture* &BigMap,  int width , int height) ; 

void closeProgram(SDL_Window* &gMainWindow , SDL_Renderer* &gRenderer) ; 

bool loadMedia(std :: string path , SDL_Renderer* &gMainRenderer) ; 

void renderTexture (SDL_Texture* &gTexture , SDL_Renderer* &gRenderer , int posX , int posY) ; 

SDL_Texture* loadTexture (const std :: string path , SDL_Renderer* gRenderer) ; 

SDL_Rect makeRect(int x , int y , int w , int h) ; 

#endif