#pragma once
#include "../U_U/U_U.h"
#include "../UsU/UsU.h"

/// deze bs kan beter :3
typedef enum {
  C_UP,
  C_DOWN,
  C_LEFT,
  C_RIGHT,
  C_JUMP,
  C_UPGWADE,

  C_MM, // middle
  C_M0,
  C_KYS,
  C_END
} CI;

// conwols
class UcU : public U_U {
protected:
  SDL_Keycode keyewnts[C_MM];
  Uint8 btnewnts[C_END - C_MM];
  BT conwols[C_END];
  BT ShConwols[C_END];
  F mf{0, 0};
  U4 sid = 0;

public:
  UcU()
      : keyewnts{SDLK_Z, SDLK_S, SDLK_Q, SDLK_D, SDLK_SPACE, SDLK_U},
        btnewnts{SDL_BUTTON_MIDDLE, SDL_BUTTON_LEFT, SDL_BUTTON_RIGHT} {
    for (size_t i = 0; i < C_END; i++)
      conwols[i] = false;
    for (size_t i = 0; i < C_END; i++)
      ShConwols[i] = conwols[i];
    sid = usu.add("crrsr");
    SDL_HideCursor();
  }
  void ewnt(SDL_Event *e);
  void itwt() override;
  ~UcU() {}

  F gtMF() { return usu.twanswate(mf); }
  BT gtConwol(CI ci) { return conwols[ci]; }
  BT gtConwolPuwse(CI ci) { return conwols[ci] > ShConwols[ci]; }
};

inline UcU ucu;
