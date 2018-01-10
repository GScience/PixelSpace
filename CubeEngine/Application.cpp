
#include "Application.h"
#include <functional>
#include <stdexcept>
#include <GL/glew.h>
#include <GLFW\glfw3.h>

Application* Application::mInstance = nullptr;

void Application::createWindow(bool isFullscreen)
{
	//禁止调整窗体大小
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	//根据是否全屏设置不同的Window Hint和monitor
	if (isFullscreen)
	{
		GLFWmonitor *monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);

		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

		mWindow = glfwCreateWindow(mode->width, mode->height, mWindowTitle, monitor, NULL);
	}
	else
		mWindow = glfwCreateWindow(1024, 768, mWindowTitle, nullptr, nullptr);

	//判断是否成功创建窗体
	if (!mWindow)
		throw(std::runtime_error("Failed to create window!"));

	glfwMakeContextCurrent(mWindow);

	//监听键盘
	glfwSetKeyCallback(mWindow, 
		[](GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Application::getInstance().mKeys[key] = action != GLFW_RELEASE;
	});
}

void Application::run(int argc, char* argv[])
{
	glfwInit();
	createWindow(mIsFullscreen);
	glewInit();

	while (!glfwWindowShouldClose(mWindow))
	{
		//简单的渲染
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBegin(GL_TRIANGLES);

		glVertex2f(0.0f, 0.0f);
		glVertex2f(0.0f, 1.0f);
		glVertex2f(1.0f, 1.0f);

		glEnd();
		glfwSwapBuffers(mWindow);
		glfwPollEvents();

		//是否切换全屏
		if (glfwGetKey(mWindow, GLFW_KEY_F11) == GLFW_PRESS)
		{
			glfwDestroyWindow(mWindow);
			createWindow(mIsFullscreen = !mIsFullscreen);
		}
	}

	//结束
	glfwTerminate();
}