#pragma once

#include <GL/glew.h>

/*!�����������
* ��OpenGL�Ķ������������м򵥷�װ
* ��֧�ֶ��̣߳�ֻ������Ⱦ�̼߳����߳��е���
*/
class VAO
{
	//!����VAO
	explicit VAO(const GLuint name) :name(name) {}

public:
	//!��������
	const GLuint name;

	//!����Buffer�Ƿ�һ��@param vao ��Ҫ�Ƚϵ�vao
	bool equal(const VAO& vao) const
	{
		return vao.name == name;
	}

	//!��Buffer
	static VAO emptyBuffer()
	{
		return VAO(0);
	}

	//!����Buffer
	static VAO genVAO()
	{
		GLuint name;
		glGenVertexArrays(1, &name);
		return VAO(name);
	}
};