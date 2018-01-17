#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <atomic>

class IScene;

/*!Application��
 * ������������йصĻ�������. 
 * ��Ҫ�������еķ���run()��������������
 */
class Application
{
	//!Application����
	static Application* mInstance;

	//!��ǰ�Ƿ�Ϊȫ��ģʽ
	bool mIsFullscreen = false;

	//!GLFW Window
	GLFWwindow* mWindow = nullptr;

	//!���������Ϣ
	std::atomic_bool mKeys[GLFW_KEY_LAST]{ false };

protected:
	//!��������@note �����ʽΪUTF-8
	const char* mWindowTitle = "";
	
	//!������Ҫӵ��һ�������Ĺ��캯��������Ҫ�ж�Application�ļ�����
	Application() { mInstance = this; }

public:
	Application(const Application&)				= delete;
	Application(Application&&)					= delete;
	Application& operator=(Application&&)		= delete;
	Application& operator=(const Application&)	= delete;

	//!����������
	virtual ~Application() = default;

private:
	//!��������@param isFullscreen �Ƿ�ϣ����ȫ����ʽ��ʾ
	void createWindow(bool isFullscreen);

	//!ˢ���߳�������@param shouldExit �Ƿ񷵻�
	void refrestEventMain(std::atomic_bool& shouldExit);

	//!����ĳ�ʼ����������ʵ��
	virtual void init() = 0;

public:
	//!���ô�������@param c �µĴ�������
	void setWindowTitle(const char* c) { glfwSetWindowTitle(mWindow, mWindowTitle = c); }

	//!�л���ָ����Scene
	void switchToScene(IScene* scene);

	/*!
	 * ���ô˺�������������ʼ����
	 * @note ����run()�󣬻������ѭ����ֻ�е����ڱ��ر�ʱ�����˳�
	 * @param argc ������������������
	 * @param argv ������������
	 */
	void run(int argc, char* argv[]);

	//!��ȡ����״̬
	bool isKeyDown(const int key) const { return mKeys[key]; }

	//!��ȡ����@return Application����
	static Application& getInstance() { return *mInstance; }
};