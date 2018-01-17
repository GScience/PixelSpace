#pragma once

#include <GL/glew.h>

/*!��������Ŀ��
 * ��OpenGL�л�������Ŀ��һ��
 */
enum BufferTarget
{
	ArrayBuffer = GL_ARRAY_BUFFER,
	CopyReadBuffer = GL_COPY_READ_BUFFER,
	CopyWriteBuffer = GL_COPY_WRITE_BUFFER,
	DrawIndirectBuffer = GL_DRAW_INDIRECT_BUFFER,
	ElementArraybuffer = GL_ELEMENT_ARRAY_BUFFER,
	PixelPackBuffer = GL_PIXEL_PACK_BUFFER,
	PixelUnpackBuffer = GL_PIXEL_UNPACK_BUFFER,
	TextureBuffer = GL_TEXTURE_BUFFER,
	TransformFeedbackBuffer = GL_TRANSFORM_FEEDBACK_BUFFER,
	UniformBuffer = GL_UNIFORM_BUFFER
};

/*!Buffer��
 * ��OpenGL�еĻ����������˼򵥵ķ�װ
 * ��֧�ֶ��̣߳�ֻ������Ⱦ�̼߳����߳��е���
 */
class Buffer final
{
	//!����Buffer
	Buffer(const BufferTarget target, const GLuint bufferName) :target(target), bufferName(bufferName) {}

public:
	//!����Buffer
	static Buffer genBuffer(const BufferTarget target)
	{
		GLuint bufferName;
		glGenBuffers(1, &bufferName);
		return { target, bufferName };
	}

	//!��Ŀ��
	const BufferTarget target;

	//!����������
	const GLuint bufferName;

	/*!�������ݵ�buffer
	 * @param data ��Ҫ�����Ƶ�����
	 * @param size ���ݵĴ�С
	 * @note dataӦ��
	 */
	void copyFrom(void* data, size_t size);

	//!��ջ������ڵ�����
	void clear();
};