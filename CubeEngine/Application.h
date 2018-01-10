#pragma once

#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include <atomic>

class Scene;

/*!
������������йصĻ�������. 
��Ҫ�������еķ���run()��������������
*/
class Application
{
private:
	//!Application����
	static Application* mInstance;

	//!��ǰ�Ƿ�Ϊȫ��ģʽ
	bool mIsFullscreen = false;

	//!GLFW Window
	GLFWwindow* mWindow = nullptr;

	//!���������Ϣ
	std::atomic_bool mKeys[GLFW_KEY_LAST];

protected:
	//!��������@note �����ʽΪUTF-8
	const char* mWindowTitle = "";
	
	//!������Ҫӵ��һ�������Ĺ��캯��������Ҫ�ж�Application�ļ�����
	Application() { mInstance = this; }

	//!��ֹ��������
	Application(const Application&) = delete;

private:
	//!��������@param isFullscreen �Ƿ�ϣ����ȫ����ʽ��ʾ
	void createWindow(bool isFullscreen);

	//!ˢ���߳�������
	void refrestEventMain();

	//!����ĳ�ʼ����������ʵ��
	virtual void init() = 0;

protected:
	//!���ô�������@param c �µĴ�������
	void setWindowTitle(const char* c);

	//!���ô����С@param w ������@param h ����߶�
	void setWindowSize(int w, int h);

	//!�л���ָ����Scene
	void switchToScene(Scene* scene);

public:
	/*!
	���ô˺�������������ʼ����
	@note ����run()�󣬻������ѭ����ֻ�е����ڱ��ر�ʱ�����˳�
	@param argc ������������������
	@param argv ������������
	*/
	void run(int argc, char* argv[]);

	//!��ȡ����@return Application����
	static Application& getInstance() { return *mInstance; }
};