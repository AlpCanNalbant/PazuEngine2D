// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

#include "Entity.hpp"

namespace Pazu
{
	Entity::Entity(const mathfu::vec2 &pos, float rot, const mathfu::vec2 &scale, float layer)
		: position{pos}, rotation{rot}, scale{scale}, layer{layer} { }

	Entity::~Entity()
	{
		if (parent)
		{
			RemoveParent();
		}
		if (!childs.empty())
		{
			RemoveChilds();
		}
	}

	void Entity::Move(const mathfu::vec2 &move)
	{
		this->position += move;
	}

	void Entity::Turn(const float turn)
	{
		this->rotation += turn;
	}

	void Entity::CalculateWorldTransform()
	{
		if (!parent)
		{
			SetWorldTransform(mathfu::mat4::FromTranslationVector({position.x, position.y, layer})
				* mathfu::mat4::FromRotationMatrix(mathfu::mat3::RotationZ(rotation * mathfu::kDegreesToRadians))
				* mathfu::mat4::FromScaleVector({scale.x, scale.y, 1.0f}));
		}
		else
		{
			SetWorldTransform(parent->worldTransform
				* (mathfu::mat4::FromTranslationVector({position.x, position.y, 1.0f})
				*  mathfu::mat4::FromRotationMatrix(mathfu::mat3::RotationZ(rotation * mathfu::kDegreesToRadians))
				*  mathfu::mat4::FromScaleVector({scale.x, scale.y, 1.0f})));
			worldTransform[14] = layer;
		}
	}

	mathfu::vec2 Entity::GetPosition() const
	{
		if (!parent)
		{
			return position;
		}
		else
		{
			return worldTransform.TranslationVector3D().xy();
		}
	}

	float Entity::GetRotation() const
	{
		if (!parent)
		{
			return rotation;
		}
		else
		{
			// Referred to: https://eecs.qmul.ac.uk/~gslabaugh/publications/euler.pdf
			return std::atan2(worldTransform[1] / std::cos(4.0f / M_PI), worldTransform[0] / std::cos(4.0f / M_PI));
		}
	}

	mathfu::vec2 Entity::GetScale() const
	{
		if (!parent)
		{
			return scale;
		}
		else
		{
			const auto &col1 = worldTransform.GetColumn(0), &col2 = worldTransform.GetColumn(1);
			return {((col1.x * col1.y * col1.z * col1.w) > -1 ? 1 : -1) * sqrtf(col1.x * col1.x + col1.y * col1.y + col1.z * col1.z),
				    ((col2.x * col2.y * col2.z * col2.w) > -1 ? 1 : -1) * sqrtf(col2.x * col2.x + col2.y * col2.y + col2.z * col2.z)};
		}
	}

	float Entity::GetLayer() const
	{
		return layer;
	}

	Entity *Entity::GetParent() const
	{
		return parent;
	}

	const std::vector<Entity *> &Entity::GetChilds() const
	{
		return childs;
	}

	mathfu::mat4 Entity::GetWorldTransform() const
	{
		return worldTransform;
	}

	void Entity::SetPosition(const mathfu::vec2 &position)
	{
		this->position = position;
	}

	void Entity::SetRotation(const float rotation)
	{
		this->rotation = rotation;
	}

	void Entity::SetScale(const mathfu::vec2 &scale)
	{
		this->scale = scale;
	}

	void Entity::SetLayer(float layer)
	{
		this->layer = layer;
	}

	void Entity::SetParent(Entity *entity)
	{
		if (parent)
		{
			RemoveParent();
		}
		parent = entity;
		if (entity)
		{
			parent->childs.push_back(this);
		}
	}

	void Entity::SetWorldTransform(const mathfu::mat4 &transform)
	{
		worldTransform = transform;
	}

	void Entity::RemoveParent()
	{
		parent->childs.erase(std::find(parent->childs.begin(), parent->childs.end(), this));
		position = GetPosition(); rotation = GetRotation(); scale = GetScale();
		parent = nullptr;
	}

	void Entity::RemoveChilds()
	{
		for (auto child : childs)
		{
			child->parent = nullptr;
		}
		childs.clear();
	}
}
