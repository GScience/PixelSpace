#pragma once

#include <GL/glew.h>
#include <vector>

//!对OpenGL的简单封装
namespace ogl
{
	using GLenum = GLenum;
	using GLbitfield = GLbitfield;
	using GLuint = GLuint;
	using GLint = GLint;
	using GLsizei = GLsizei;
	using GLboolean = GLboolean;
	using GLbyte = GLbyte;
	using GLshort = GLshort;
	using GLubyte = GLubyte;
	using GLushort = GLushort;
	using GLulong = GLulong;
	using GLfloat = GLfloat;
	using GLclampf = GLclampf;
	using GLdouble = GLdouble;
	using GLclampd = GLclampd;
	using GLvoid = GLvoid;
	using GLint64EXT = GLint64EXT;
	using GLuint64EXT = GLuint64EXT;
	using GLint64 = GLint64;
	using GLuint64 = GLuint64;
	using GLchar = GLchar;
	using GLintptr = GLintptr;
	using GLsizeiptr = GLsizeiptr;
	class Shader;
	class Buffer;
	class VertexArrayObj;

	//!绑定Buffer
	void bindBuffer(const Buffer& buffer);
	//!绑定VAO
	void bindVertexArray(const VertexArrayObj& vao);
	//!切换着色器
	void useShader(const Shader& shader);
	/*!绘制
	 * @param vao 顶点数组对象
	 * @param mode 绘制模式\n
	 * mode可以是以下值：\n
	 * GL_POINTS 点\n
	 * GL_LINES 线\n
	 * GL_LINE_STRIP 连续的线\n
	 * GL_LINE_LOOP 首尾相接的连续的线\n
	 * GL_TRIANFLES 三角形\n
	 * GL_TRIANGLE_STRIP 三角形带\n
	 * GL_TRIANGLE_FAN 三角形扇\n
	 * GL_PATCHES 用于细分着色器
	 * @param first 第一个顶点的位置
	 * @param count 顶点个数
	 */
	void drawVertexArray(const VertexArrayObj& vao, GLenum mode, GLuint first, GLuint count);

	/*!着色器类
	* 对OpenGL的着色器进行了简单的封装，
	* 不支持多线程，只能在渲染线程即主线程中调用
	*/
	class Shader final
	{
		//!构造shader
		explicit Shader(const GLuint shaderObj) :shaderObj(shaderObj) {}
	public:
		//!着色器信息
		struct ShaderInfo
		{
			GLenum       type;
			const char*  fileName;
		};

		//!shader program
		const GLuint shaderObj;

		//!创建Shader@param shaders 着色器信息
		static Shader genShader(std::vector<ShaderInfo> shaders);
	};

	/*!顶点数组对象
	* 对OpenGL的顶点数组对象进行简单封装，
	* 不支持多线程，只能在渲染线程即主线程中调用
	*/
	class VertexArrayObj final
	{
		//!构造VAO
		explicit VertexArrayObj(const GLuint name) :name(name) {}
	public:
		//!对象名称
		const GLuint name;

		//!两个Buffer是否一样@param vao 需要比较的vao
		bool equal(const VertexArrayObj& vao) const
		{
			return vao.name == name;
		}

		//!空Buffer
		static VertexArrayObj emptyBuffer()
		{
			return VertexArrayObj(0);
		}

		//!创建Buffer
		static VertexArrayObj genVertexArrayObj()
		{
			GLuint name;
			glGenVertexArrays(1, &name);
			return VertexArrayObj(name);
		}

		/*!绑定数据到着色器中的属性位置
		 * @param buffer 数据所在的缓冲区
		 * @param index 在着色器中的索引
		 * @param size 每个顶点的数据大小
		 * @param sType 原始数据类型
		 * @param normalized 是否需要进行归一化
		 * @param stride 每两个元素之间的间隔（byte）
		 * @param pointer 第一个元素的位置
		 * @param dType 目标数据类型（L:long，I:int），默认为浮点型
		 * @param autoEnable 是否自动启用Attrib Array
		 * @note dType只支持浮点，长整型，整型，不支持其他类型。
		 * 当dType为空时默认为浮点型，当dType非空时normalized一项无效。
		 * 如果dType无效，会抛出异常。
		 */
		void vertexAttribPointer(
			GLuint index, 
			const Buffer& buffer, 
			GLuint size, 
			GLenum sType, 
			GLboolean normalized, 
			GLsizei stride, 
			const GLvoid* pointer, 
			char dType = '\0',
			bool autoEnable = true
		) const;
	};

	/*!Buffer类
	* 对OpenGL中的缓冲区进行了简单的封装
	* 不支持多线程，只能在渲染线程即主线程中调用
	*/
	class Buffer final
	{
		//!构造Buffer
		Buffer(const GLenum target, const GLuint bufferName) :target(target), bufferName(bufferName) {}
	public:
		//!绑定目标
		const GLenum target;
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
			return { static_cast<GLenum>(0), 0 };
		}

		/*!创建Buffer
		 * @param target 缓冲区类型\n
		 * 缓冲区类型可能为以下情况：
		 * GL_ARRAY_BUFFER，GL_ELEMENT_ARRAY_BUFFER，GL_COPY_READ_BUFFER 和 GL_COPY_WRITE_BUFFER\n
		 * GL_PIXEL_UNPACK_BUFFER 和 GL_PIXEL_PACK_BUFFER，GL_DRAW_INDIRECT_BUFFER\n
		 * GL_TEXTURE_BUFFER，GL_TRANSFORM_FEEDBACK_BUFFER，GL_UNIFORM_BUFFER等
		 */
		static Buffer genBuffer(const GLenum target)
		{
			GLuint bufferName;
			glGenBuffers(1, &bufferName);
			return { target, bufferName };
		}

		/*!复制数据到buffer
		* @param data 需要被复制的数据
		* @param size 数据的大小
		*/
		void copyFrom(void* data, const ogl::GLsizeiptr size) const
		{
			ogl::bindBuffer(*this);
			glBufferData(target, size, data, GL_STATIC_DRAW);
		}

		/*!设置部分数据
		 * @param data 需要被复制的数据
		 * @param size 数据的大小
		 * @param offset 数据在缓冲区中的偏移
		 * @note 如果offset超过了缓存对象绑定的数据范围会返回错误
		 */
		void copySubData(void* data, const ogl::GLsizeiptr size, const ogl::GLintptr offset) const
		{
			ogl::bindBuffer(*this);
			glBufferSubData(target, offset, size, data);
		}

		//!清空缓冲区内的数据
		void clear() const
		{
			copyFrom(nullptr, 0);
		}
	};
}