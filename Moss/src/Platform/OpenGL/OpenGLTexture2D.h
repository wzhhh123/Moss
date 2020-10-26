#pragma once
#include "Moss/Renderer/Texture.h"

namespace Moss {

	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path) {

		}

		virtual ~OpenGLTexture2D() {}

		uint32_t GetWidth() const override;

		uint32_t GetHeight() const override;
 
		void Bind() const override;


	private:
		std::string m_Path;
		int m_Height;
		int m_Width;
	};

}

