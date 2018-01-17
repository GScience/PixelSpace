#pragma once

#include <memory>

class IScene;

//!ָ��ISceneʵ����shared ptr
using ISceneObj = std::shared_ptr<IScene>;

/*!Scene�ӿڣ�������Ⱦ��
 * һ����Ⱦ������Ӧ��draw�����У�һ���¼�ˢ�¶�Ӧ��refresh������
 */
class IScene
{
	IScene() = default;

public:
	/*!
	 * �����¼���ÿ����ô�Լ20��
	 * @param tick �����ϴ�ˢ��������������
	 * @note �÷������¼��߳��е��ö�������Ⱦ�߳���
	 */
	virtual void refresh(double tick) = 0;

	//!����һ���µ�Sceneʵ����������ʵ��
	virtual ISceneObj create() = 0;

	//!��Ⱦ����Scene
	virtual void draw() = 0;

	//!����������
	virtual ~IScene() = default;

	IScene(const IScene&)				= delete;
	IScene(IScene&&)					= delete;
	IScene& operator=(IScene&&)			= delete;
	IScene& operator=(const IScene&)	= delete;
};