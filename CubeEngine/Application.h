#pragma once

/*!
������������йصĻ�������. 
��Ҫ�������еķ���run()��������������
*/
class Application
{
private:

protected:
	/*!
	��������
	@note �����ʽΪUTF-8
	*/
	const char* mWindowTitle = "";
	
	//!������Ҫӵ��һ�������Ĺ��캯��������Ҫ�ж�Application�ļ�����
	Application() {}

	//!����ĳ�ʼ����������ʵ��
	virtual void init() = 0;

	//!���ô�������@param c �µĴ�������
	void setWindowTitle(const char* c);

public:
	//!��ֹ��������
	Application(const Application&) = delete;

	/*!
	���ô˺�������������ʼ���С�
	@note ����run()�󣬻������ѭ����ֻ�е����ڱ��ر�ʱ�����˳���
	*/
	void run();
};