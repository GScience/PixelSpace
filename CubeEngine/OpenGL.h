#pragma once

#include <GL/glew.h>
#include "Buffer.h"

//!��OpenGL�ļ򵥷�װ
class OpenGL
{
public:
	//!��Buffer
	static void bindBuffer(const Buffer& buffer)
	{
		glBindBuffer(GL_ARRAY_BUFFER)
	}

}