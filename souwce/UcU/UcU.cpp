#include "UcU.h"

void UcU::ewnt(SDL_Event* e) {
  switch (e->type) {
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
      for (size_t i = 0; i < C_END - C_MM; i++)
        if (e->button.button == btnewnts[i])
          conwols[i + C_MM] = true;
      break;
    case SDL_EVENT_MOUSE_BUTTON_UP:
      for (size_t i = 0; i < C_END - C_MM; i++)
        if (e->button.button == btnewnts[i])
          conwols[i + C_MM] = false;
      break;
    case SDL_EVENT_KEY_DOWN:
      for (size_t i = 0; i < C_MM; i++)
        if (e->key.key == keyewnts[i])
          conwols[i] = true;
      break;
    case SDL_EVENT_KEY_UP:
      for (size_t i = 0; i < C_MM; i++)
        if (e->key.key == keyewnts[i])
          conwols[i] = false;
      break;
    case SDL_EVENT_MOUSE_MOTION:
      F2 x, y;
      SDL_GetMouseState(&x, &y);
      mf = F(x, y);
      break;
    default:
      break;}
}

void UcU::itwt() { 
  for (size_t i = 0; i < C_END; i++) ShConwols[i] = conwols[i]; 
  usu.rndrSpwite(gtMF(), sid);
}