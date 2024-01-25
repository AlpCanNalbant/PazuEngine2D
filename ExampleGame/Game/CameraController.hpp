#pragma once
#include "Pazu/Input.hpp"
#include "Pazu/Camera.hpp"

class CameraController
{
public:
	CameraController(const std::shared_ptr<Pazu::Camera> &camera, const std::shared_ptr<Pazu::Input> &input);
	void Update(float dt);

	float moveSpeed{2000.0f};
	float zoomingSpeed{2000.0f};

private:
	void HandleMovement(float dt);
	void HandleZoom(float dt);

	std::shared_ptr<Pazu::Camera> camera;
	std::shared_ptr<Pazu::Input> input;
	mathfu::vec2 camPos;
	float camZoom;
};
