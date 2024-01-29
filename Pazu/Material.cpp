// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

#include "Material.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

namespace Pazu
{
	void Material::BindTextures()
	{
		if (diffMap)
		{
			noTexture = false;
			diffMap->Bind(0);
		}
		else
		{
			noTexture = true;
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}

	const std::shared_ptr<Shader> &Material::GetShader() const
	{
		return shader;
	}

	const mathfu::vec3 &Material::GetColor() const
	{
		return color;
	}

	const std::shared_ptr<Texture> &Material::GetDiffuseMap() const
	{
		return diffMap;
	}

	const std::shared_ptr<Texture> &Material::GetNormalMap() const
	{
		return normMap;
	}

	const std::shared_ptr<Texture> &Material::GetSpecularMap() const
	{
		return specMap;
	}

	void Material::SetShader(const std::shared_ptr<Shader> &shader)
	{
		this->shader = shader;
	}

	void Material::SetColor(const mathfu::vec3 &color)
	{
		this->color = color;
	}

	void Material::SetDiffuseMap(const std::shared_ptr<Texture> &texture)
	{
		diffMap = texture;

		shader->Use();
		shader->SetInt(shader->uniforms["diff"], 0);
		shader->Unuse();
	}

	void Material::SetNormalMap(const std::shared_ptr<Texture> &texture)
	{
		normMap = texture;
	}

	void Material::SetSpecularMap(const std::shared_ptr<Texture> &texture)
	{
		specMap = texture;
	}
}
