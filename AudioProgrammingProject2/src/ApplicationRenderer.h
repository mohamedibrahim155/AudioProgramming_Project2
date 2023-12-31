#pragma once
#include "Shader.h"
#include "Camera.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"
#include "VertexArray.h"
#include  "model.h"
#include "material.h"
#include "Light.h"
#include "Transform.h"
#include"LightManager.h"
#include "Random.h"

#include "AudioHandler.h"
#include "GraphicsRender.h"



class ApplicationRenderer
{
public:
	ApplicationRenderer();
	~ApplicationRenderer();

	static void SetViewPort(GLFWwindow* window, int width, int height);
	void KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
	void MouseCallBack(GLFWwindow* window, double xposIn, double yposIn);
	void MouseScroll(GLFWwindow* window, double xoffset, double yoffset);
	
	void WindowInitialize(int width, int height,  std::string windowName ="Window");
	
	void Start();
	void PreRender();
	void Render();
	void Clear();

	void ProcessInput(GLFWwindow* window);
	



private:
	GLFWwindow* window;
	Camera camera;

	GraphicsRender render;
	LightManager lightManager;

	Shader* defaultShader;
	Shader* lightShader;

	 int windowWidth;
	 int  WindowHeight;


	 float lastX;
	 float lastY;
	 float deltaTime;
	 double lastTime;
	 float lastFrame;

	 bool firstMouse;
	 bool isActivateSiren;

	 float ambulanceSpeed = 2.0f;

	 AudioHandler audioHandler;



#pragma region Models
	 Model* Plane;
	 Model* Plane2;
	 Model* Plane3;
	 Model* Plane4;
	 Model* Plane5;
	 Model* Plane6;



	 Model* Sphere;
	 Model* Sphere2;
	 Model* Sphere3;
	 Model* Sphere4;


	 Model* ambulance;
#pragma endregion

	 AudioId* Tv_Sound;
	 AudioId* doorBell_Sound;
	 AudioId* siren_Sound;
	 AudioId* CarStart_Sound;


};

