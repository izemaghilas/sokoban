/**
* strucure de la sprite caisse
*/

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

using namespace std;

//box dimension
const int box_w = 40;
const int box_h = 40;

//screen dimension
const int box_H = 480;
const int box_W = 480;

struct Box
{
    SDL_Rect box_rect;
    SDL_Surface *spirite;
    Box(int x, int y)
    {
        spirite = IMG_Load("images/caisse.jpg");
        box_rect.x = x;
        box_rect.y = y;
        box_rect.w = box_w;
        box_rect.h = box_h;
    }
    //dessiner la caisse
    void drawBox(SDL_Renderer *&s_renderer){
        SDL_Texture *s_texture = NULL;
        s_texture = SDL_CreateTextureFromSurface(s_renderer, spirite);

        if(s_texture != NULL){
            SDL_RenderCopy(s_renderer, s_texture, NULL, &box_rect);

            SDL_DestroyTexture(s_texture);
            s_texture = NULL;
        }
        else{
            cout<<"Failed to load player spirite"<<endl;
        }
    }
    bool moveBox(int direction, vector< vector<int> > &labyrinth, vector<Box*> &v_box, vector<SDL_Rect> &v_boxok){
        bool success = true;
        int i = 0;
        int j = 0;

        switch(direction){
        case SDLK_UP:
            i = (box_rect.y-box_h)/box_h;
            j = box_rect.x/box_w;
            if((box_rect.y-box_h) >= 0 && labyrinth[i][j] != 1 && labyrinth[i][j] != 2){
                box_rect.y-=box_h;
                if(labyrinth[i][j] == 3){
                    v_boxok.push_back(box_rect);
                    //supprime cette caisse
                    for(unsigned int c=0; c<v_box.size(); c++){
                        if(v_box[c] == this){
                            v_box.erase(v_box.begin()+c, v_box.begin()+c+1);
                            break;
                        }
                    }
                    labyrinth[i+1][j] = 0;
                    labyrinth[i][j] = 1;
                }
                else{
                    labyrinth[i+1][j] = 0;
                    labyrinth[i][j] = 2;
                }
            }
            else
                success = false;
            break;
        case SDLK_DOWN:
            i = (box_rect.y+box_h)/box_h;
            j = box_rect.x/box_w;
            if((box_rect.y+box_h) <= box_H-box_h  && labyrinth[i][j] != 1 && labyrinth[i][j] != 2){
                box_rect.y+=box_h;

                if(labyrinth[i][j] == 3){
                    v_boxok.push_back(box_rect);
                    //supprime cette caisse
                    for(unsigned int i=0; i<v_box.size(); i++){
                        if(v_box[i] == this){
                            v_box.erase(v_box.begin()+1, v_box.begin()+i+1);
                            break;
                        }
                    }
                    labyrinth[i-1][j] = 0;
                    labyrinth[i][j] = 1;
                }
                else{
                    labyrinth[i-1][j] = 0;
                    labyrinth[i][j] = 2;
                }
            }
            else
                success = false;

            break;
        case SDLK_LEFT:
            i = (box_rect.y)/box_h;
            j = (box_rect.x-box_w)/box_w;
            if((box_rect.x-box_w) >= 0  && labyrinth[i][j] != 1 && labyrinth[i][j] != 2){
                box_rect.x-=box_w;
                if(labyrinth[i][j] == 3){

                    v_boxok.push_back(box_rect);
                    //supprime cette caisse
                    for(unsigned int i=0; i<v_box.size(); i++){
                        if(v_box[i] == this){
                            v_box.erase(v_box.begin()+1, v_box.begin()+i+1);
                            break;
                        }
                    }
                    labyrinth[i][j+1] = 0;
                    labyrinth[i][j] = 1;

                }
                else{
                    labyrinth[i][j+1] = 0;
                    labyrinth[i][j] = 2;
                }
            }
            else
                success = false;

            break;
        case SDLK_RIGHT:
            i = (box_rect.y)/box_h;
            j = (box_rect.x+box_w)/box_w;
            if((box_rect.x+box_w) <= box_W-box_w  && labyrinth[i][j] != 1 && labyrinth[i][j] != 2){
                box_rect.x+=box_w;
                if(labyrinth[i][j] == 3){
                    v_boxok.push_back(box_rect);
                    //supprime cette caisse
                    for(unsigned int i=0; i<v_box.size(); i++){
                        if(v_box[i] == this){
                            v_box.erase(v_box.begin()+1, v_box.begin()+i+1);
                            break;
                        }
                    }
                    labyrinth[i][j-1] = 0;
                    labyrinth[i][j] = 1;
                }
                else{
                    labyrinth[i][j-1] = 0;
                    labyrinth[i][j] = 2;
                }
            }
            else
                success = false;

            break;

        default :
            success = false;
            break;
        }

        return success;
    }

    void updateLabyrinth(vector< vector<int> > labyrinth){

    }

    //verifier si une caisse se trouve dans ces coordonees
    bool containCoord(int x, int y){
        if(box_rect.x == x && box_rect.y == y)
            return true;
        else
            return false;
    }

    //mettre a jour la position
    void setPos(int x, int y){
        box_rect.x = x;
        box_rect.y = y;
    }

    //deallocation
    void clearBox(){
        SDL_FreeSurface(spirite);
        spirite = NULL;
    }
};

