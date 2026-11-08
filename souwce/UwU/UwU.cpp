#include "UwU.h"
#include <memory>

void UwU::mewge(PS<UwU> w) { w->die(); }

PS<UwU> UwU::gtMinD() {
  F2 minD = INF;
  PS<UwU> minW = uwus[0];
  for (auto &w : uwus) {
    minD = std::min(minD, f.d(w->f));
    minW = w;
  }
  return minW;
}

UwU::UwU() : f{F(0, 0)} {
  m = true;
  sid = usu.add("mrrew");
  sidDed = usu.add("VwV");
  usu.stCntr(PS<F>(&f, [](F *) {}));
  suwu = std::make_unique<UwU>(usu.gtNm(sid), f, 32);
}

void UwU::itwtM() {
  for (auto &w : uwus) w->itwt();
  if (ucu.gtConwol(C_LEFT)) ff.x -= a;
  if (ucu.gtConwol(C_RIGHT)) ff.x += a;
  if (ucu.gtConwol(C_UP)) ff.y -= a;
  if (ucu.gtConwol(C_DOWN)) ff.y += a;
  if (ucu.gtConwol(C_KYS)) die();
  if (ucu.gtConwol(C_M0)) spawn(usu.gtNm(sid), f);
}

UwU::UwU(STR nm, const F &fff, U4 ss) : f{fff} {
  sid = usu.add(nm);
  if (ss) suwu = std::make_unique<UwU>(nm, fff, ss - 1);
}

void UwU::spawn(STR nm, const F &fff, U4 ss) {
  uwus.push_back(std::make_shared<UwU>(nm, fff, ss));
}

void UwU::itwt() {
  if (m) itwtM();
  if (suwu) {
    suwu->itwt();
    suwu->f = f;
  } f += ff;
  
  if (alive)
    usu.rndrSpwite(f, sid);
  else // hier de doden a nr beneden clr
    usu.rndrSpwite(f, sidDed);
}

void UwU::die() {
  if (suwu)
    suwu->die();
  alive = false; /// miw
}
