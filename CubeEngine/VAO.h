#pragma once

#include <GL/glew.h>

/*!顶点数组对象
* 对OpenGL的顶点数组对象进行简单封装
* 不支持多线程，只能在渲染线程即主线程中调用
*/
class VAO
{
	//!构造VAO
	explicit VAO(const GLuint name) :name(name) {}

public:
	//!对象名称
	const GLuint name;

	//!两个Buffer是否一样@param vao 需要比较的vao
	bool equal(const VAO& vao) const
	{
		return vao.name == name;
	}

	//!空Buffer
	static VAO emptyBuffer()
	{
		return VAO(0);
	}

	//!创建Buffer
	static VAO genVAO()
	{
		GLuint name;
		glGenVertexArrays(1, &name);
		return VAO(name);
	}
};