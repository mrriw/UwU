#pragma once
#include "../UvU/UvU.h"
#include "../UxU/UxU.h"

// wing
class UwU : public UxU {
private:
  BT m = false; // maar 1 mag true :3
  inline static VS<UwU> vwvs{};

  VS<UwU> mvwvs;
  void mewge(PS<UwU> w);
  
  F2 a = 0.8f;
  U1 n = 8;
  U4 sid = 0;
  PS<UwU> gtMinD(); /// cooler funcparam?
  
protected:
public:
  UwU(const F& fff) : UxU{fff} { m = true; }
  UwU(STR nm, const F& fff);
  void ewnt(SDL_Event* e) override;
  void itwt() override;
  void die();
  ~UwU() {}
  
  void spawn(STR nm, const F& fff);
};

inline UwU uwu(gf);
