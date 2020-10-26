#pragma once


#include "Moss/Renderer/VertexArray.h"

namespace Moss {

	class OpenGLVertexArray : public VertexArray
	{
	public:

		OpenGLVertexArray();

		virtual ~OpenGLVertexArray();

		virtual void Bind()const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const Moss::Ref<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Moss::Ref<IndexBuffer>& indexBuffer) override;


		virtual const std::vector<Moss::Ref<VertexBuffer>>&GetVertexBuffer() const override;
		virtual const Moss::Ref<IndexBuffer>&GetIndexBuffer() const override;


	private:

		uint32_t m_RendererID;

		std::vector<Moss::Ref<VertexBuffer>>m_VertexBuffers;
		Moss::Ref<IndexBuffer>m_IndexBuffers;
	};

}
