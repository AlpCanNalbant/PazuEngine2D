#pragma once
#include <GL\glew.h>
#include "Entity.hpp"

namespace Pazu
{
	class Material;
	class Camera;

	class Sprite : public Entity
	{
	public:
		Sprite();
		Sprite(const mathfu::vec2 &pos, float rot = 0.0f, const mathfu::vec2 &scale = {1.0f, 1.0f}, float layer = 0.0f);
		Sprite(const Sprite &) = default;
		Sprite(Sprite &&) = default;
		virtual ~Sprite();
		Sprite &operator=(const Sprite &) = default;
		Sprite &operator=(Sprite &&) = default;
		void Render(const Camera *camera);
		void Drag(const mathfu::vec2 &point, bool trigger);
		float* GetVertices(GLuint& size) const;
		GLuint* GetIndices(GLuint& size) const;
		const std::shared_ptr<Material> &GetMaterial() const;
		mathfu::vec2 GetTopLeftCorner() const;
		mathfu::vec2 GetTopRightCorner() const;
		mathfu::vec2 GetBottomLeftCorner() const;
		mathfu::vec2 GetBottomRightCorner() const;
		float GetHalfWidth() const;
		float GetHalfHeight() const;
		float GetLongestSide() const;
		bool IsPointInside(const mathfu::vec2 &point) const;
		bool IsSelected(const mathfu::vec2 &point, bool trigger) const;
		void SetMaterial(const std::shared_ptr<Material> &material);
		void SetDisableRender(bool disable);

		bool rendererDisable;
		std::shared_ptr<Material> material;

	private:
		void Initialize();

		unsigned int vbo, vao, ebo;
		mathfu::vec2 offset;
		bool draggingMode;
	};
}
