#pragma once
#include "../UcU/UcU.h"
#include "../UsU/UsU.h"
#include "../UvU/UvU.h"


// wimit: 3000 homing wormen met uu = 32
/// memowy efcienc
//// gwappl
//?// powes
//// mrrge met particle simulationns
//// pwojectilles
/// future prediction met al de shadows :3
/// forms type shiii
//// post UuU ofc: auto spwite
//// fix mew
         
class V_V : public U_U {
protected:
  inline static VS<V_V> uwus{};
  inline static V_V* vv = nullptr;
  F ff;
  BT alive = true;
  F2 a = 0.8f;
  U4 n = 8;
  U4 s_idl = 0;
  U4 s_ded = 0;
public:
  F f;
  V_V(STR nm, const F &fff);
  void itwt() override { f += ff; }
  virtual void rndr();
  virtual void die() { alive = false; };
  ~V_V() { die(); }
};
