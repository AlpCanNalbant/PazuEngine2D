#include <iostream>
#include <algorithm>
#include "CameraController.hpp"

CameraController::CameraController(const std::shared_ptr<Pazu::Camera> &camera, const std::shared_ptr<Pazu::Input> &input)
	: camera{camera}, input{input}, camPos{camera->GetPosition()}, camZoom{camera->GetZoom()} { }

void CameraController::Update(float dt)
{
	HandleMovement(dt);
	// if (input->IsMouseScrolled())
	// {
	HandleZoom(dt);
	// }
}

void CameraController::HandleMovement(float dt)
{
	if (input->IsKeyDown(SDLK_w))
	{
		camPos += mathfu::vec2(0.0f, moveSpeed * dt);
	}
	if (input->IsKeyDown(SDLK_s))
	{
		camPos -= mathfu::vec2(0.0f, moveSpeed * dt);
	}

	if (input->IsKeyDown(SDLK_d))
	{
		camPos -= mathfu::vec2(moveSpeed * dt, 0.0f);
	}
	if (input->IsKeyDown(SDLK_a))
	{
		camPos += mathfu::vec2(moveSpeed * dt, 0.0f);
	}

	camera->position = mathfu::vec2::Lerp(camera->position, camPos, dt * 60.0f);
}

void CameraController::HandleZoom(float dt)
{
	camZoom += input->GetMouseWheelDelta() * zoomingSpeed * dt;

	camera->zoom = mathfu::Lerp(camera->zoom, camZoom, dt * 200.0f);

    camera->zoom = std::clamp(camera->zoom, 0.4f, 8.0f);
	camZoom = std::clamp(camZoom, 0.5f, 7.0f);
}
