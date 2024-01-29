// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

#include <algorithm>
#include "Camera.hpp"
#include "World.hpp"

namespace Pazu
{
	Camera::Camera()
	{
		ActiveWorld->SetObject(this);
	}

	Camera::Camera(const mathfu::vec2 &pos, float rot, const mathfu::vec2 &scale, float zoom)
		: Entity(pos, rot, scale), zoom{zoom}
	{
		ActiveWorld->SetObject(this);
	}

	mathfu::mat4 Camera::GetViewMatrix() const
	{
		return mathfu::mat4::FromTranslationVector({midOffset.x, midOffset.y, 0.0f})
			* mathfu::mat4::FromRotationMatrix(mathfu::mat3::RotationZ(rotation))
		 	* mathfu::mat4::FromScaleVector({zoom * 50.0f, zoom * 50.0f, 1.0f})
		 	* mathfu::mat4::FromTranslationVector({-midOffset.x, -midOffset.y, 0.0f})
		 	* mathfu::mat4::FromTranslationVector({position.x, position.y, 0.0f});
	}

	mathfu::vec2 Camera::GetScreenToWorldPoint(const mathfu::vec2 &point) const
	{
		return mathfu::mat4::UnProject({point.x, height - point.y, 0.0f}, GetViewMatrix(), GetOrthoProjection(), width, height).xy();
	}

	mathfu::mat4 Camera::GetOrthoProjection() const
	{
		return orthoProj;
	}

	float Camera::GetZoom() const
	{
		return zoom;
	}

	void Camera::SetOrthoProjection(int width, int height)
	{
		orthoProj = mathfu::mat4::Ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f);
		midOffset = mathfu::vec2(width / 2.0f, height / 2.0f);
		this->width = width;
		this->height = height;
	}

	void Camera::SetZoom(float zoom)
	{
		this->zoom = zoom;
	}
}
