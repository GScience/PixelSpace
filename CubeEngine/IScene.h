#pragma once

/*!
Scene�ӿڣ�������Ⱦ��
*/
class IScene
{
public:
	/*!
	�����¼���ÿ����ô�Լ20��
	@param tick �����ϴ�ˢ��������������
	@note �÷������¼��߳��е��ö�������Ⱦ�߳���
	*/
	virtual void refresh(double tick) = 0;

	//!��Ⱦ����Scene
	virtual void draw() = 0;
};