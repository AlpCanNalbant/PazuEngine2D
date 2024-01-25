#include "Texture.hpp"

namespace Pazu
{
	Texture::~Texture()
	{
		glDeleteTextures(1, &texID);
	}

	void Texture::Bind(GLint index)
	{
		glActiveTexture(GL_TEXTURE0 + index);
		glBindTexture(GL_TEXTURE_2D, texID);
	}

	mathfu::vec2i Texture::GetSize()
	{
		return {width, height};
	}

	/*
	GLint Texture::GetRgb(int x, int y)
	{
		return rgbData[(y * width + x) * channels];
	}
	*/
}
