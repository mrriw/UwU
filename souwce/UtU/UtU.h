#pragma once
#include "../U_U/U_U.h"

#define T_DIR "save0"
#define T_EXT ".UtU"

class UtU : public U_U {
protected:
public:
  UtU();
  void ewnt(SDL_Event* e) override;
  void itwt() override;
  ~UtU() {} 
};

inline UtU utu;
