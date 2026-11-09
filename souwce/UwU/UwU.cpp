#include "UwU.h"



UwU::UwU() : V_V{"vv", ffff} {
  vv = this;
  usu.stCntr(PS<F>(&f, [](F *) {}));
}

void UwU::itwt() {
  if (ucu.gtConwol(C_LEFT)) ff.x -= a;
  if (ucu.gtConwol(C_RIGHT)) ff.x += a;
  if (ucu.gtConwol(C_UP)) ff.y -= a;
  if (ucu.gtConwol(C_DOWN)) ff.y += a;
  if (ucu.gtConwol(C_KYS)) die();
  if (ucu.gtConwol(C_M0)) spawn(ucu.gtMF());

  for (auto &w : uwus) w->itwt();
  V_V::itwt();
  for (auto &w : uwus) w->rndr();
  V_V::rndr();
}

void UwU::rndr() {
  for (auto &w : uwus) w->rndr();
  V_V::rndr();
}

void UwU::die() {
  for (auto &w : uwus) w->die();
  V_V::die();
}


void UwU::spawn(const F &fff) {
  uwus.push_back(std::make_shared<uuUuwuUuu>(32, "vv", ucu.gtMF()));
}
