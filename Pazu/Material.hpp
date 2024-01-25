#pragma once
#include <vector>
#include <memory>
#include "mathfu/glsl_mappings.h"

namespace Pazu
{
	class Shader;
	class Texture;

	class Material
	{
	public:
		void BindTextures();
		const std::shared_ptr<Shader> &GetShader() const;
		const mathfu::vec3 &GetColor() const;
		const std::shared_ptr<Texture> &GetDiffuseMap() const;
		const std::shared_ptr<Texture> &GetNormalMap() const;
		const std::shared_ptr<Texture> &GetSpecularMap() const;
		void SetShader(const std::shared_ptr<Shader> &shader);
		void SetColor(const mathfu::vec3 &color);
		void SetDiffuseMap(const std::shared_ptr<Texture> &texture);
		void SetNormalMap(const std::shared_ptr<Texture> &texture);
		void SetSpecularMap(const std::shared_ptr<Texture> &texture);

		std::shared_ptr<Shader> shader;
		mathfu::vec3 color{1.0f};
		bool noTexture{true};

	private:
		std::shared_ptr<Texture> diffMap;
		std::shared_ptr<Texture> normMap;
		std::shared_ptr<Texture> specMap;
	};
}
