#pragma once
#include <vector>
#include "App.hpp"

class State : public Pazu::State
{
public:
	State(const std::shared_ptr<Pazu::ResourceManager> &resource, const std::shared_ptr<Pazu::Camera> &camera,
	 	  const std::shared_ptr<Pazu::Input> &input, const std::shared_ptr<Pazu::Time> &time);
	void Load() override;
	void Unload() override;
	void Pause() override;
	void Resume() override;
	void Resize(int width, int height) override;
	void Update() override;

public:
	std::shared_ptr<Pazu::ResourceManager> resource;
	std::shared_ptr<Pazu::Camera> camera;
	std::shared_ptr<Pazu::Input> input;
	std::shared_ptr<Pazu::Time> time;
	std::vector<std::shared_ptr<Pazu::Sprite>> sprites;
	std::shared_ptr<Pazu::Sprite> kurdele;
};
