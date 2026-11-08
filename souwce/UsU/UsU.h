#pragma once
#include "../U_U/U_U.h"

/// out class (mixt v&s)
/// ss->rndr(fwames ook)

#define S_W 256
#define S_H 256
#define S_FPS 32
#define S_DIR DIR + "UsU/VsV/"
#define S_EXT ".gif"

// spwites
class UsU : public U_U {
protected:
  F2 z = 8;
  U1 bgf = 255;

  S4 w;
  S4 h;
  PS<F> cf;
  
  std::vector<S2> fr;
  std::vector<U4> id;
  std::vector<U8> sh;
  std::vector<F2> r;
  
  U8 shTick = 0;
  
  std::vector<STR> names; 
  std::vector<F> dims; 
  std::vector<std::vector<SDL_Texture*>> frames;
  std::vector<IMG_Animation*> animations;
	
	SDL_Window* window = NULL;
	SDL_Renderer* rndrr = NULL;
  SDL_Texture* texture = NULL;
  SDL_Surface* surface = NULL;
  
  U4 xyz;
  F fxyz;
  STR sxyz = "abcdefghijklmnopqrstuvwxyz +";
  
public:
  U4 add(STR n);
  
  void stCntr(PS<F> f) { cf = f; } // maar 1 ding tegelijk

  void gtColor(const F& f, U1* r, U1* g, U1* b, U1* a) { SDL_ReadSurfacePixel(surface, f.x, f.y, r, g, b, a); }
  void stColor(U1 r, U1 g, U1 b, U1 a) { SDL_SetRenderDrawColor(rndrr, r, g, b, a); }

  STR gtNm(U4 i) { return names[id[i]]; }
  
  void rndrPoint(const F& f) { SDL_RenderPoint(rndrr, f.x, f.y); }
  void rndrLine(const F& f0, const F& f1) { SDL_RenderLine(rndrr, f0.x, f0.y, f1.x, f1.y); }
  void rndrRect(const F& f0, const F& f1, BT fill);
  void rndrCircle(const F& f, F2 r);
  void rndrSpwite(const F& f, U4 i);
  void rndrTxt(const F& f, STR txt);
  
  void resize() { SDL_GetWindowSize(window, &w, &h); }
  F twanswate(const F& f) { return F((f.x - w / 2.0f) / z + cf->x, (f.y - h / 2.0f) / z + cf->y ); };

  UsU();
  void itwt() override;
  ~UsU(); 
};

inline UsU usu;
