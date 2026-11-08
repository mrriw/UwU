#pragma once
#include "../U_U/U_U.h"

#define U_DIR DIR + "UuU/VtV/"
#define U_EXT ".UuU"

// Upg
class UuU : public U_U {
private:
  SDL_Window* window = nullptr;
  SDL_GPUDevice* device = nullptr;

  SDL_GPUGraphicsPipeline* pipeline = nullptr;
  Uint32 numVertices = 0;
  SDL_GPUBuffer* vertexBuffer = nullptr;

public:
  UuU();
  void itwt() override {};
  ~UuU() {}
};

inline UuU uuu;
