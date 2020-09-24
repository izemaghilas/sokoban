#include <vector>

using namespace std;

void drawMenu(SDL_Renderer *&s_renderer);
void drawWiningMenu(SDL_Renderer *&s_renderer);
void drawLevel(vector< vector<int> > s_labyrinth, SDL_Renderer *&s_renderer);
void drawEditor(SDL_Renderer *&s_renderer);
void movePlayer(SDL_Renderer *&s_renderer, int direction);
void clearVectors();
void closeScreen();
