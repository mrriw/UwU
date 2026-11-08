#pragma once
#include "../U_U/U_U.h"

#define V_DIR DIR + "UvU/VvV/"
#define V_EXT ".wav"

// vibwasions
class UvU : public U_U {
protected:
  SDL_AudioDeviceID audioDevice = 0;
  std::vector<STR> names;
  std::vector<SDL_AudioSpec> specs;
  std::vector<Uint8*> wavs;
  std::vector<Uint32> lens;
  
  std::vector<SDL_AudioStream*> stweams;
  std::vector<int> shQueu;

// BG muwic
// sound cut off
        
public:
  U4 add(STR name);
  void play(U4 vid);

  UvU();
  void itwt() override;
  ~UvU();
};

inline UvU uvu;
