#ifndef PRIVATE_MODULES
#define PRIVATE_MODULES

#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <string> 
#include <algorithm>
#include <iostream> 

#include <stdlib.h> 
#include <time.h> 
#include "DataPattern/DataStructure.h"
#include "DataPattern/DataConstance.h"

//! ==================================================================================================

//! ===================================================================================================
bool initVideo (SDL_Window* &gMainWindow , SDL_Renderer* &gRenderer , SDL_Texture* &BigMap,  int width , int height) ; 

void closeProgram(SDL_Window* &gMainWindow , SDL_Renderer* &gRenderer) ; 

bool loadMedia(std :: string path , SDL_Renderer* &gMainRenderer) ; 

void renderTexture (SDL_Texture* &gTexture , SDL_Renderer* &gRenderer , int posX , int posY) ; 

SDL_Texture* loadTexture (const std :: string path , SDL_Renderer* gRenderer) ; 

SDL_Rect makeRect(int x , int y , int w , int h) ; 

#endif
