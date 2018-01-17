#pragma once

#include <memory>

class IScene;

//!指向IScene实例的shared ptr
using ISceneObj = std::shared_ptr<IScene>;

/*!Scene接口，用作渲染。
 * 一切渲染操作都应在draw方法中，一切事件刷新都应在refresh方法中
 */
class IScene
{
	IScene() = default;

public:
	/*!
	 * 更新事件，每秒调用大约20次
	 * @param tick 距离上次刷新所经过的秒数
	 * @note 该方法在事件线程中调用而不是渲染线程中
	 */
	virtual void refresh(double tick) = 0;

	//!创建一个新的Scene实例，由子类实现
	virtual ISceneObj create() = 0;

	//!渲染整个Scene
	virtual void draw() = 0;

	//!虚析构函数
	virtual ~IScene() = default;

	IScene(const IScene&)				= delete;
	IScene(IScene&&)					= delete;
	IScene& operator=(IScene&&)			= delete;
	IScene& operator=(const IScene&)	= delete;
};