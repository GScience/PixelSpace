#pragma once

#include <GL/glew.h>
#include "Buffer.h"

//!对OpenGL的简单封装
class OpenGL
{
public:
	//!绑定Buffer
	static void bindBuffer(const Buffer& buffer)
	{
		glBindBuffer(GL_ARRAY_BUFFER)
	}

}