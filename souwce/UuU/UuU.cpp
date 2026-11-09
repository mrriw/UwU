#include "UuU.h"

struct MyAppState {};

SDL_GPUShader *UuU::LoadShader(const std::string &shaderFilename) {
  // Auto-detect the shader stage from the file name for convenience
  SDL_GPUShaderStage stage;
  if (shaderFilename.find(".vert") != std::string::npos) {
    stage = SDL_GPU_SHADERSTAGE_VERTEX;
  } else if (shaderFilename.find(".frag") != std::string::npos) {
    stage = SDL_GPU_SHADERSTAGE_FRAGMENT;
  } else {
    SDL_Log("Couldn't deduce shader stage from file name: %s",
            shaderFilename.c_str());
    return nullptr;
  }

  std::filesystem::path fullPath =
      std::filesystem::path(SDL_GetBasePath()) / "UuU/VuV";
  SDL_GPUShaderFormat format = SDL_GPU_SHADERFORMAT_INVALID;
  const char *entrypoint;

  SDL_GPUShaderFormat backendFormats = SDL_GetGPUShaderFormats(device);
  if (backendFormats & SDL_GPU_SHADERFORMAT_SPIRV) {
    fullPath /= shaderFilename + ".spv";
    format = SDL_GPU_SHADERFORMAT_SPIRV;
    entrypoint = "main";
  } else if (backendFormats & SDL_GPU_SHADERFORMAT_MSL) {
    fullPath /= shaderFilename + ".msl";
    format = SDL_GPU_SHADERFORMAT_MSL;
    entrypoint = "main0";
  } else if (backendFormats & SDL_GPU_SHADERFORMAT_DXIL) {
    fullPath /= shaderFilename + ".dxil";
    format = SDL_GPU_SHADERFORMAT_DXIL;
    entrypoint = "main";
  } else {
    SDL_Log("Couldn't find a supported shader format for backend %s!",
            SDL_GetGPUDeviceDriver(device));
    return nullptr;
  }

  size_t fileSize;
  void *code = SDL_LoadFile(fullPath.string().c_str(), &fileSize);
  if (code == nullptr) {
    SDL_Log("Couldn't load shader file from disk!\n\t%s", SDL_GetError());
    return nullptr;
  }

  SDL_GPUShaderCreateInfo shaderInfo = SDL_GPUShaderCreateInfo{
      .code_size = fileSize,
      .code = static_cast<Uint8 *>(code),
      .entrypoint = entrypoint,
      .format = format,
      .stage = stage,
  };
  SDL_GPUShader *shader = SDL_CreateGPUShader(device, &shaderInfo);
  if (shader == nullptr) {
    SDL_Log("Couldn't create shader from file %s: %s", fullPath.c_str(),
            SDL_GetError());
    SDL_free(code);
    return nullptr;
  }

  SDL_free(code);
  return shader;
}

/// Returns true on success, false on failure
BT UuU::CreatePipeline() {
  SDL_GPUShader *vertexShader = LoadShader("OnlyPosition.vert");
  if (vertexShader == nullptr) {
    SDL_Log("Couldn't create vertex shader!");
    return false;
  }

  SDL_GPUShader *fragmentShader = LoadShader("SolidColor.frag");
  if (fragmentShader == nullptr) {
    SDL_Log("Couldn't create fragment shader!");
    return false;
  }

  std::array vertexBufferDescriptions{
      SDL_GPUVertexBufferDescription{
          .slot = 0,
          .pitch = sizeof(Vertex),
          .input_rate = SDL_GPU_VERTEXINPUTRATE_VERTEX,
          .instance_step_rate = 0,
      },
  };

  std::array vertexAttributes{
      SDL_GPUVertexAttribute{
          .location = 0,
          .buffer_slot = 0,
          .format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT,
          .offset = 0 * sizeof(float),
      },
      SDL_GPUVertexAttribute{
          .location = 1,
          .buffer_slot = 0,
          .format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT,
          .offset = 1 * sizeof(float),
      },
      SDL_GPUVertexAttribute{
          .location = 2,
          .buffer_slot = 0,
          .format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT,
          .offset = 2 * sizeof(float),
      },
  };

  std::array colorTargetDescriptions{SDL_GPUColorTargetDescription{
      .format = SDL_GetGPUSwapchainTextureFormat(device, window)}};

  SDL_GPUGraphicsPipelineCreateInfo pipelineCreateInfo =
      SDL_GPUGraphicsPipelineCreateInfo{
          .vertex_shader = vertexShader,
          .fragment_shader = fragmentShader,
          .vertex_input_state =
              SDL_GPUVertexInputState{
                  .vertex_buffer_descriptions = vertexBufferDescriptions.data(),
                  .num_vertex_buffers = vertexBufferDescriptions.size(),
                  .vertex_attributes = vertexAttributes.data(),
                  .num_vertex_attributes = vertexAttributes.size(),
              },
          .primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST,
          .rasterizer_state =
              SDL_GPURasterizerState{
                  .fill_mode = SDL_GPU_FILLMODE_FILL,
                  .cull_mode = SDL_GPU_CULLMODE_BACK,
                  .front_face = SDL_GPU_FRONTFACE_COUNTER_CLOCKWISE,
              },
          .target_info =
              SDL_GPUGraphicsPipelineTargetInfo{
                  .color_target_descriptions = colorTargetDescriptions.data(),
                  .num_color_targets = colorTargetDescriptions.size(),
              },
  };
  pipeline = SDL_CreateGPUGraphicsPipeline(device, &pipelineCreateInfo);
  if (pipeline == nullptr) {
    SDL_Log("Couldn't create graphics pipeline! %s", SDL_GetError());
    return false;
  }

  SDL_ReleaseGPUShader(device, vertexShader);
  SDL_ReleaseGPUShader(device, fragmentShader);

  return true;
}

/// Returns true on success, false on failure
BT UuU::CreateVertexBuffer(std::vector<Vertex> vertices) {
  numVertices = vertices.size();
  Uint32 verticesSize = numVertices * sizeof(Vertex);

  SDL_GPUBufferCreateInfo vertexBufferCreateInfo = SDL_GPUBufferCreateInfo{
      .usage = SDL_GPU_BUFFERUSAGE_VERTEX,
      .size = verticesSize,
  };
  vertexBuffer = SDL_CreateGPUBuffer(device, &vertexBufferCreateInfo);
  if (vertexBuffer == nullptr) {
    SDL_Log("Couldn't create vertex buffer: %s", SDL_GetError());
    return false;
  }

  SDL_GPUTransferBufferCreateInfo transferBufferCreateInfo =
      SDL_GPUTransferBufferCreateInfo{
          .usage = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD,
          .size = verticesSize,
  };
  SDL_GPUTransferBuffer *transferBuffer =
      SDL_CreateGPUTransferBuffer(device, &transferBufferCreateInfo);
  if (transferBuffer == nullptr) {
    SDL_Log("Couldn't create transfer buffer: %s", SDL_GetError());
    return false;
  }

  Vertex *transferData = static_cast<Vertex *>(
      SDL_MapGPUTransferBuffer(device, transferBuffer, false));
  if (transferData == nullptr) {
    SDL_Log("Couldn't map transfer buffer: %s", SDL_GetError());
    SDL_ReleaseGPUTransferBuffer(device, transferBuffer);
    return false;
  }

  SDL_memcpy(transferData, vertices.data(), verticesSize);

  SDL_UnmapGPUTransferBuffer(device, transferBuffer);

  // Upload the transfer data to the vertex buffer
  SDL_GPUCommandBuffer *uploadCmdBuf = SDL_AcquireGPUCommandBuffer(device);
  if (uploadCmdBuf == nullptr) {
    SDL_Log("Couldn't acquire GPU command buffer: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  SDL_GPUCopyPass *copyPass = SDL_BeginGPUCopyPass(uploadCmdBuf);

  SDL_GPUTransferBufferLocation bufferLocation = SDL_GPUTransferBufferLocation{
      .transfer_buffer = transferBuffer,
      .offset = 0,
  };

  SDL_GPUBufferRegion bufferRegion = SDL_GPUBufferRegion{
      .buffer = vertexBuffer,
      .offset = 0,
      .size = verticesSize,
  };

  SDL_UploadToGPUBuffer(copyPass, &bufferLocation, &bufferRegion, false);

  SDL_EndGPUCopyPass(copyPass);
  if (!SDL_SubmitGPUCommandBuffer(uploadCmdBuf)) {
    SDL_Log("Couldn't submit GPU command buffer: %s", SDL_GetError());
    return false;
  }

  SDL_ReleaseGPUTransferBuffer(device, transferBuffer);

  return true;
}

UuU::UuU() {
  if (!U_DBG)
    return;
  window = SDL_CreateWindow("Hello, SDL GPU!", 1280, 720, 0);
  if (window == nullptr) {
    SDL_Log("Couldn't create window: %s", SDL_GetError());
    return;
  }

  SDL_GPUShaderFormat formatFlags = SDL_GPU_SHADERFORMAT_SPIRV |
                                    SDL_GPU_SHADERFORMAT_DXIL |
                                    SDL_GPU_SHADERFORMAT_MSL;
  device = SDL_CreateGPUDevice(formatFlags, true, nullptr);
  if (device == nullptr) {
    SDL_Log("Couldn't create GPU device: %s", SDL_GetError());
    return;
  }

  if (!SDL_ClaimWindowForGPUDevice(device, window)) {
    SDL_Log("Couldn't claim window for GPU device: %s", SDL_GetError());
    return;
  }

  if (!CreatePipeline()) {
    // Error message already logged in the function
    return;
  }

  // Counter-Clockwise order:
  std::array vertices{
      Vertex{0.5f, 0.5f, 0.0f},   // Bottom-Left
      Vertex{-0.5f, 0.5f, 0.0f},  // Bottom-Right
      Vertex{0.0f, -0.5f, 0.0f},  // Top-Middle
      Vertex{-0.5f, -0.5f, 0.0f}, // 2Bottom-Left
      Vertex{0.5f, -0.5f, 0.0f},  // 2Bottom-Right
      Vertex{0.0f, 0.5f, 0.0f},   // 2Top-Middle
  };

  std::vector<Vertex> vertexVector(vertices.begin(), vertices.end());
  if (!CreateVertexBuffer(vertexVector)) {
    // Error message already logged in the function
    return;
  }
}

void UuU::ewnt(SDL_Event *e) {}

void UuU::itwt() {
  if (!U_DBG)
    return;
  SDL_GPUCommandBuffer *commandBuffer = SDL_AcquireGPUCommandBuffer(device);
  if (commandBuffer == nullptr) {
    SDL_Log("Couldn't acquire GPU command buffer: %s", SDL_GetError());
    return;
  }

  SDL_GPUTexture *swapchainTexture;
  if (!SDL_WaitAndAcquireGPUSwapchainTexture(
          commandBuffer, window, &swapchainTexture, nullptr, nullptr)) {
    SDL_Log("Couldn't acquire swapchain texture: %s", SDL_GetError());
    return;
  }

  if (swapchainTexture != nullptr) {
    SDL_GPUColorTargetInfo colorTargetInfo = {
        .texture = swapchainTexture,
        .clear_color = SDL_FColor{0.4f, 0.0f, 0.5f, 1.0f},
        .load_op = SDL_GPU_LOADOP_CLEAR,
        .store_op = SDL_GPU_STOREOP_STORE,
    };

    SDL_GPURenderPass *renderPass =
        SDL_BeginGPURenderPass(commandBuffer, &colorTargetInfo, 1, nullptr);

    SDL_BindGPUGraphicsPipeline(renderPass, pipeline);

    std::array vertexBuffers{
        SDL_GPUBufferBinding{
            .buffer = vertexBuffer,
            .offset = 0,
        },
    };
    SDL_BindGPUVertexBuffers(renderPass, 0, vertexBuffers.data(),
                             vertexBuffers.size());

    SDL_DrawGPUPrimitives(renderPass, numVertices, 1, 0, 0);

    SDL_EndGPURenderPass(renderPass);
  }

  SDL_SubmitGPUCommandBuffer(commandBuffer);
}

UuU::~UuU() {
  SDL_ReleaseGPUBuffer(device, vertexBuffer);
  SDL_ReleaseGPUGraphicsPipeline(device, pipeline);
  SDL_ReleaseWindowFromGPUDevice(device, window);
  SDL_DestroyGPUDevice(device);
  SDL_DestroyWindow(window);
}