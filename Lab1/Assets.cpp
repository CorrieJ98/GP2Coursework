#include "Assets.h"

#pragma region Mesh
std::shared_ptr<Mesh> s_PlaneMesh = std::make_shared<Mesh>("..\\res\\models\\surface.obj");
std::shared_ptr<Mesh> s_MonkeyMesh = std::make_shared<Mesh>("..\\res\\models\\monkey3.obj");
std::shared_ptr<Mesh> s_BallMesh = std::make_shared<Mesh>("..\\res\\models\\Ball.obj");
std::shared_ptr<Mesh> s_CapsuleMesh = std::make_shared<Mesh>("..\\res\\models\\capsule.obj");
#pragma endregion

#pragma region Shader
std::shared_ptr<Shader> s_FogShader = std::make_shared<Shader>("..\\res\\shaders\\fogShader.vert", "..\\res\\shaders\\fogShader.frag");
std::shared_ptr<Shader> s_ToonShader = std::make_shared<Shader>("..\\res\\shaders\\shaderToon.vert", "..\\res\\shaders\\shaderToon.frag");
std::shared_ptr<Shader> s_RimShader = std::make_shared<Shader>("..\\res\\shaders\\Rim.vert", "..\\res\\shaders\\Rim.frag");
#pragma endregion

#pragma region Texture
std::shared_ptr<Texture> s_WaterTexture = std::make_shared<Texture>("..\\res\\textures\\Water.jpg");
std::shared_ptr<Texture> s_BrickWallTexture = std::make_shared<Texture>("..\\res\\textures\\brickwall.jpg");
std::shared_ptr<Texture> s_BrickGroundTexture = std::make_shared<Texture>("..\\res\\textures\\bricks.jpg");
#pragma endregion