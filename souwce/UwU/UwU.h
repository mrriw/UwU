#pragma once
#include "../UcU/UcU.h"
#include "../UsU/UsU.h"
#include "../UvU/UvU.h"
#include "../UxU/UxU.h"

// UwU
/// memowy efcienc
/// post-UuU autospwite
/// future prediction met al de shadows :3
class UwU : public U_U {
private:
  BT m = false; // maar 1 mag true :3
  inline static VS<UwU> uwus{};
  inline static U4 sidDed = 0;

  F f;
  F ff;
  BT alive = true;

  VS<UwU> muwus;
  PU<UwU> suwu = nullptr;
  void mewge(PS<UwU> w);

  const F2 a = 0.8f;

  const U4 n = 8;
  U4 sid = 0;
  
  PS<UwU> gtMinD(); /// cooler funcparam?

protected:
  void spawn(STR nm, const F &fff, U4 ss = 0);

public:
  UwU();
  void itwtM();
  void dieM();
  UwU(STR nm, const F &fff, U4 ss);
  void itwt() override;
  void die();
  ~UwU() {}
};

inline UwU uwu;
