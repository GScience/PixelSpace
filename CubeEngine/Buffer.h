#pragma once

#include <GL/glew.h>

/*!��������Ŀ��
 * ��OpenGL�л�������Ŀ��һ��
 */
enum BufferTarget
{
	UnknownBuffer = -1,
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
	//!��Ŀ��
	const BufferTarget target;
	//!����������
	const GLuint bufferName;

	//!����Buffer�Ƿ�һ��@param buffer ��Ҫ�Ƚϵ�Buffer
	bool equal(const Buffer& buffer) const
	{
		return buffer.bufferName == bufferName && 
			buffer.target == target;
	}
	
	//!��Buffer
	static Buffer emptyBuffer()
	{
		return { UnknownBuffer, 0 };
	}

	//!����Buffer
	static Buffer genBuffer(const BufferTarget target)
	{
		GLuint bufferName;
		glGenBuffers(1, &bufferName);
		return { target, bufferName };
	}

	/*!�������ݵ�buffer
	 * @param data ��Ҫ�����Ƶ�����
	 * @param size ���ݵĴ�С
	 * @note dataӦ��
	 */
	void copyFrom(void* data, const size_t size) const
	{
		glBindBuffer(target, bufferName);
		glBufferData(target, size, data, GL_STATIC_DRAW);
	}

	//!��ջ������ڵ�����
	void clear();
};