#pragma once
#include "Pazu/Application.hpp"
#include "CameraController.hpp"
#include "Gui.hpp"

class App final : public Pazu::Application
{
public:
	App(const Pazu::Configuration &config);
	void Initialize() final;
	void Load() final;
	void Update() final;
	void PreRender() final;
	void Render() final;
	void Resize(int width, int height) final;
	void Destroy() final;
	void Focused() final;
	void Unfocused() final;

	std::shared_ptr<Pazu::Camera> camera;
	std::shared_ptr<CameraController> camController;
	// std::shared_ptr<Gui> gui;
};
