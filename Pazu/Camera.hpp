// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

#pragma once
#include "Entity.hpp"

namespace Pazu
{
	class Camera : public Entity
	{
	public:
		Camera();
		Camera(const mathfu::vec2 &pos, float rot = 0.0f, const mathfu::vec2 &scale = {1.0f, 1.0f}, float zoom = 1.0f);
		mathfu::mat4 GetViewMatrix() const;
		mathfu::vec2 GetScreenToWorldPoint(const mathfu::vec2 &point) const;
		mathfu::mat4 GetOrthoProjection() const;
		float GetZoom() const;
		void SetOrthoProjection(int width, int height);
		void SetZoom(float zoom);

		float zoom{1.0f};

	private:
		mathfu::mat4 orthoProj;
		mathfu::vec2 midOffset;
		int width, height;
	};
}
