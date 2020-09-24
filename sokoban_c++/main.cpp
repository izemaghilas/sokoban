/**
* point d'enter de programme sokoban
*/

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "initializer.h"
#include "screenhandler.h"
#include "eventhandler.h"


using namespace std;

const int WIDTH = 480;
const int HEIGHT = 480;

//window
SDL_Window *sokoban_window = NULL;
//main renderer
SDL_Renderer *sokoban_renderer = NULL;

int main(int argc, char** argv)
{
    bool quit = false;
    SDL_Event sokoban_events;

    if (sokoban_init(WIDTH, HEIGHT, sokoban_window, sokoban_renderer)){
        drawMenu(sokoban_renderer);

        while(!quit){
            while(SDL_PollEvent(&sokoban_events) != 0){
                if(sokoban_events.type == SDL_QUIT)
                    quit = true;
                if(sokoban_events.type == SDL_KEYDOWN)
                    handle_keyboard_event(&sokoban_events, sokoban_renderer);

            }
        }
        closeScreen();
        sokoban_close(sokoban_window, sokoban_renderer);
    }

    return 0;
}
