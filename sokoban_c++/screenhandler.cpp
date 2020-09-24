/**
* gerer la surface : mise a jour, ajout des sprites
*/

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include <map>

#include "structplayer.h"
#include "messenger.h"

void drawVectorBox(SDL_Renderer *&s_renderer);

using namespace std;

const int WIDTH = 480;
const int HEIGHT = 480;

const int width = 40;
const int height = 40;

vector< vector<int> > sokoban_labyrinth;
vector<Box*> v_box;
unsigned int nbr_box;
vector<SDL_Rect> v_boxok;
Player player(-1, -1);

map<string, SDL_Surface*> spirites = {
    {"menu", IMG_Load("images/menu.png")},
    {"menu_reussite", IMG_Load("images/menu_reussite.jpg")},
    {"fond", IMG_Load("images/fond.jpg")},
    {"mur", IMG_Load("images/mur.png")},
    {"caisse_ok", IMG_Load("images/caisse_ok.jpg")},
    {"objectif", IMG_Load("images/objectif.png")}
};


//dessiner un sprite
bool drawSpirite(SDL_Renderer *&s_renderer, string spirite_name, int x, int y, int w, int h){
    bool success = true;
    SDL_Rect spirite_rect;
    spirite_rect.x = x;
    spirite_rect.y = y;
    spirite_rect.w = w;
    spirite_rect.h = h;

    SDL_Texture *s_texture = NULL;
    s_texture = SDL_CreateTextureFromSurface(s_renderer, spirites[spirite_name]);


    if(s_texture != NULL){
        SDL_RenderCopy(s_renderer, s_texture, NULL, &spirite_rect);

        SDL_DestroyTexture(s_texture);
        s_texture = NULL;
    }
    else{
        cout<<"Failed to load Spirite \""<<spirite_name<<"\""<<endl;
        success = false;
    }

    return success;
}

//chargement de menu
void drawMenu(SDL_Renderer *&s_renderer){
    SDL_RenderClear(s_renderer);
    drawSpirite(s_renderer, "menu", 0, 0, WIDTH, HEIGHT);
    SDL_RenderPresent(s_renderer);
}

//chargement de menu reussite
void drawWiningMenu(SDL_Renderer *&s_renderer){
    SDL_RenderClear(s_renderer);
    drawSpirite(s_renderer, "menu_reussite", 0, 0, WIDTH, HEIGHT);
    SDL_RenderPresent(s_renderer);
}


//chargement d'un niveau
void drawLevel(vector< vector<int> > s_labyrinth, SDL_Renderer *&s_renderer){
    SDL_RenderClear(s_renderer);
    sokoban_labyrinth = s_labyrinth;
    if(drawSpirite(s_renderer, "fond", 0, 0, WIDTH, HEIGHT)){
        int y = 0;
        int x = 0;
        for(vector<int> v : sokoban_labyrinth){
            for(unsigned int j=0; j<v.size(); j++){
                x = 40*j;
                switch(v[j]){
                    case 0:
                        continue;
                        break;
                    case 1:
                        drawSpirite(s_renderer, "mur", x, y, width, height);
                        break;
                    case 2:
                        v_box.push_back(new Box(x, y));
                        break;
                    case 3:
                        drawSpirite(s_renderer, "objectif", x, y, width, height);
                        break;
                    case 4:
                        player.setPos(x, y);
                        player.drawPlayer(s_renderer);
                        break;
                        default : cout<<"Failed to load niveaux ScreenHandler->drawLevel"<<endl; break;
                }
            }
            y+=40;
        }
        nbr_box = v_box.size();
        drawVectorBox(s_renderer);
        SDL_RenderPresent(s_renderer);
    }

}

//chargement de l'editeur de nivreaux
void drawEditor(SDL_Renderer *&s_renderer){
    drawSpirite(s_renderer, "fond", 0,0,WIDTH, HEIGHT);
    SDL_RenderPresent(s_renderer);
}

//mise a jour de la surface de la fenetre
void updateScreen(SDL_Renderer *&s_renderer){
    drawSpirite(s_renderer, "fond", 0, 0, WIDTH, HEIGHT);
    int y = 0;
    int x = 0;

    for(vector<int> v : sokoban_labyrinth){
        for(unsigned int j=0; j<v.size(); j++){
            x = 40*j;
            switch(v[j]){
                case 0:
                    continue;
                    break;
                case 1:
                    drawSpirite(s_renderer, "mur", x, y, width, height);
                    break;
                case 2:
                    continue;
                    break;
                case 3:
                    drawSpirite(s_renderer, "objectif", x, y, width, height);
                    break;
                case 4:
                    continue;
                    break;
                default : cout<<"Failed to load niveaux ScreenHandler->drawLevel"<<endl; break;
            }
        }
        y+=40;
    }


}

//dessiner les caisse qui se trouve sur le vecteur
void drawVectorBox(SDL_Renderer *&s_renderer){
    for(Box *b : v_box)
        b->drawBox(s_renderer);
}

//dessiner les caisse qui se trouve sur l'objectif
void drawVectorBoxOk(SDL_Renderer *&s_renderer){
    if(v_boxok.size() > 0){
        for(SDL_Rect r : v_boxok)
            drawSpirite(s_renderer, "caisse_ok", r.x, r.y, width, height);
    }

}

//gestion des deplacement de joueur et de caisse
void movePlayer(SDL_Renderer *&s_renderer, int direction){
    player.movePlayer(direction, sokoban_labyrinth, v_box, v_boxok);
    SDL_RenderClear(s_renderer);
    updateScreen(s_renderer);

    drawVectorBox(s_renderer);
    drawVectorBoxOk(s_renderer);
    player.drawPlayer(s_renderer);

    SDL_RenderPresent(s_renderer);

    //send winning event
    if(v_box.empty() && v_boxok.size() == nbr_box)
        sendWinningmessage(s_renderer);

}


//retour au menu vider les deux "vector"
void clearVectors(){
    v_box.clear();
    v_boxok.clear();
    sokoban_labyrinth.clear();
}

//fermeture de la fenetre (free pointers, vider les vectors)
void closeScreen(){
    for(Box *b : v_box)
        delete b;
    for(auto it=spirites.begin(); it!=spirites.end(); it++){
        SDL_FreeSurface(it->second);
        it->second = NULL;
    }
    spirites.clear();
    clearVectors();
}
