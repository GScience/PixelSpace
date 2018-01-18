#pragma once

#include <GL/glew.h>

/*!缓冲区绑定目标
 * 与OpenGL中缓冲区绑定目标一致
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

/*!Buffer类
 * 对OpenGL中的缓冲区进行了简单的封装
 * 不支持多线程，只能在渲染线程即主线程中调用
 */
class Buffer final
{
	//!构造Buffer
	Buffer(const BufferTarget target, const GLuint bufferName) :target(target), bufferName(bufferName) {}

public:
	//!绑定目标
	const BufferTarget target;
	//!缓冲区名称
	const GLuint bufferName;

	//!两个Buffer是否一样@param buffer 需要比较的Buffer
	bool equal(const Buffer& buffer) const
	{
		return buffer.bufferName == bufferName && 
			buffer.target == target;
	}
	
	//!空Buffer
	static Buffer emptyBuffer()
	{
		return { UnknownBuffer, 0 };
	}

	//!创建Buffer
	static Buffer genBuffer(const BufferTarget target)
	{
		GLuint bufferName;
		glGenBuffers(1, &bufferName);
		return { target, bufferName };
	}

	/*!复制数据到buffer
	 * @param data 需要被复制的数据
	 * @param size 数据的大小
	 * @note data应由
	 */
	void copyFrom(void* data, const size_t size) const
	{
		glBindBuffer(target, bufferName);
		glBufferData(target, size, data, GL_STATIC_DRAW);
	}

	//!清空缓冲区内的数据
	void clear();
};