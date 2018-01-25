
#include "OpenGL.h"
#include <stdexcept>

using namespace ogl;

void VertexArrayObj::vertexAttribPointer(
	const ogl::GLuint index, 
	const Buffer& buffer, 
	const GLuint size, 
	const GLenum sType, 
	const GLboolean normalized, 
	const GLsizei stride, 
	const GLvoid* pointer, 
	const char dType,
	const bool autoEnable
) const
{
	bindVertexArray(*this);
	bindBuffer(buffer);

	switch (dType)
	{
	case '\0':
		glVertexAttribPointer(index, size, sType, normalized, stride, pointer);
		break;
	case 'L':
		glVertexAttribLPointer(index, size, sType, stride, pointer);
		break;
	case 'I':
		glVertexAttribIPointer(index, size, sType, stride, pointer);
		break;
	default:
		throw(std::invalid_argument("Unexpected dType"));
	}
	if (autoEnable)
		glEnableVertexAttribArray(index);
}