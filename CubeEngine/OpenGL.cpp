
#include "OpenGL.h"

using namespace ogl;

void ogl::bindBuffer(const Buffer& buffer)
{
	glBindBuffer(buffer.target, buffer.bufferName);
}

void ogl::bindVertexArray(const VertexArrayObj& vao)
{
	glBindVertexArray(vao.name);
}

void ogl::useShader(const Shader& shader)
{
	glUseProgram(shader.shaderObj);
}

void ogl::drawVertexArray(const VertexArrayObj& vao, const GLenum mode, const GLuint first, const GLuint count)
{
	glDrawArrays(mode, first, count);
}