#include "runtime/function/render/opengl/opengl_shader.h"
#include "runtime/function/global/global_context.h"
#include "runtime/resource/config_manager.h"
#include "runtime/resource/asset_manager.h"
#include "runtime/core/timer/timer.h"
#include <fstream>

namespace Toon
{
	namespace Utils 
	{

		static GLenum ShaderTypeFromString(const std::string& type)
		{
			if (type == "vertex")
				return GL_VERTEX_SHADER;
			if (type == "fragment" || type == "pixel")
				return GL_FRAGMENT_SHADER;

			LOG_FATAL(__FUNCTION__, "Unknown shader type!");
			return 0;
		}

		static const char* GLShaderStageToString(GLenum stage)
		{
			switch (stage)
			{
			case GL_VERTEX_SHADER:   return "GL_VERTEX_SHADER";
			case GL_FRAGMENT_SHADER: return "GL_FRAGMENT_SHADER";
			}
			ASSERT(false);
			return nullptr;
		}
	
	}

	OpenGLShader::OpenGLShader(const std::string& filepath)
		: m_FilePath(filepath)
	{

		std::string source = ReadFile(filepath);
		PreProcess(source);

		{
			Timer timer;
			CreateProgram();
			LOG_INFO("Shader creation took {0} ms", timer.ElapsedMillis());
		}

		// Extract name from filepath
		auto lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = filepath.rfind('.');
		auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
		m_Name = filepath.substr(lastSlash, count);
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
		: m_Name(name)
	{
		m_OpenGLSourceCode[GL_VERTEX_SHADER] = vertexSrc;
		m_OpenGLSourceCode[GL_FRAGMENT_SHADER] = fragmentSrc;
		CreateProgram();
	}

	OpenGLShader::~OpenGLShader()
	{
		GL_CALL(glDeleteProgram(m_RendererID));
	}

	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary); // ifstream closes itself due to RAII
		if (in)
		{
			in.seekg(0, std::ios::end);
			size_t size = in.tellg();
			if (size != -1)
			{
				result.resize(size);
				in.seekg(0, std::ios::beg);
				in.read(&result[0], size);
			}
			else
			{
				LOG_ERROR("Could not read from file '{0}'", filepath);
			}
		}
		else
		{
			LOG_ERROR("Could not open file '{0}'", filepath);
		}

		return std::move(result);
	}

	void OpenGLShader::PreProcess(const std::string& source)
	{
		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0); //Start of shader type declaration line
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos); //End of shader type declaration line
			CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLength + 1; //Start of shader type name (after "#type " keyword)
			std::string type = source.substr(begin, eol - begin);
			CORE_ASSERT(Utils::ShaderTypeFromString(type), "Invalid shader type specified");
			size_t nextLinePos = source.find_first_not_of("\r\n", eol); //Start of shader code after shader type declaration line
			CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");
			pos = source.find(typeToken, nextLinePos); //Start of next shader type declaration line
			m_OpenGLSourceCode[Utils::ShaderTypeFromString(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
		}

	}

	void OpenGLShader::CreateProgram()
	{
		GLuint program = GL_CALL(glCreateProgram());

		std::vector<GLuint> shaderIDs;
		for (auto&& [stage, source] : m_OpenGLSourceCode)
		{
			GLuint shaderID = GL_CALL(glCreateShader(stage));
			shaderIDs.push_back(shaderID);
			const char* shaderSource = source.c_str();
			GL_CALL(glShaderSource(shaderID, 1, &shaderSource, NULL));
			GL_CALL(glCompileShader(shaderID));

			GLint isSuccess;
			GL_CALL(glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isSuccess));
			if (isSuccess == GL_FALSE)
			{
				GLint maxLength;
				GL_CALL(glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength));
				std::vector<GLchar> infoLog(maxLength);
				GL_CALL(glGetShaderInfoLog(shaderID, maxLength, NULL, infoLog.data()));
				LOG_ERROR("Shader Compile Errpr failed ({0}):\n{1}", m_FilePath, infoLog.data());
			}
			else
			{
				GL_CALL(glAttachShader(program, shaderID));
			}
		}


		GL_CALL(glLinkProgram(program));
	
		GLint isLinked;
		GL_CALL(glGetProgramiv(program, GL_LINK_STATUS, &isLinked));
		if (isLinked == GL_FALSE)
		{
			GLint maxLength;
			GL_CALL(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength));

			std::vector<GLchar> infoLog(maxLength);
			GL_CALL(glGetProgramInfoLog(program, maxLength, &maxLength, infoLog.data()));
			LOG_ERROR("Shader linking failed ({0}):\n{1}", m_FilePath, infoLog.data());

			GL_CALL(glDeleteProgram(program));

			for (auto id : shaderIDs)
				GL_CALL(glDeleteShader(id));
		}

		for (auto id : shaderIDs)
		{
			GL_CALL(glDetachShader(program, id));
			GL_CALL(glDeleteShader(id));
		}

		m_RendererID = program;
	}

	void OpenGLShader::Bind() const
	{
		GL_CALL(glUseProgram(m_RendererID));
	}

	void OpenGLShader::Unbind() const
	{
		GL_CALL(glUseProgram(0));
	}

	void OpenGLShader::SetInt(const std::string& name, int value)
	{
		UploadUniformInt(name, value);
	}

	void OpenGLShader::SetIntArray(const std::string& name, int* values, uint32_t count)
	{
		UploadUniformIntArray(name, values, count);
	}

	void OpenGLShader::SetFloat(const std::string& name, float value)
	{
		UploadUniformFloat(name, value);
	}

	void OpenGLShader::SetFloat2(const std::string& name, const Vector2& value)
	{
		UploadUniformFloat2(name, value);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const Vector3& value)
	{
		UploadUniformFloat3(name, value);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const Vector4& value)
	{
		UploadUniformFloat4(name, value);
	}

	void OpenGLShader::SetMat3(const std::string& name, const Matrix3x3& value)
	{
		UploadUniformMat3(name, value);
	}

	void OpenGLShader::SetMat4(const std::string& name, const Matrix4x4& value)
	{
		UploadUniformMat4(name, value);
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformIntArray(const std::string& name, int* values, uint32_t count)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1iv(location, count, values);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const Vector2& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const Vector3& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const Vector4& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const Matrix3x3& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_TRUE, matrix.data());
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const Matrix4x4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_TRUE, matrix.data());
	}	
}