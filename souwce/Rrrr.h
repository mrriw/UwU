#pragma once
#include "MRRW.h"

class Rrrr {
protected:
  void spawn(STR nm, const F& f);
  
  CHR loop = 's';
  void samsawa();
  void upgwade();
  void nirvini();
	
public:
  SDL_AppResult ewnt(SDL_Event* e);
  SDL_AppResult itwt();

  Rrrr();
  ~Rrrr() {
    std::cout << "U___________________________________________________________________________________________________________________________________U\n";
    std::cout << SDL_GetError() << std::endl;
    SDL_Quit();
  }
};
