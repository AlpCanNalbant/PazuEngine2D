#pragma once
#include "GL/glew.h"
#include "mathfu/glsl_mappings.h"
#include "Resource.hpp"

namespace Pazu
{
	class Texture final : public Resource
	{
	public:
		Texture() = default;
		~Texture();
		Texture(const Texture &) = default;
		Texture(Texture &&) = default;
		Texture &operator=(const Texture &) = default;
		Texture &operator=(Texture &&) = default;
		void Bind(GLint index);
		mathfu::vec2i GetSize();
		// GLint GetRgb(int x, int y);

		// GLuint rgbData;
		GLuint texID;
		GLint width, height;
	};
}
