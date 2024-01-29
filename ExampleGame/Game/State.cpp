#include <iostream>
#include "WinAPICommon.hpp"
#include "Pazu/Sprite.hpp"
#include "Pazu/Material.hpp"
#include "Pazu/Globals.hpp"
#include "State.hpp"

State::State(const std::shared_ptr<Pazu::ResourceManager> &resource, const std::shared_ptr<Pazu::Camera> &camera, const std::shared_ptr<Pazu::Input> &input, const std::shared_ptr<Pazu::Time> &time)
	: resource{resource}, camera{camera}, input{input}, time{time} { }

void State::Load()
{
	for (int i = 0; i < 60; i++)
	{
		int j = i % 2;

		sprites.push_back(std::make_shared<Pazu::Sprite>());
		sprites.back()->material->SetDiffuseMap(j == 0 ?
			resource->Load<Pazu::Texture>("Characters/Character.png")
			: resource->Load<Pazu::Texture>("Characters/Character2.png"));
		sprites.back()->SetPosition(mathfu::vec2(rand() % 10 + 600, rand() % 10 + 400));
	}

	kurdele = std::make_shared<Pazu::Sprite>();
	kurdele->material->SetDiffuseMap(resource->Load<Pazu::Texture>("Armors/Kurdele.png"));
	kurdele->SetLayer(0.5f);

	kurdele->SetParent(sprites.back().get());
	sprites.back()->layer = 0.1f;
}

void State::Unload()
{
}

void State::Pause()
{
}

void State::Resume()
{
}

void State::Resize(int width, int height)
{
	std::cout << width << " : " << height << std::endl;
}

void State::Update()
{
	const float dt = time->GetDelta() * 3600.0f;
	for (auto spr : sprites)
	{
		spr->Turn(dt);
		mathfu::vec2 mousePos = camera->GetScreenToWorldPoint(input->GetMousePosition());
		spr->Drag(mousePos, input->IsMouseDown(SDL_BUTTON_LEFT));
	}

	if (input->IsKeyHit(SDLK_r))
	{
		kurdele->SetDisableRender(true);
	}
	else if (input->IsKeyUp(SDLK_r))
	{
		kurdele->SetDisableRender(false);
	}
	else if (input->IsKeyUp(SDLK_q))
	{
		kurdele->SetParent(nullptr);
	}
	else if (input->IsKeyUp(SDLK_DELETE))
	{
		kurdele = nullptr;
	}

    if (input->IsKeyUp(SDLK_SPACE))
	{
		Wcm::Log->Info("Translations of the kurdele.")
			.Sub("Position X", std::to_string(kurdele->position.x))
			.Sub("Position Y", std::to_string(kurdele->position.y))
			.Sub("Rotation",   std::to_string(kurdele->rotation))
			.Sub("Scale X",    std::to_string(kurdele->scale.x))
			.Sub("Scale Y",    std::to_string(kurdele->scale.y));
		Wcm::Log->Info("Translations of the kurdele (relative to its parent).")
			.Sub("Position X", std::to_string(kurdele->GetPosition().x))
			.Sub("Position Y", std::to_string(kurdele->GetPosition().y))
			.Sub("Rotation",   std::to_string(kurdele->GetRotation()))
			.Sub("Scale X",    std::to_string(kurdele->GetScale().x))
			.Sub("Scale Y",    std::to_string(kurdele->GetScale().y));
	}
}
