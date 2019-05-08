#ifndef END_GAME_EXIST
#define END_GAME_EXIST

#include "../../modules/modules.h"

static const int GoodJobPosX = 109 ; 
static const int GoodJobPosY = ScreenHeight - 494 ; 
static const int GoodJobWidth = 800 ; 
static const int GoodJobHeight = 112 ; 

static const int ToMainMenuPosX = 300 ; 
static const int ToMainMenuPosY = ScreenHeight - 260 ; 
static const int ToMainMenuWidth = 152 ; 
static const int ToMainMenuHeight = 141 ; 

static const int PlayAgainPosX = 511 ; 
static const int PlayAgainPosY = ScreenHeight - 260 ;
static const int PlayAgainWidth = 152 ; 
static const int PlayAgainHeight = 141 ; 

class EndGame {
    public:
        EndGame() {
            Selection = NotChoose ;
            GoodJobRect = makeRect(GoodJobPosX , GoodJobPosY , GoodJobWidth , GoodJobHeight) ; 
            PlayAgainRect = makeRect(PlayAgainPosX , PlayAgainPosY , PlayAgainWidth , PlayAgainHeight) ; 
            ToMainMenuRect = makeRect(ToMainMenuPosX , ToMainMenuPosY , ToMainMenuWidth , ToMainMenuHeight) ; 
        } 

        void BeginEndGame () {
            Selection = NotChoose ; 
        }

        bool IsChoose () {
            if (Selection == NotChoose) return false ;
            return true ; 
        }

        bool PlayAgain () {
            if (Selection == EnterPlayAgain) return true ; 
            return false ; 
        }

        void Process(SDL_Event &e) {            
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                int X , Y ; 
                SDL_GetMouseState(&X , &Y) ;
                if (X >= PlayAgainPosX && 
                    Y >= PlayAgainPosY && 
                    X <= PlayAgainPosX + PlayAgainWidth && 
                    Y <= PlayAgainPosY + PlayAgainHeight) {
                        Selection = EnterPlayAgain ; 
                    }

                else if (X >= ToMainMenuPosX && 
                         Y >= ToMainMenuPosY &&
                         X <= ToMainMenuPosX + ToMainMenuWidth &&
                         Y <= ToMainMenuPosY + ToMainMenuHeight) {
                             Selection = EnterToMainMenu ; 
                         }
            }
        }

        void Render () {
            SDL_RenderCopy(gMainRenderer , BigMap , NULL , NULL) ; 
            SDL_RenderCopy(gMainRenderer , GoodJobText , NULL , &GoodJobRect) ; 
            SDL_RenderCopy(gMainRenderer , PlayAgainText , NULL , &PlayAgainRect) ; 
            SDL_RenderCopy(gMainRenderer , ToMainMenuText , NULL , &ToMainMenuRect) ; 
        }

    private:
        SDL_Rect GoodJobRect , 
                 PlayAgainRect ,
                 ToMainMenuRect ; 
        
        enum {
            NotChoose,
            EnterPlayAgain,
            EnterToMainMenu
        } Selection ;
} ; 

#endif