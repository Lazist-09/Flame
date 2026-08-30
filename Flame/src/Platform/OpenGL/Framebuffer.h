#pragma once

#include "Core/Core.h"

#include <cstdint>

namespace Flame
{
	class FL_API Framebuffer
	{
	public:
		Framebuffer(uint32_t width, uint32_t height);
		~Framebuffer();

		void Bind() const;
		void Unbind() const;
		void Resize(uint32_t width, uint32_t height);

		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }
		uint32_t GetColorAttachmentRendererID() const { return m_ColorAttachment; }

	private:
		void Invalidate();
		void Release();

	private:
		uint32_t m_Width = 0;
		uint32_t m_Height = 0;
		uint32_t m_RendererID = 0;
		uint32_t m_ColorAttachment = 0;
		uint32_t m_DepthAttachment = 0;
	};
}
