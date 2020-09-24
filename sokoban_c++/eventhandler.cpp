/**
* gestionnaire d'evenements
*/

#include <iostream>
#include <vector>
#include <SDL.h>

#include "interpreter.h"
#include "screenhandler.h"

using namespace std;

//game modes
bool menu_mode = true;
bool playing_mode = false;
bool editing_mode = false;
bool win_mode = false;
//identifiant de niveau
int level_id = 0;

//gerer les evenement de clavier
void handle_keyboard_event(SDL_Event *s_event, SDL_Renderer *s_renderer){
    switch(s_event->key.keysym.sym){
    case SDLK_F1:
        if(!playing_mode && menu_mode){
            playing_mode = true;
            menu_mode = false;
            editing_mode = false;
            win_mode = false;
            //call interpreter and the screenhandler
            vector< vector<int> > labyrinth = FileToLabyrinth(level_id);
            if(!labyrinth.empty())
                drawLevel(labyrinth, s_renderer);
        }
        break;
    case SDLK_F2:
        if(!editing_mode && menu_mode){
            editing_mode = true;
            playing_mode = false;
            menu_mode = false;
            win_mode = false;
            drawEditor(s_renderer);
        }
        break;
    case SDLK_F3:
        if(!menu_mode){
            menu_mode = true;
            clearVectors();
            drawMenu(s_renderer);
            playing_mode = false;
            editing_mode = false;
        }
        break;
    case SDLK_F4:
        if(win_mode && !menu_mode && !playing_mode && !editing_mode){
            win_mode = true;
            level_id+=1;
            //call interpreter and the screenhandler
            vector< vector<int> > labyrinth = FileToLabyrinth(level_id);
            if(!labyrinth.empty()){
                drawLevel(labyrinth, s_renderer);
                playing_mode = true;
                win_mode = false;
            }
            else
                level_id = 0;
        }
        break;
    case SDLK_UP:
        if(playing_mode)
            movePlayer(s_renderer, SDLK_UP);
        break;
    case SDLK_DOWN:
        if(playing_mode)
            movePlayer(s_renderer, SDLK_DOWN);
        break;
    case SDLK_LEFT:
        if(playing_mode)
            movePlayer(s_renderer, SDLK_LEFT);
        break;
    case SDLK_RIGHT:
        if(playing_mode)
            movePlayer(s_renderer, SDLK_RIGHT);
        break;

    default : break;
    }
}

//gerer les evenement de souris TODO
void handle_mouse_event(SDL_Event *s_event){
}

//gerer evenement joueur gagne
void handle_win_event(SDL_Renderer *&s_renderer){
    win_mode = true;
    menu_mode = false;
    playing_mode = false;
    editing_mode = false;
    //clear vectors
    clearVectors();
    //draw menu reussite
    drawWiningMenu(s_renderer);
}
