#pragma once

#include <GL/glew.h>
#include "Shader.h"
#include "Buffer.h"
#include "VAO.h"

//!对OpenGL的简单封装
class Ogl
{
	//!构造
	Ogl() = default;

	//!获取实例
	static Ogl& getInstance()
	{
		static Ogl ogl;
		return ogl;
	}

public:
	//!绑定Buffer
	static void bindBuffer(const Buffer& buffer)
	{
		glBindBuffer(buffer.target, buffer.bufferName);
	}

	//!绑定VAO
	static void bindVertexArray(const VAO& vao)
	{
		glBindVertexArray(vao.name);
	}

	//!切换着色器
	static void useShader(const Shader& shader)
	{
		glUseProgram(shader.shaderObj);
	}
};