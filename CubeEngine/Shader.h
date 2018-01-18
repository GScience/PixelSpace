#pragma once

#include <GL/glew.h>

//!着色器信息
struct ShaderInfo
{
	GLenum       type;
	const char*  fileName;
};

/*!着色器类
 * 对OpenGL的着色器进行了简单的封装
 * 不支持多线程，只能在渲染线程即主线程中调用
 */
class Shader final
{
	//!构造shader
	explicit Shader(const GLuint shaderObj) :shaderObj(shaderObj) {}

public:
	//!shader program
	const GLuint shaderObj;

	//!创建Shader@param shaders 着色器信息
	static Shader genShader(ShaderInfo shaders[]);
};