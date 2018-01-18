#pragma once

#include <GL/glew.h>

//!��ɫ����Ϣ
struct ShaderInfo
{
	GLenum       type;
	const char*  fileName;
};

/*!��ɫ����
 * ��OpenGL����ɫ�������˼򵥵ķ�װ
 * ��֧�ֶ��̣߳�ֻ������Ⱦ�̼߳����߳��е���
 */
class Shader final
{
	//!����shader
	explicit Shader(const GLuint shaderObj) :shaderObj(shaderObj) {}

public:
	//!shader program
	const GLuint shaderObj;

	//!����Shader@param shaders ��ɫ����Ϣ
	static Shader genShader(ShaderInfo shaders[]);
};