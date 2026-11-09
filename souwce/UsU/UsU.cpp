#include "UsU.h"

U4 UsU::add(STR nm) {
  U4 match = 0;

  for (U4 i = 0; i < names.size(); i++)
    if (names[i] == nm)
      match = i;

  if (!match) {
    STR loc = S_DIR + nm + S_EXT;
    IMG_Animation *animation = IMG_LoadAnimation(loc.c_str());
    if (!animation) {
      DBG(("UsU: " + nm + " not found")) return 0;
    };
    std::vector<SDL_Texture *> tframes;
    for (S2 i = 0; i < animation->count; i++)
      tframes.push_back(
          SDL_CreateTextureFromSurface(rndrr, animation->frames[i]));
    SDL_Texture *texture = tframes[0];
    F2 w, h;
    SDL_GetTextureSize(texture, &w, &h);

    names.push_back(nm);
    animations.push_back(animation);
    frames.push_back(tframes);
    dims.push_back(F(w, h));
    match = (U4)names.size() - 1;
  }

  fr.push_back(0);
  sh.push_back(SDL_GetTicks());
  id.push_back(match);
  r.push_back(0.0f);

  return id.size() - 1;
}

void UsU::rndrRect(const F &f0, const F &f1, BT fill) {
  SDL_FRect rect = {f0.x, f0.y, f1.x - f0.x, f1.y - f0.y};

  if (fill)
    SDL_RenderFillRect(rndrr, &rect);
  else
    SDL_RenderRect(rndrr, &rect);
}

void UsU::rndrCircle(const F &f, F2 r) {
  const F2 d = (r * 2);
  F2 x = (r - 1);
  F2 y = 0;
  F2 tx = 1;
  F2 ty = 1;
  F2 err = (tx - d);

  while (x >= y) {
    SDL_RenderPoint(rndrr, f.x + x, f.y - y);
    SDL_RenderPoint(rndrr, f.x + x, f.y + y);
    SDL_RenderPoint(rndrr, f.x - x, f.y - y);
    SDL_RenderPoint(rndrr, f.x - x, f.y + y);
    SDL_RenderPoint(rndrr, f.x + y, f.y - x);
    SDL_RenderPoint(rndrr, f.x + y, f.y + x);
    SDL_RenderPoint(rndrr, f.x - y, f.y - x);
    SDL_RenderPoint(rndrr, f.x - y, f.y + x);

    if (err <= 0) {
      ++y;
      err += ty;
      ty += 2;
    }
    if (err > 0) {
      --x;
      tx += 2;
      err += (tx - d);
    }
  }
}

void UsU::rndrSpwite(const F &f, U4 i) {
  SDL_Texture *texture = frames[id[i]][fr[i]];

  F2 w = dims[id[i]].x;
  F2 h = dims[id[i]].y;
  SDL_FRect rect = {(F2)round(f.x - (w / 2.0)), (F2)round(f.y - (h / 2.0)), w,
                    h};
  SDL_RenderTextureRotated(rndrr, texture, nullptr, &rect, r[i], NULL,
                           SDL_FLIP_NONE);

  /// post-UuU in UwU
  // draaien
  // r[i] += 8;

  if (shTick - sh[i] >= (U8)animations[id[i]]->delays[fr[i]]) {
    fr[i] = ++fr[i] % animations[id[i]]->count;
    sh[i] = shTick;
  }
}

void UsU::rndrTxt(const F &f, STR txt) {
  SDL_Texture *texture = frames[id[xyz]][0];
  F2 a = (F2)txt.size() * (fxyz.x / 2.0);
  F2 d = 0;

  for (auto &ch : txt) {
    SDL_FRect srcRect = {(F2)sxyz.find(ch) * fxyz.x, 0, fxyz.x, fxyz.y};
    SDL_FRect disRect = {(F2)round(f.x + d - a),
                         (F2)round(f.y - (fxyz.y / 2.0)), fxyz.x, fxyz.y};
    SDL_RenderTexture(rndrr, texture, &srcRect, &disRect);
    d += fxyz.x;
  }
}

UsU::UsU() {
  cf = std::make_shared<F>(0, 0);

  // window
  SDL_SetAppMetadata("mrrrrew", "8.0", "mrreww");
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
  SDL_CreateWindowAndRenderer(":3", S_W, S_H, SDL_WINDOW_RESIZABLE, &window,
                              &rndrr);
  SDL_MaximizeWindow(window);

  resize();

  // VcVale
  texture = SDL_CreateTexture(rndrr, SDL_PIXELFORMAT_RGBA8888,
                              SDL_TEXTUREACCESS_TARGET, S_W, S_H);
  SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

  // icon
  STR bmp = "dweamTrree.bmp";
  SDL_Surface *iconSurface = SDL_LoadBMP((S_DIR + bmp).c_str());
  SDL_SetWindowIcon(window, iconSurface);
  SDL_DestroySurface(iconSurface);

  surface = SDL_CreateSurface(w, h, SDL_PIXELFORMAT_RGBA32);

  // default
  add("VsV");

  // text
  xyz = add("xyz");
  SDL_Texture *texture = frames[id[xyz]][0];
  F2 w = dims[id[xyz]].x;
  F2 h = dims[id[xyz]].y;
  fxyz = F(w / (F2)sxyz.size(), h);
}

void UsU::itwt() {
  surface = SDL_RenderReadPixels(rndrr, NULL);
  SDL_SetRenderTarget(rndrr, NULL);
  SDL_FRect r = {w / 2.0f - cf->x * z, h / 2.0f - cf->y * z, S_W * z, S_H * z};
  SDL_RenderTexture(rndrr, texture, NULL, &r);

  SDL_RenderPresent(rndrr);
  while (shTick + 1000 / S_FPS > SDL_GetTicks()) {
  }
  // DBG(SDL_GetTicks() - shTick);
  shTick = SDL_GetTicks();

  SDL_SetRenderTarget(rndrr, texture);
  SDL_SetRenderDrawColor(rndrr, 42, 4, 51, bgf);
  SDL_RenderClear(rndrr);
}

UsU::~UsU() {
  SDL_DestroyRenderer(rndrr);
  SDL_DestroyWindow(window);
  for (auto &frame : frames)
    for (SDL_Texture *texture : frame)
      if (texture)
        SDL_DestroyTexture(texture);
  for (IMG_Animation *animation : animations)
    if (animation)
      IMG_FreeAnimation(animation);
  frames.clear();
  animations.clear();
}
