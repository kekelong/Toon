#pragma once
#include "runtime/core/base/error.h"
#include "runtime/core/math/math_headers.h"
#include "runtime/function/render/opengl/interface/rhi_shader.h"
#include <unordered_map>
#include <string>

namespace Toon
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetInt(const std::string& name, int value) override;
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) override;
		virtual void SetFloat(const std::string& name, float value) override;
		virtual void SetFloat2(const std::string& name, const Vector2& value) override;
		virtual void SetFloat3(const std::string& name, const Vector3& value) override;
		virtual void SetFloat4(const std::string& name, const Vector4& value) override;
		virtual void SetMat3(const std::string& name, const Matrix3x3& value) override;
		virtual void SetMat4(const std::string& name, const Matrix4x4& value) override;

		const std::string& GetName() const { return m_Name; }

		void UploadUniformInt(const std::string& name, int value);
		void UploadUniformIntArray(const std::string& name, int* values, uint32_t count);

		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const Vector2& value);
		void UploadUniformFloat3(const std::string& name, const Vector3& value);
		void UploadUniformFloat4(const std::string& name, const Vector4& value);

		void UploadUniformMat3(const std::string& name, const Matrix3x3& matrix);
		void UploadUniformMat4(const std::string& name, const Matrix4x4& matrix);
	private:
		std::string ReadFile(const std::string& filepath);
		void PreProcess(const std::string& source);

		void CreateProgram();
	private:
		uint32_t m_RendererID;
		std::string m_FilePath;
		std::string m_Name;
		std::unordered_map<GLenum, std::string> m_OpenGLSourceCode;
	};

}