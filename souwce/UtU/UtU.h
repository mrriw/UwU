#pragma once
#include "../U_U/U_U.h"

#define T_DIR DIR + "UtU/VtV/"
#define T_EXT ".UtU"

// tmpwt
class UtU : public U_U {
public:
  UtU() {}
  void itwt() override;
  ~UtU() {} 
};

inline UtU utu;
