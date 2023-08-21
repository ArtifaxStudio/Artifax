#pragma once

#include "Artifax/Renderer/Shader.h"
#include <glm/glm.hpp>

//TODO: Remove it when abstracting more
typedef unsigned int GLenum;

namespace Artifax
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		~OpenGLShader();

		void Bind() const;
		void Unbind() const;

		virtual const std::string& GetName() const override { return m_Name; }

		void UploadUniformInt(const std::string& name, const int& value);

		void UploadUniformFloat1(const std::string& name, const float& value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	private:
		std::unordered_map<GLenum, std::string> SourcesFromFile(const std::string& filepath);
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum,std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
	private:
		uint32_t m_RendererID;
		std::string m_Name;
	};
}