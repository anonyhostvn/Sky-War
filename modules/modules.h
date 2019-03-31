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
extern const double pii ; 
//! ==================================================================================================

struct CoordVector { 

    private:
        int CoordX , CoordY ;

    public:
        CoordVector() {

        }
        CoordVector(int x , int y) {
            this->CoordX = x ;    
            this->CoordY = y ;
        }

        int GetCoordX () {
            return this->CoordX ; 
        }

        void SetCoordX(int CoordX) {
            this->CoordX = CoordX ; 
        }

        int GetCoordY () {
            return this->CoordY ;
        }

        void SetCoordY (int CoordY) {
            this->CoordY = CoordY ; 
        }
 
        CoordVector operator + (const CoordVector &other) {
            CoordVector res ; 
            res.SetCoordX(this->CoordX + other.CoordX) ; 
            res.SetCoordY(this->CoordY + other.CoordY) ; 
            return res ; 
        }

        int operator ^ (const CoordVector &other) {
            return (CoordX * other.CoordY) - (CoordY * other.CoordX) ; 
        }

        int operator * (const CoordVector &other) {
            return CoordX * other.CoordX + CoordY * other.CoordY ; 
        }

        int SqrLeng () {
            return CoordX * CoordX + CoordY * CoordY ; 
        }

        void print() {
            printf("%d %d \n" , CoordX , CoordY) ; 
        }
} ; 

struct CoordPoint {
    private:
        int CoordX , CoordY ; 

    public:
        CoordPoint() {

        } 
        CoordPoint(int x , int y) {
            this->CoordX = x ; 
            this->CoordY = y ; 
        }

        int GetX () { return CoordX ; } 
        int GetY () {return CoordY ; } 
        void SetX (int x) {this->CoordX = x  ; } 
        void SetY (int y) {this->CoordY = y ; }
        void print () {
            printf("%d %d \n" , CoordX , CoordY) ; 
        }
} ; 

//! ===================================================================================================

bool initVideo (SDL_Window* &gMainWindow , SDL_Renderer* &gRenderer , SDL_Texture* &BigMap,  int width , int height) ; 

void closeProgram(SDL_Window* &gMainWindow , SDL_Renderer* &gRenderer) ; 

bool loadMedia(std :: string path , SDL_Renderer* &gMainRenderer) ; 

void renderTexture (SDL_Texture* &gTexture , SDL_Renderer* &gRenderer , int posX , int posY) ; 

SDL_Texture* loadTexture (const std :: string path , SDL_Renderer* gRenderer) ; 

SDL_Rect makeRect(int x , int y , int w , int h) ; 

#endif