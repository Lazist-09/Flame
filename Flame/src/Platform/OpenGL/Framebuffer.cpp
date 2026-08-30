#include "flpch.h"
#include "Framebuffer.h"

#include <glad/glad.h>

namespace Flame
{
	Framebuffer::Framebuffer(uint32_t width, uint32_t height)
		: m_Width(width), m_Height(height)
	{
		Invalidate();
	}

	Framebuffer::~Framebuffer()
	{
		Release();
	}

	void Framebuffer::Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		glViewport(0, 0, static_cast<GLsizei>(m_Width), static_cast<GLsizei>(m_Height));
	}

	void Framebuffer::Unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Framebuffer::Resize(uint32_t width, uint32_t height)
	{
		if (width == 0 || height == 0 || (width == m_Width && height == m_Height))
			return;

		m_Width = width;
		m_Height = height;
		Invalidate();
	}

	void Framebuffer::Invalidate()
	{
		Release();

		glGenFramebuffers(1, &m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

		glGenTextures(1, &m_ColorAttachment);
		glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, static_cast<GLsizei>(m_Width), static_cast<GLsizei>(m_Height), 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);

		glGenRenderbuffers(1, &m_DepthAttachment);
		glBindRenderbuffer(GL_RENDERBUFFER, m_DepthAttachment);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, static_cast<GLsizei>(m_Width), static_cast<GLsizei>(m_Height));
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_DepthAttachment);

		FL_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Framebuffer::Release()
	{
		if (m_DepthAttachment)
		{
			glDeleteRenderbuffers(1, &m_DepthAttachment);
			m_DepthAttachment = 0;
		}

		if (m_ColorAttachment)
		{
			glDeleteTextures(1, &m_ColorAttachment);
			m_ColorAttachment = 0;
		}

		if (m_RendererID)
		{
			glDeleteFramebuffers(1, &m_RendererID);
			m_RendererID = 0;
		}
	}
}
