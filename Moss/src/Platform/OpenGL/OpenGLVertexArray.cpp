#include "mspch.h"
#include "OpenGLVertexArray.h"


#include <glad/glad.h>

namespace Moss {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
		switch (type)
		{
		case Moss::ShaderDataType::Float:				return GL_FLOAT;
		case Moss::ShaderDataType::Float2:			return GL_FLOAT;
		case Moss::ShaderDataType::Float3:			return GL_FLOAT;
		case Moss::ShaderDataType::Float4:			return GL_FLOAT;
		case Moss::ShaderDataType::Mat3:				return GL_FLOAT;
		case Moss::ShaderDataType::Mat4:				return GL_FLOAT;
		case Moss::ShaderDataType::Int:					return GL_INT;
		case Moss::ShaderDataType::Int2:				return GL_INT;
		case Moss::ShaderDataType::Int3:				return GL_INT;
		case Moss::ShaderDataType::Int4:				return GL_INT;
		case Moss::ShaderDataType::Bool:				return GL_BOOL;

		}
		MS_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray() {
		glCreateVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		MS_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_RendererID); 
		vertexBuffer->Bind();
		auto layout = vertexBuffer->GetLayout();
		int index = 0;
		for (auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				element.GetElementComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(), (const void*)element.Offset);
			index++;
		}
		glBindVertexArray(0);
		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();
		glBindVertexArray(0);
		m_IndexBuffers = indexBuffer;
	}

	const std::vector<std::shared_ptr<Moss::VertexBuffer>>& OpenGLVertexArray::GetVertexBuffer() const
	{
		return m_VertexBuffers;
	}

	const std::shared_ptr<Moss::IndexBuffer>& OpenGLVertexArray::GetIndexBuffer() const
	{
		return m_IndexBuffers;
	}

}