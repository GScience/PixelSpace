#pragma once

#include <memory>

/*!
 * Scene�ӿڣ�������Ⱦ��
 */
class IScene
{
public:
	/*!
	 * �����¼���ÿ����ô�Լ20��
	 * @param tick �����ϴ�ˢ��������������
	 * @note �÷������¼��߳��е��ö�������Ⱦ�߳���
	 */
	virtual void refresh(double tick) = 0;

	//!��Ⱦ����Scene
	virtual void draw() = 0;

	//!����������
	virtual ~IScene() = default;

	IScene(const IScene&)				= delete;
	IScene(IScene&&)					= delete;
	IScene& operator=(IScene&&)			= delete;
	IScene& operator=(const IScene&)	= delete;
};

//!ָ��ISceneʵ����shared ptr
using ISceneObj = std::shared_ptr<IScene>();