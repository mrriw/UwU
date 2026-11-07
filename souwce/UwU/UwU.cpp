#include "UwU.h"



void UwU::mewge(PS<UwU> w) {
  w->die();
}

PS<UwU> UwU::gtMinD() { 
  F2 minD = INF;
  PS<UwU> minW = vwvs[0];
  for (auto& w : vwvs) {
    minD = std::min(minD, f.d(w->f));
    minW = w; } 
  return minW;
}


UwU::UwU(STR nm, const F& fff) : UxU{fff} {
  DBG(nm);
  sid = usu.add(nm);
}

void UwU::ewnt(SDL_Event* e) {
  if (m)
    for (auto& w : vwvs)
      w->ewnt(e);
}

void UwU::itwt() {
  if (m)
    for (auto& w : vwvs)
      w->itwt();
  UxU::itwt();
  
  usu.stColor(64, 10, 64, 128);
  usu.rndrCircle(f, 50);
  usu.rndrSpwite(f, sid);
  
  if (ucu.gtConwol(C_LEFT)) ff.x -= a;
  if (ucu.gtConwol(C_RIGHT)) ff.x += a;
  if (ucu.gtConwol(C_UP)) ff.y -= a;
  if (ucu.gtConwol(C_DOWN)) ff.y += a;
}

void UwU::spawn(STR nm, const F& fff) {
  vwvs.push_back(std::make_shared<UwU>(nm, fff));
}

void UwU::die() {
  if (m)
    gtMinD()->m = true;

  alive = false; /// miw
}