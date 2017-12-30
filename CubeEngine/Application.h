#pragma once

/*!
包含了与程序有关的基本操作. 
需要调用其中的方法run()来启动整个程序。
*/
class Application
{
private:

protected:
	/*!
	窗口名称
	@note 编码格式为UTF-8
	*/
	const char* mWindowTitle = "";
	
	//!子类需要拥有一个公共的构造函数，其中要有对Application的简单配置
	Application() {}

	//!程序的初始化，由子类实现
	virtual void init() = 0;

	//!设置窗口名称@param c 新的窗口名称
	void setWindowTitle(const char* c);

public:
	//!禁止拷贝构造
	Application(const Application&) = delete;

	/*!
	调用此函数后，整个程序开始运行。
	@note 调用run()后，会进入主循环，只有当窗口被关闭时才能退出。
	*/
	void run();
};