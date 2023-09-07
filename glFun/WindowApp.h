#ifndef WINDOWAPP_H
#define WINDOWAPP_H

#include "Shader.h"
#include "Camera.h"
#include <GLFW/glfw3.h>

struct WindowData
{
	GLFWwindow* window;
	int width, height;

	WindowData(std::string title, int winX, int winY)
	{
		this->window = glfwCreateWindow(winX, winY, title.c_str(), NULL, NULL);
		this->width = winX;
		this->height = winY;
	}

	~WindowData()
	{
		delete window;
	}
};

struct CameraData
{
	Camera* camera;
	float lastX, lastY;

	CameraData(float winX, float winY)
	{
		this->camera = new Camera(0.0f, 0.0f, 9.0f, 0.0f, 1.0f, 0.0f, -90.0f, 0.0f);
		this->lastX = winX / 2.0f;
		this->lastY = winY / 2.0f;
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
	void runLoop();

private:
	float deltaTime;
	float lastFrame;
	std::vector<float> vertices, lightVertices;
	GLuint VAO, VBO, lightVAO, lightVBO;
	unsigned int texture;
	unsigned int specularMap;
	WindowData* winData;
	Shader* shader;
	Shader* lightShader;

	~WindowApp();
	void buffersConfig();
	void shadersConfig();
	void processInput();
	void cameraConfig();
	void texturesConfig();
	unsigned int loadTexture(char const*);

	static CameraData* camData;

	static void mouseCallback(GLFWwindow*, double, double);
	static void scrollCallback(GLFWwindow*, double, double);
	static void framebufferSizeCallback(GLFWwindow*, int, int);
};
#endif // !WINDOWAPP_H
