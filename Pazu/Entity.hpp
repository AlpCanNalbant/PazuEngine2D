// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

#pragma once
#include <vector>
#include <memory>

namespace Pazu
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(const mathfu::vec2 &pos, float rot = 0.0f, const mathfu::vec2 &scale = {1.0f, 1.0f}, float layer = 0.0f);
		Entity(const Entity &) = default;
		Entity(Entity &&) = default;
		Entity &operator=(const Entity &) = default;
		Entity &operator=(Entity &&) = default;
		void Move(const mathfu::vec2 &move);
		void Turn(const float turn);
		void CalculateWorldTransform();
		mathfu::vec2 GetPosition() const;
		float GetRotation() const;
		mathfu::vec2 GetScale() const;
		float GetLayer() const;
		Entity *GetParent() const;
		const std::vector<Entity *> &GetChilds() const;
		mathfu::mat4 GetWorldTransform() const;
		void SetPosition(const mathfu::vec2 &position);
		void SetRotation(const float rotation);
		void SetScale(const mathfu::vec2 &scale);
		void SetLayer(float layer);
		void SetParent(Entity *entity);
		void SetWorldTransform(const mathfu::mat4 &transform);

		mathfu::vec2 position{0.0f};
		float rotation{0.0f};
		mathfu::vec2 scale{1.0f};
		float layer{0.0f};
		mathfu::mat4 worldTransform{mathfu::mat4::Identity()};

	protected:
		~Entity();
		void RemoveParent();
		void RemoveChilds();

		Entity *parent{nullptr};
		std::vector<Entity *> childs;
	};
}
