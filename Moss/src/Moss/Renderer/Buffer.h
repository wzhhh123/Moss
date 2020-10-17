#pragma once

namespace Moss {


	enum class ShaderDataType : uint8_t
	{
		None = 0,
		Float,
		Float2,
		Float3,
		Float4,
		Mat3,
		Mat4,
		Int,
		Int2,
		Int3,
		Int4,
		Bool,
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type) {
		switch (type)
		{
		case Moss::ShaderDataType::None:        return 0;
		case Moss::ShaderDataType::Float:	        return 4;
		case Moss::ShaderDataType::Float2:       return 4 * 2;
		case Moss::ShaderDataType::Float3:       return 4 * 3;
		case Moss::ShaderDataType::Float4:	    return 4 * 4;
		case Moss::ShaderDataType::Mat3:        return 4 * 3 * 3;
		case Moss::ShaderDataType::Mat4:	        return 4 * 4 * 4;
		case Moss::ShaderDataType::Int:			    return 4;
		case Moss::ShaderDataType::Int2:          return 4 * 2;
		case Moss::ShaderDataType::Int3:          return 4 * 3;
		case Moss::ShaderDataType::Int4:          return 4 * 4;
		case Moss::ShaderDataType::Bool:         return 1;
		}
		MS_CORE_ASSERT(false, "Unknow ShaderDataType!");
		return 0;
	}

	struct  BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		uint32_t Offset;
		uint32_t Size;
		bool Normalized;

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false) :
			Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized) {
		}


		uint32_t GetElementComponentCount() {
			switch (Type)
			{
			case Moss::ShaderDataType::Float:	        return 1;
			case Moss::ShaderDataType::Float2:       return 2;
			case Moss::ShaderDataType::Float3:       return 3;
			case Moss::ShaderDataType::Float4:	    return 4;
			case Moss::ShaderDataType::Mat3:        return 3 * 3;
			case Moss::ShaderDataType::Mat4:	        return 4 * 4;
			case Moss::ShaderDataType::Int:			    return 1;
			case Moss::ShaderDataType::Int2:          return 2;
			case Moss::ShaderDataType::Int3:          return 3;
			case Moss::ShaderDataType::Int4:          return 4;
			case Moss::ShaderDataType::Bool:         return 1;
			case Moss::ShaderDataType::None:        return 0;
			}

			MS_CORE_ASSERT(false, "Unknow ShaderDataType!");
			return 0;
		}
	};

	class BufferLayout {
	public:
		BufferLayout(){}
		//BufferLayout(std::vector<BufferElement> elements) :m_Elements(elements) {}
		BufferLayout(const std::initializer_list<BufferElement> &elements) :m_Elements(elements) {
			CalculateOffsetsAndStride();
		}
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }

		inline uint32_t GetStride() const { return m_Stride; }
	private:
		void CalculateOffsetsAndStride() {
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements) {
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}
	private:
		uint32_t m_Stride = 0;
		std::vector<BufferElement> m_Elements;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size);
	};


	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* vertices, uint32_t size);
	};

}
