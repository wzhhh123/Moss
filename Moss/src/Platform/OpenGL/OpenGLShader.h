#pragma once
#include "Moss/Renderer/Shader.h"


namespace Moss {

	class OpenGLShader : public Shader
	{

	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& shaderSrc);

		virtual void Bind() const override;
		virtual void Unbind() const override;

		~OpenGLShader();

		void UploadUniformMat4(const std::string&name, const glm::mat4& matrix);
		void UploadUniformMat3(const std::string&name, const glm::mat3& matrix);

		void UploadUniformFloat4(const std::string& name, const glm::vec4& value);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformInt(const std::string& name, int value);

	private:
		uint32_t m_RendererID; //maybe program id

	};
}

