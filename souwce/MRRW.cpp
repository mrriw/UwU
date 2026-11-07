#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>
#include "Rrrr.h" // MRRW.h via hier; 
Rrrr rr;
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) { return SDL_APP_CONTINUE; }
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* e) { return rr.ewnt(e); }
SDL_AppResult SDL_AppIterate(void* appstate) { return rr.itwt(); }
void SDL_AppQuit(void* appstate, SDL_AppResult result) { }
