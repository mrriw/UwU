#pragma once
#include "../U_U/U_U.h"

#define U_DIR DIR + "UuU/VuV/"
#define U_EXT ".UuU"
#define U_DBG 1

struct Vertex {
  float x, y, z;
};

// Upg
class UuU : public U_U {
private:
  SDL_Window *window = nullptr;
  SDL_GPUDevice *device = nullptr;

  SDL_GPUGraphicsPipeline *pipeline = nullptr;
  Uint32 numVertices = 0;
  SDL_GPUBuffer *vertexBuffer = nullptr;

  SDL_GPUShader *LoadShader(const std::string &shaderFilename);
  BT CreatePipeline();
  BT CreateVertexBuffer(std::vector<Vertex> vertices);

public:
  UuU();
  void ewnt(SDL_Event *e);
  void itwt() override;
  ~UuU();
};

inline UuU uuu;

// ./cnvrtAll.sh
