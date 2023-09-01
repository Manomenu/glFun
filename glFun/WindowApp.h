#ifndef WINDOWAPP_H
#define WINDOWAPP_H

#include "Shader.h"
#include "Camera.h"
#include <GLFW/glfw3.h>

struct WindowData
{
	GLFWwindow* window;
	int width, height;
};

struct CameraData
{
	Camera* camera;
	float lastX, lastY;

	CameraData(Camera* camera, float lastX, float lastY)
	{
		this->camera = camera;
		this->lastX = lastX;
		this->lastY = lastY;
	}

	~CameraData()
	{
		delete camera;
	}
};

class WindowApp
{
public:
	WindowApp();
	~WindowApp();

	float vertices[36 * 5];
	float deltaTime;
	float lastFrame;
	WindowData winData;
	GLuint VAO, VBO;
	Shader* shader;
	static CameraData camData;
	static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
	static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

private:
	void buffersConfig();
	void shadersConfig();
	void processInput();
	void cameraConfig();
};
#endif // !WINDOWAPP_H
