
#include "Application.h"
#include <thread>
#include <stdexcept>
#include <iostream>

Application* Application::mInstance = nullptr;

void Application::createWindow(bool const isFullscreen)
{
	//��ֹ���������С
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	//�����Ƿ�ȫ�����ò�ͬ��Window Hint��monitor
	if (isFullscreen)
	{
		const auto monitor = glfwGetPrimaryMonitor();
		const auto mode = glfwGetVideoMode(monitor);

		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

		mWindow = glfwCreateWindow(mode->width, mode->height, mWindowTitle, monitor, nullptr);
	}
	else
		mWindow = glfwCreateWindow(1024, 768, mWindowTitle, nullptr, nullptr);

	//�ж��Ƿ�ɹ���������
	if (!mWindow)
		throw(std::runtime_error("Failed to create window!"));

	glfwMakeContextCurrent(mWindow);

	//��������
	glfwSetKeyCallback(mWindow, 
		[](GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		getInstance().mKeys[key] = action != GLFW_RELEASE;
	});
}

void Application::refrestEventMain(std::atomic_bool& shouldExit)
{
	auto lastRefreshTime = glfwGetTime();
	double tickTime = 0;

	//�¼���ѭ��
	while (!shouldExit)
	{
		double nowTime;
		double passedTime;

		//�ȴ�
		while ((passedTime = (nowTime = glfwGetTime()) - lastRefreshTime) < 0.05)
			std::this_thread::sleep_for
			(
				std::chrono::milliseconds(1)
			);

		tickTime += passedTime * 20;
		if (static_cast<int>(tickTime) % 20 == 0)
			std::cout << "[" << static_cast<int>(lastRefreshTime) << "]tick!" << static_cast<int>(tickTime) / 20 << std::endl;

		lastRefreshTime = nowTime;
	}
}

void Application::run(int argc, char* argv[])
{
	//��������
	glfwInit();
	createWindow(mIsFullscreen);
	glewInit();

	//�����¼��߳�
	std::atomic_bool shouleEventThreadEnd = false;
	
	std::thread eventThread([&]
	{
		refrestEventMain(shouleEventThreadEnd);
	});

	//��ѭ��
	while (!glfwWindowShouldClose(mWindow))
	{
		//�򵥵���Ⱦ
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBegin(GL_TRIANGLES);

		glVertex2f(0.0f, 0.0f);
		glVertex2f(0.0f, 1.0f);
		glVertex2f(1.0f, 1.0f);

		glEnd();
		glfwSwapBuffers(mWindow);
		glfwPollEvents();

		//�Ƿ��л�ȫ��
		if (glfwGetKey(mWindow, GLFW_KEY_F11) == GLFW_PRESS)
		{
			glfwDestroyWindow(mWindow);
			createWindow(mIsFullscreen = !mIsFullscreen);
		}
	}

	//����
	// ReSharper disable CppAssignedValueIsNeverUsed
	shouleEventThreadEnd = true;
	// ReSharper restore CppAssignedValueIsNeverUsed
	eventThread.join();
	glfwTerminate();
}

void Application::switchToScene(IScene* scene)
{
	
}