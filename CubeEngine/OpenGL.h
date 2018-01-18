#pragma once

#include <GL/glew.h>
#include "Shader.h"
#include "Buffer.h"
#include "VAO.h"

//!��OpenGL�ļ򵥷�װ
class Ogl
{
	//!����
	Ogl() = default;

	//!��ȡʵ��
	static Ogl& getInstance()
	{
		static Ogl ogl;
		return ogl;
	}

public:
	//!��Buffer
	static void bindBuffer(const Buffer& buffer)
	{
		glBindBuffer(buffer.target, buffer.bufferName);
	}

	//!��VAO
	static void bindVertexArray(const VAO& vao)
	{
		glBindVertexArray(vao.name);
	}

	//!�л���ɫ��
	static void useShader(const Shader& shader)
	{
		glUseProgram(shader.shaderObj);
	}
};