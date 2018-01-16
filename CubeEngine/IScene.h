#pragma once

#include <memory>

/*!
 * Scene接口，用作渲染。
 */
class IScene
{
public:
	/*!
	 * 更新事件，每秒调用大约20次
	 * @param tick 距离上次刷新所经过的秒数
	 * @note 该方法在事件线程中调用而不是渲染线程中
	 */
	virtual void refresh(double tick) = 0;

	//!渲染整个Scene
	virtual void draw() = 0;

	//!虚析构函数
	virtual ~IScene() = default;

	IScene(const IScene&)				= delete;
	IScene(IScene&&)					= delete;
	IScene& operator=(IScene&&)			= delete;
	IScene& operator=(const IScene&)	= delete;
};

//!指向IScene实例的shared ptr
using ISceneObj = std::shared_ptr<IScene>();