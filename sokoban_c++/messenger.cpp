/**
* envoi des evenements hors clavier et souris au eventhandler
*/

#include <SDL.h>

#include "eventhandler.h"

//envoi d'un message de niveau reussi
void sendWinningmessage(SDL_Renderer *&s_renderer){
    handle_win_event(s_renderer);
}
