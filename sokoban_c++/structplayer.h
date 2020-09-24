/**
* structure de sprite joueur
*/

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

#include "structbox.h"


using namespace std;

//screen dimension
const int W = 480;
const int H = 480;

//player dimension
const int player_w = 40;
const int player_h = 40;



struct Player
{
    SDL_Rect player_rect;
    SDL_Surface *spirite;

    Player(int x, int y)
    {
        spirite = IMG_Load("images/joueur.jpg");
        player_rect.x = x;
        player_rect.y = y;
        player_rect.w = player_w;
        player_rect.h = player_h;
    }

    //deplacer le joueur
    void movePlayer(int direction, vector< vector<int> > &labyrinth, vector<Box*> &v_box, vector<SDL_Rect> &v_boxok){
        int i = 0;
        int j = 0;

        switch(direction){
        case SDLK_UP:
            i = (player_rect.y-player_h)/player_h;
            j = player_rect.x/player_w;

            if((player_rect.y-player_h) >= 0 && labyrinth[i][j] != 1){
                if(labyrinth[i][j] == 2){
                    Box *box = NULL;
                    for(Box *b: v_box){
                        if(b->containCoord(player_rect.x, (player_rect.y-player_h))){
                            box = b;
                            break;
                        }
                    }
                    if (box != NULL){
                        if( box->moveBox(SDLK_UP, labyrinth, v_box, v_boxok) ){
                            player_rect.y-=player_h;
                        }
                    }
                    else
                        cout<<"Failed to find Box on specified position "<<endl;
                }
                else
                    player_rect.y-=player_h;
            }
            break;

        case SDLK_DOWN:
            i = (player_rect.y+player_h)/player_h;
            j = player_rect.x/player_w;

            if((player_rect.y+player_h) <= H-player_h  && labyrinth[i][j] != 1){
                if(labyrinth[i][j] == 2){
                    Box *box = NULL;
                    for(Box *b: v_box){
                        if(b->containCoord(player_rect.x, (player_rect.y+player_h))){
                            box = b;
                            break;
                        }
                    }
                    if (box != NULL){
                        if( box->moveBox(SDLK_DOWN, labyrinth, v_box, v_boxok) ){
                            player_rect.y+=player_h;
                        }
                    }
                    else
                        cout<<"Failed to find Box on specified position "<<endl;
                }
                else
                    player_rect.y+=player_h;
            }


            break;
        case SDLK_LEFT:
            i = (player_rect.y)/player_h;
            j = (player_rect.x-player_w)/player_w;

            if((player_rect.x-player_w) >= 0  && labyrinth[i][j] != 1){
                if(labyrinth[i][j] == 2){
                    Box *box = NULL;
                    for(Box *b: v_box){
                        if(b->containCoord( (player_rect.x-player_w), player_rect.y)){
                            box = b;
                            break;
                        }
                    }
                    if (box != NULL){
                        if( box->moveBox(SDLK_LEFT, labyrinth, v_box, v_boxok) ){
                            player_rect.x-=player_w;
                        }
                    }
                    else
                        cout<<"Failed to find Box on specified position "<<endl;
                }
                else
                    player_rect.x-=player_w;
            }

            break;
        case SDLK_RIGHT:
            i = (player_rect.y)/player_h;
            j = (player_rect.x+player_w)/player_w;

            if((player_rect.x+player_w) <= W-player_w  && labyrinth[i][j] != 1){
                if(labyrinth[i][j] == 2){
                    Box *box = NULL;
                    for(Box *b: v_box){
                        if(b->containCoord( (player_rect.x+player_w), player_rect.y)){
                            box = b;
                            break;
                        }
                    }
                    if (box != NULL){
                        if( box->moveBox(SDLK_RIGHT, labyrinth, v_box, v_boxok) ){
                            player_rect.x+=player_w;

                        }
                    }
                    else
                        cout<<"Failed to find Box on specified position "<<endl;
                }
                else
                    player_rect.x+=player_w;
            }
            break;
        default: break;
        }

    }

    //dessiner le joueur
    void drawPlayer(SDL_Renderer *&s_renderer){
        SDL_Texture *s_texture = NULL;
        s_texture = SDL_CreateTextureFromSurface(s_renderer, spirite);

        if(s_texture != NULL){
            SDL_RenderCopy(s_renderer, s_texture, NULL, &player_rect);

            SDL_DestroyTexture(s_texture);
            s_texture = NULL;
        }
        else{
            cout<<"Failed to load player spirite"<<endl;
        }
    }

    //mettre a jour la position
    void setPos(int x, int y){
        player_rect.x = x;
        player_rect.y = y;
    }

    //deallocation
    void clearPlayer(){
        SDL_FreeSurface(spirite);
        spirite = NULL;
    }
};

