#pragma once

#include <GL/glew.h>
#include <vector>

//!��OpenGL�ļ򵥷�װ
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

	//!��Buffer
	void bindBuffer(const Buffer& buffer);
	//!��VAO
	void bindVertexArray(const VertexArrayObj& vao);
	//!�л���ɫ��
	void useShader(const Shader& shader);
	/*!����
	 * @param vao �����������
	 * @param mode ����ģʽ\n
	 * mode����������ֵ��\n
	 * GL_POINTS ��\n
	 * GL_LINES ��\n
	 * GL_LINE_STRIP ��������\n
	 * GL_LINE_LOOP ��β��ӵ���������\n
	 * GL_TRIANFLES ������\n
	 * GL_TRIANGLE_STRIP �����δ�\n
	 * GL_TRIANGLE_FAN ��������\n
	 * GL_PATCHES ����ϸ����ɫ��
	 * @param first ��һ�������λ��
	 * @param count �������
	 */
	void drawVertexArray(const VertexArrayObj& vao, GLenum mode, GLuint first, GLuint count);

	/*!��ɫ����
	* ��OpenGL����ɫ�������˼򵥵ķ�װ��
	* ��֧�ֶ��̣߳�ֻ������Ⱦ�̼߳����߳��е���
	*/
	class Shader final
	{
		//!����shader
		explicit Shader(const GLuint shaderObj) :shaderObj(shaderObj) {}
	public:
		//!��ɫ����Ϣ
		struct ShaderInfo
		{
			GLenum       type;
			const char*  fileName;
		};

		//!shader program
		const GLuint shaderObj;

		//!����Shader@param shaders ��ɫ����Ϣ
		static Shader genShader(std::vector<ShaderInfo> shaders);
	};

	/*!�����������
	* ��OpenGL�Ķ������������м򵥷�װ��
	* ��֧�ֶ��̣߳�ֻ������Ⱦ�̼߳����߳��е���
	*/
	class VertexArrayObj final
	{
		//!����VAO
		explicit VertexArrayObj(const GLuint name) :name(name) {}
	public:
		//!��������
		const GLuint name;

		//!����Buffer�Ƿ�һ��@param vao ��Ҫ�Ƚϵ�vao
		bool equal(const VertexArrayObj& vao) const
		{
			return vao.name == name;
		}

		//!��Buffer
		static VertexArrayObj emptyBuffer()
		{
			return VertexArrayObj(0);
		}

		//!����Buffer
		static VertexArrayObj genVertexArrayObj()
		{
			GLuint name;
			glGenVertexArrays(1, &name);
			return VertexArrayObj(name);
		}

		/*!�����ݵ���ɫ���е�����λ��
		 * @param buffer �������ڵĻ�����
		 * @param index ����ɫ���е�����
		 * @param size ÿ����������ݴ�С
		 * @param sType ԭʼ��������
		 * @param normalized �Ƿ���Ҫ���й�һ��
		 * @param stride ÿ����Ԫ��֮��ļ����byte��
		 * @param pointer ��һ��Ԫ�ص�λ��
		 * @param dType Ŀ���������ͣ�L:long��I:int����Ĭ��Ϊ������
		 * @param autoEnable �Ƿ��Զ�����Attrib Array
		 * @note dTypeֻ֧�ָ��㣬�����ͣ����ͣ���֧���������͡�
		 * ��dTypeΪ��ʱĬ��Ϊ�����ͣ���dType�ǿ�ʱnormalizedһ����Ч��
		 * ���dType��Ч�����׳��쳣��
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

	/*!Buffer��
	* ��OpenGL�еĻ����������˼򵥵ķ�װ
	* ��֧�ֶ��̣߳�ֻ������Ⱦ�̼߳����߳��е���
	*/
	class Buffer final
	{
		//!����Buffer
		Buffer(const GLenum target, const GLuint bufferName) :target(target), bufferName(bufferName) {}
	public:
		//!��Ŀ��
		const GLenum target;
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
			return { static_cast<GLenum>(0), 0 };
		}

		/*!����Buffer
		 * @param target ����������\n
		 * ���������Ϳ���Ϊ���������
		 * GL_ARRAY_BUFFER��GL_ELEMENT_ARRAY_BUFFER��GL_COPY_READ_BUFFER �� GL_COPY_WRITE_BUFFER\n
		 * GL_PIXEL_UNPACK_BUFFER �� GL_PIXEL_PACK_BUFFER��GL_DRAW_INDIRECT_BUFFER\n
		 * GL_TEXTURE_BUFFER��GL_TRANSFORM_FEEDBACK_BUFFER��GL_UNIFORM_BUFFER��
		 */
		static Buffer genBuffer(const GLenum target)
		{
			GLuint bufferName;
			glGenBuffers(1, &bufferName);
			return { target, bufferName };
		}

		/*!�������ݵ�buffer
		* @param data ��Ҫ�����Ƶ�����
		* @param size ���ݵĴ�С
		*/
		void copyFrom(void* data, const ogl::GLsizeiptr size) const
		{
			ogl::bindBuffer(*this);
			glBufferData(target, size, data, GL_STATIC_DRAW);
		}

		/*!���ò�������
		 * @param data ��Ҫ�����Ƶ�����
		 * @param size ���ݵĴ�С
		 * @param offset �����ڻ������е�ƫ��
		 * @note ���offset�����˻������󶨵����ݷ�Χ�᷵�ش���
		 */
		void copySubData(void* data, const ogl::GLsizeiptr size, const ogl::GLintptr offset) const
		{
			ogl::bindBuffer(*this);
			glBufferSubData(target, offset, size, data);
		}

		//!��ջ������ڵ�����
		void clear() const
		{
			copyFrom(nullptr, 0);
		}
	};
}