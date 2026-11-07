#include "Rrrr.h"

Rrrr::Rrrr() {
  
}

void Rrrr::samsawa() {
  if (ucu.gtConwolPuwse(C_M0)) uwu.spawn("tchiva00", ucu.gtMF());
  if (ucu.gtConwolPuwse(C_UPGWADE)) loop = 'u';
}

void Rrrr::upgwade() {
  if (ucu.gtConwolPuwse(C_UPGWADE)) loop = 's';
}

void Rrrr::nirvini() {

}

SDL_AppResult Rrrr::ewnt(SDL_Event* e) {
  switch (e->type) {
    case SDL_EVENT_QUIT:
      return SDL_APP_SUCCESS;
    case SDL_EVENT_KEY_DOWN:
      switch (e->key.key) {
        case SDLK_ESCAPE:
          return SDL_APP_SUCCESS;
        default:
          break;}
      break;
    case SDL_EVENT_USER:
      switch (e->user.code) {
        case E_DEAD:
          std::cout << "az";
          break;
        default:
          break;}
      break;
    default:
      break; }
      
  VewntV(e);
  return SDL_APP_CONTINUE;
}

SDL_AppResult Rrrr::itwt() {
  switch (loop) {
    case 's':
      samsawa();
      break;
    case 'u':
      upgwade();
      break;
    case 'n':
      nirvini();
      break;
    default:
      DBG("uhh...");
      break; }
      
  VitwtV();
  return SDL_APP_CONTINUE;
}
