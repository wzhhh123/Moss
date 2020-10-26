#pragma once




#include "Moss/Renderer/Buffer.h"

namespace Moss {

	class VertexArray {

	public:
		virtual ~VertexArray();

		virtual void Bind()const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Moss::Ref<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const Moss::Ref<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<Moss::Ref<VertexBuffer>>&GetVertexBuffer() const = 0;
		virtual const Moss::Ref<IndexBuffer>&GetIndexBuffer() const = 0;

		static VertexArray* Create();
	};

}