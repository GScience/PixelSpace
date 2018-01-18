
#define _CRT_SECURE_NO_WARNINGS
#include "Shader.h"
#include <iostream>

const char* readShader(const char* fileName)
{
	std::string fullFileName = std::string("resources\\shader\\") + fileName;

	//读取文件
	auto infile = fopen(fullFileName.c_str(), "rb");

	//是否读取
	if (!infile)
		return nullptr;

	//设置读取位置
	fseek(infile, 0, SEEK_END);
	const int len = ftell(infile);
	fseek(infile, 0, SEEK_SET);

	//读取数据
	const auto source = new GLchar[len + 1];

	//读取并关闭
	fread(source, 1, len, infile);
	fclose(infile);

	//最后处理
	source[len] = 0;

	//返回
	return const_cast<const GLchar*>(source);
}

Shader Shader::genShader(ShaderInfo shaders[])
{
	//检测是否为空
	if (shaders == nullptr)
		return Shader(0);;

	//创建着色器程序
	const auto program = glCreateProgram();

	auto entry = shaders;

	//循环编译着色器
	while (entry->type != GL_NONE)
	{
		//创建Shader
		const auto shader = glCreateShader(entry->type);

		//读取Shader代码
		const auto source = readShader(entry->fileName);

		//检测代码是否为空
		if (source == nullptr)
		{
			//删除Shader
			for (entry = shaders; entry->type != GL_NONE; ++entry)
				glDeleteShader(shader);
		}

		//绑定源码
		glShaderSource(shader, 1, &source, nullptr);
		delete[] source;

		//编译源码
		glCompileShader(shader);

		//获取编译状态
		GLint compiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

		//如果编译出错
		if (!compiled)
		{
			//获取错误并输出
			GLsizei len;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

			GLchar* log = new GLchar[len + 1];
			glGetShaderInfoLog(shader, len, &len, log);
			std::cerr << "[ERROR]Shader compilation failed: " << log << std::endl;
			delete[] log;
			throw std::runtime_error("Shader compilation failed");
		}

		//绑定Shader到着色器程序
		glAttachShader(program, shader);

		++entry;
	}
	glLinkProgram(program);

	GLint linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);

	if (!linked)
	{
		GLsizei len;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);

		GLchar* log = new GLchar[len + 1];
		glGetProgramInfoLog(program, len, &len, log);
		std::cerr << "[ERROR]Shader linking failed: " << log << std::endl;
		delete[] log;
		throw std::runtime_error("Shader linking failed");
	}
	glUseProgram(program);

	return Shader(program);
}