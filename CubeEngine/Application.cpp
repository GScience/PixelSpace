
#include "Application.h"
#include <GL/glew.h>
#include <GLFW\glfw3.h>

void Application::run()
{
	GLFWwindow* window;

	glfwInit();
	window = glfwCreateWindow(512, 512, mWindowTitle, nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glewInit();

	while (!glfwWindowShouldClose(window)) glfwPollEvents();
}