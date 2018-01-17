#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <atomic>

class IScene;

/*!Application类
 * 包含了与程序有关的基本操作. 
 * 需要调用其中的方法run()来启动整个程序。
 */
class Application
{
	//!Application单例
	static Application* mInstance;

	//!当前是否为全屏模式
	bool mIsFullscreen = false;

	//!GLFW Window
	GLFWwindow* mWindow = nullptr;

	//!储存键盘信息
	std::atomic_bool mKeys[GLFW_KEY_LAST]{ false };

protected:
	//!窗体名称@note 编码格式为UTF-8
	const char* mWindowTitle = "";
	
	//!子类需要拥有一个公共的构造函数，其中要有对Application的简单配置
	Application() { mInstance = this; }

public:
	Application(const Application&)				= delete;
	Application(Application&&)					= delete;
	Application& operator=(Application&&)		= delete;
	Application& operator=(const Application&)	= delete;

	//!虚析构函数
	virtual ~Application() = default;

private:
	//!创建窗体@param isFullscreen 是否希望以全屏形式显示
	void createWindow(bool isFullscreen);

	//!刷新线程主函数@param shouldExit 是否返回
	void refrestEventMain(std::atomic_bool& shouldExit);

	//!程序的初始化，由子类实现
	virtual void init() = 0;

public:
	//!设置窗体名称@param c 新的窗口名称
	void setWindowTitle(const char* c) { glfwSetWindowTitle(mWindow, mWindowTitle = c); }

	//!切换到指定的Scene
	void switchToScene(IScene* scene);

	/*!
	 * 调用此函数后，整个程序开始运行
	 * @note 调用run()后，会进入主循环，只有当窗口被关闭时才能退出
	 * @param argc 程序启动参数的数量
	 * @param argv 程序启动参数
	 */
	void run(int argc, char* argv[]);

	//!获取按键状态
	bool isKeyDown(const int key) const { return mKeys[key]; }

	//!获取单例@return Application引用
	static Application& getInstance() { return *mInstance; }
};