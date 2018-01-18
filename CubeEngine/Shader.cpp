
#define _CRT_SECURE_NO_WARNINGS
#include "Shader.h"
#include <iostream>

const char* readShader(const char* fileName)
{
	std::string fullFileName = std::string("resources\\shader\\") + fileName;

	//��ȡ�ļ�
	auto infile = fopen(fullFileName.c_str(), "rb");

	//�Ƿ��ȡ
	if (!infile)
		return nullptr;

	//���ö�ȡλ��
	fseek(infile, 0, SEEK_END);
	const int len = ftell(infile);
	fseek(infile, 0, SEEK_SET);

	//��ȡ����
	const auto source = new GLchar[len + 1];

	//��ȡ���ر�
	fread(source, 1, len, infile);
	fclose(infile);

	//�����
	source[len] = 0;

	//����
	return const_cast<const GLchar*>(source);
}

Shader Shader::genShader(ShaderInfo shaders[])
{
	//����Ƿ�Ϊ��
	if (shaders == nullptr)
		return Shader(0);;

	//������ɫ������
	const auto program = glCreateProgram();

	auto entry = shaders;

	//ѭ��������ɫ��
	while (entry->type != GL_NONE)
	{
		//����Shader
		const auto shader = glCreateShader(entry->type);

		//��ȡShader����
		const auto source = readShader(entry->fileName);

		//�������Ƿ�Ϊ��
		if (source == nullptr)
		{
			//ɾ��Shader
			for (entry = shaders; entry->type != GL_NONE; ++entry)
				glDeleteShader(shader);
		}

		//��Դ��
		glShaderSource(shader, 1, &source, nullptr);
		delete[] source;

		//����Դ��
		glCompileShader(shader);

		//��ȡ����״̬
		GLint compiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

		//����������
		if (!compiled)
		{
			//��ȡ�������
			GLsizei len;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

			GLchar* log = new GLchar[len + 1];
			glGetShaderInfoLog(shader, len, &len, log);
			std::cerr << "[ERROR]Shader compilation failed: " << log << std::endl;
			delete[] log;
			throw std::runtime_error("Shader compilation failed");
		}

		//��Shader����ɫ������
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