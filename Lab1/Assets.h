#pragma once
#include <memory>
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"

// s_ prefix indicates shared_ptr

extern std::shared_ptr<Mesh> s_PlaneMesh;
extern std::shared_ptr<Mesh> s_MonkeyMesh;
extern std::shared_ptr<Mesh> s_BallMesh;
extern std::shared_ptr<Mesh> s_CapsuleMesh;

extern std::shared_ptr<Shader> s_FogShader;
extern std::shared_ptr<Shader> s_ToonShader;
extern std::shared_ptr<Shader> s_RimShader;

extern std::shared_ptr<Texture> s_WaterTexture;
extern std::shared_ptr<Texture> s_BrickWallTexture;
extern std::shared_ptr<Texture> s_BrickGroundTexture;