#pragma once
#include "MRRW.h"

class Rrrw {
protected:
  CHR loop = 's';
  void samsawa();
  void upgwade();
  void nirvini();
	
public:
  Rrrw(); 
  SDL_AppResult init(void** appstate, int argc, char* argv[]);
  SDL_AppResult ewnt(void* appstate, SDL_Event* e);
  SDL_AppResult itwt(void* appstate);
  void die(void *appstate, SDL_AppResult result);
  ~Rrrw() { std::cout << SDL_GetError() << std::endl; SDL_Quit(); }
};

#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>
inline Rrrw rr;
