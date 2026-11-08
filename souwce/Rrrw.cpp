#include "Rrrw.h"

Rrrw::Rrrw() {}

void Rrrw::samsawa() {
  if (ucu.gtConwolPuwse(C_UPGWADE))
    loop = 'u';
}

void Rrrw::upgwade() {
  if (ucu.gtConwolPuwse(C_UPGWADE))
    loop = 's';
}

void Rrrw::nirvini() {}

SDL_AppResult Rrrw::init(void **appstate, int argc, char *argv[]) {
  return SDL_APP_CONTINUE;
}

SDL_AppResult Rrrw::ewnt(void *appstate, SDL_Event *e) {
  switch (e->type) {
  case SDL_EVENT_QUIT:
    return SDL_APP_SUCCESS;
  case SDL_EVENT_MOUSE_BUTTON_DOWN:
  case SDL_EVENT_MOUSE_BUTTON_UP:
  case SDL_EVENT_MOUSE_MOTION:
  case SDL_EVENT_KEY_DOWN:
  case SDL_EVENT_KEY_UP:
    ucu.ewnt(e);
    break;
  case SDL_EVENT_WINDOW_RESIZED:
    usu.resize();
    break;
  case SDL_EVENT_USER:
    switch (e->user.code) {
    case E_DEAD:
      std::cout << "az";
      break;
    default:
      break;
    }
    break;
  default:
    break;
  }

  return SDL_APP_CONTINUE;
}

SDL_AppResult Rrrw::itwt(void *appstate) {
  VitwtV();
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
    break;
  }

  return SDL_APP_CONTINUE;
}

void Rrrw::die(void *appstate, SDL_AppResult result) {}

inline SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
  return rr.init(appstate, argc, argv);
}
inline SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *e) {
  return rr.ewnt(appstate, e);
}
inline SDL_AppResult SDL_AppIterate(void *appstate) {
  return rr.itwt(appstate);
}
inline void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  rr.die(appstate, result);
}