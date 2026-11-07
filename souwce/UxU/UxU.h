#pragma once
#include "../U_U/U_U.h"
#include "../UcU/UcU.h"
#include "../UsU/UsU.h"


// mxw
class UxU : public U_U {
private:
  F sf;
protected:
  F f;
  F ff;
  BT alive = true;
  
public:
  UxU(const F& fff) : f{fff} { }  
  void ewnt(SDL_Event* e) override {}
  void itwt() override { sf = f; f += ff; }  
  ~UxU() {}  
};

inline UxU uxu(gf);
