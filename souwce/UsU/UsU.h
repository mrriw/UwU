#pragma once
#include "../U_U/U_U.h"

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
  F2 cx = S_W/2;
  F2 cy = S_H/2;
  
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

  void gtColor(const F& f, U1* r, U1* g, U1* b, U1* a) { SDL_ReadSurfacePixel(surface, f.x, f.y, r, g, b, a); }
  void stColor(U1 r, U1 g, U1 b, U1 a) { SDL_SetRenderDrawColor(rndrr, r, g, b, a); }
  
  void rndrPoint(const F& f) { SDL_RenderPoint(rndrr, f.x, f.y); }
  void rndrLine(const F& f0, const F& f1) { SDL_RenderLine(rndrr, f0.x, f0.y, f1.x, f1.y); }
  void rndrRect(const F& f0, const F& f1, BT fill);
  void rndrCircle(const F& f, F2 r);
  void rndrSpwite(const F& f, U4 sid);
  void rndrTxt(const F& f, STR txt);
  
  F twanswate(const F& f) { return F((f.x - w / 2) / z + cx, (f.y - h / 2) / z + cy ); };

  UsU();
  void ewnt(SDL_Event* e) override;
  void itwt() override;
  ~UsU(); 
};

inline UsU usu;
