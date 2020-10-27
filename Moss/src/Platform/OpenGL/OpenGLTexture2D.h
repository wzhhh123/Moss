#pragma once
#include "Moss/Renderer/Texture.h"

namespace Moss {

	class OpenGLTexture2D : public Texture2D
	{
	public:
		virtual ~OpenGLTexture2D();

		OpenGLTexture2D(const std::string& path);
		uint32_t GetWidth() const override;
		uint32_t GetHeight() const override;
		void Bind(uint32_t slot = 0) const override;


	private:
		std::string m_Path;
		int m_Height;
		int m_Width;
		uint32_t m_RendererID; //maybe program id
	};

}

