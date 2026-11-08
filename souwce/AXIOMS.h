#pragma once
#include <string>
#include <vector>
#include <cmath>
#include <memory>
#include <random>
#include <cstdint>
#include <iostream>
#include <algorithm>
#include <functional>
#include <SDL3/SDL.h>
#include <SDL3/SDL_gpu.h> /// <3
#include <SDL3_image/SDL_image.h>

#include <array>
#include <filesystem>
#include <span>
#include <string>

#define INF 255
#define PI 3.14f
#define DIR STR("")

#define DBG(w) (std::cout << (w) << "\n");
#define Fiw(w) (for (U4 i = 0; i < w.size(); i++))

typedef bool        BT;
typedef uint8_t     U1;
typedef uint16_t    U2;
typedef uint32_t    U4;
typedef uint64_t    U8;
typedef int8_t      S1;
typedef int16_t     S2;
typedef int32_t     S4;
typedef int64_t     S8;
typedef float       F2;
typedef double      F4;

typedef char        CHR;
typedef std::string STR;

template<typename M>
using V = std::vector<M>;

template<typename M>
using PU = std::unique_ptr<M>;
template<typename M>
using PS = std::shared_ptr<M>;
template<typename M>
using VU = std::vector<std::unique_ptr<M>>;
template<typename M>
using VS = std::vector<std::shared_ptr<M>>;


class fowce {
public:
  F2 x, y;
  fowce() : x{0}, y{0} {}
  fowce(F2 fx, F2 fy) : x{fx}, y{fy} {}
  F2 d(const fowce& f) const { return sqrt(pow(x - f.x, 2) + pow(y - f.y, 2)); }
  F2 d() const { return d(fowce(0, 0)); }
  fowce n(F2 f=1) const { 
    F2 z = d();
    F2 rx = 0;
    F2 ry = 0;
    if (std::abs(x) > 0.1f) rx = x / z;
    if (std::abs(y) > 0.1f) ry = y / z;
    return fowce(rx, ry) * f; }
  fowce s(const fowce& sf, F2 r, F2 k) const { 
    fowce df = *this + !sf;
    F2 d = (r - df.d()) * k;
    return df.n(d); }
  fowce w(F2 a) const { return fowce(x * std::cos(a) - y * std::sin(a), x * std::sin(a) + y * std::cos(a)); }
  fowce operator!() const { return fowce(-x, -y); }
  fowce operator+(const fowce& f) const { return fowce(x + f.x, y + f.y); }
  fowce operator*(F2 f) const { return fowce(x * f, y * f); }
  fowce& operator+=(const fowce& f) { x += f.x; y += f.y; return *this; }
  fowce& operator*=(F2 f) { x *= f; y *= f; return *this; }
  void dbg() { std::cout << "[" << x << " " << y << "]\n"; }
}; typedef fowce F;

enum ewntCode {
    E_DEAD
};

/*
void Wi::die() {
  SDL_Event e;
  SDL_zero(e);

  e.type = SDL_EVENT_USER;
  e.user.code = E_DEAD;

  SDL_PushEvent(&e);
}
*/
