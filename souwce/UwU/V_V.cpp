#include "V_V.h"

V_V::V_V(STR nm, const F &fff) : f {fff} {
  s_idl = usu.add(nm);
  s_ded = usu.add(nm);
}

void V_V::rndr() {
  if (alive)
    usu.rndrSpwite(f, s_idl); /// het is obviouss
  else                            /// hier de doden a nr beneden clr
    usu.rndrSpwite(f, s_ded);
}
