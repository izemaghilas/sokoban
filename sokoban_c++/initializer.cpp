/**
* initialiser le programme sokoban
*/

#include <iostream>
#include <SDL.h>

using namespace std;

//initialisation de bibliotheque SDL, creation de la fenetere et le renderer
bool sokoban_init(int w, int h, SDL_Window *&s_window, SDL_Renderer *&s_renderer){
    bool success = true;
    if(SDL_Init(SDL_INIT_VIDEO) < 0 ){
        cout<<cout<<"SDL could not initialize! SDL_Error: "<<SDL_GetError()<<endl;
        success = false;
    }
    else{
        s_window = SDL_CreateWindow("Sokoban",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
        if(s_window == NULL){
            cout<<"Window could not be created! SDL_Error: "<< SDL_GetError() <<endl;
            success = false;
        }
        else
            s_renderer = SDL_CreateRenderer(s_window, -1, SDL_RENDERER_SOFTWARE);
    }

    return success;
}

//liberation de la memoire
void sokoban_close(SDL_Window *&s_window, SDL_Renderer *&s_renderer){
    //free surface
    SDL_DestroyRenderer(s_renderer);
    s_renderer = NULL;

    //destroy window
    SDL_DestroyWindow(s_window);
    s_window = NULL;


    //Quit SDL
    SDL_Quit();
}
