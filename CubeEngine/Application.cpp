
#include "Application.h"
#include "OpenGL.h"
#include <thread>
#include <stdexcept>
#include <iostream>

Application* Application::mInstance = nullptr;

void Application::createWindow(bool const isFullscreen)
{
	//禁止调整窗体大小
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	//根据是否全屏设置不同的Window Hint和monitor
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

	//判断是否成功创建窗体
	if (!mWindow)
		throw(std::runtime_error("Failed to create window!"));

	glfwMakeContextCurrent(mWindow);

	//监听键盘
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

	//事件主循环
	while (!shouldExit)
	{
		double nowTime;
		double passedTime;

		//等待
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
	//创建窗体
	glfwInit();
	createWindow(mIsFullscreen);
	glewInit();

	//启动事件线程
	std::atomic_bool shouleEventThreadEnd = false;
	
	std::thread eventThread([&]
	{
		refrestEventMain(shouleEventThreadEnd);
	});

	GLfloat testVertices[6][2] =
	{
		{-0.9f,-0.9f},
		{0.85f,-0.9f},
		{-0.9f,0.85f},
		{0.9f,-0.85f},
		{0.9f,0.9f},
		{-0.85f,0.9f},
	};
	const auto testShader = ogl::Shader::genShader(
		{
			{ GL_VERTEX_SHADER, "test.vert" },
			{ GL_FRAGMENT_SHADER,"test.frag" },
			{ GL_NONE,nullptr }
		}
	);
	ogl::useShader(testShader);
	const auto testVAO = ogl::VertexArrayObj::genVertexArrayObj();
	const auto testBuffer = ogl::Buffer::genBuffer(GL_ARRAY_BUFFER);
	testBuffer.copyFrom(testVertices, sizeof(testVertices));
	testVAO.vertexAttribPointer(0, testBuffer, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	//主循环
	while (!glfwWindowShouldClose(mWindow))
	{
		//简单的渲染
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		ogl::bindVertexArray(testVAO);
		ogl::drawVertexArray(testVAO, GL_TRIANGLES, 0, 6);

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
	// ReSharper disable CppAssignedValueIsNeverUsed
	shouleEventThreadEnd = true;
	// ReSharper restore CppAssignedValueIsNeverUsed
	eventThread.join();
	glfwTerminate();
}

void Application::switchToScene(ISceneObj)
{
	
}