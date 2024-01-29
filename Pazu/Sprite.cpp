// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

#include "Sprite.hpp"
#include "Material.hpp"
#include "Camera.hpp"
#include "Globals.hpp"
#include "World.hpp"

namespace Pazu
{
	Sprite::Sprite()
	{
		Initialize();
		ActiveWorld->AddObject(this);
	}

	Sprite::Sprite(const mathfu::vec2 &pos, float rot, const mathfu::vec2 &scale, float layer)
		: Entity(pos, rot, scale, layer)
	{
		Initialize();
		ActiveWorld->AddObject(this);
	}

	Sprite::~Sprite()
	{
		ActiveWorld->RemoveObject(this);
	}

	void Sprite::Render(const Camera *camera)
	{
		material->BindTextures();

		CalculateWorldTransform();

		auto shader = material->shader;
		shader->Use();
		shader->SetMat4(shader->uniforms["proj"], camera->GetOrthoProjection());
		shader->SetMat4(shader->uniforms["view"], camera->GetViewMatrix());
		shader->SetMat4(shader->uniforms["model"], worldTransform);

		shader->SetVec3(shader->uniforms["color"], material->color);
		shader->SetBool(shader->uniforms["noTex"], material->noTexture);

		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

		glBindVertexArray(0);
		shader->Unuse();
	}

	void Sprite::Drag(const mathfu::vec2 &point, bool trigger)
	{
		static Sprite* currentSprite = nullptr;

		if (trigger && IsPointInside(point) && !draggingMode)
		{
			draggingMode = true;

			mathfu::vec2 objCenter = position;
			mathfu::vec2 touchPosition = point;
			offset = touchPosition - objCenter;
		}

		if (!trigger)
		{
			draggingMode = false;
			currentSprite = nullptr;
		}

		if(draggingMode)
		{
			if(!currentSprite)
			{
				currentSprite = this;
			}

			mathfu::vec2 touchPosition = point;
			mathfu::vec2 newObjCenter = touchPosition - currentSprite->offset;
			currentSprite->position = newObjCenter;
		}
	}

	float* Sprite::GetVertices(GLuint& size) const
	{
		size = 32;

		float* vertices = new float[size]
		{
			// Positions         // Normals           // TexCoords
			0.5f, 0.5f, 0.0f,    0.0f, 0.0f, 1.0f,    1.0f, 1.0f,
			0.5f,-0.5f, 0.0f,    0.0f, 0.0f, 1.0f,    1.0f, 0.0f,
		   -0.5f,-0.5f, 0.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
		   -0.5f, 0.5f, 0.0f,    0.0f, 0.0f, 1.0f,    0.0f, 1.0f
		};

		return vertices;
	}

	GLuint* Sprite::GetIndices(GLuint& size) const
	{
		size = 6;

		GLuint* indices = new GLuint[size]
		{
			0, 1, 3,
			1, 2, 3
		};

		return indices;
	}

	const std::shared_ptr<Material> &Sprite::GetMaterial() const
	{
		return material;
	}

	mathfu::vec2 Sprite::GetTopLeftCorner() const
	{
		return mathfu::vec2((-GetHalfWidth())  * std::cos(rotation) - (-GetHalfHeight()) * std::sin(rotation),
			(-GetHalfWidth()) * std::sin(rotation) + (-GetHalfHeight()) * std::cos(rotation)) + position;
	}

	mathfu::vec2 Sprite::GetTopRightCorner() const
	{
		return mathfu::vec2((GetHalfWidth()) * std::cos(rotation) - (-GetHalfHeight()) * std::sin(rotation),
			(GetHalfWidth()) * std::sin(rotation) + (-GetHalfHeight()) * std::cos(rotation)) + position;
	}

	mathfu::vec2 Sprite::GetBottomLeftCorner() const
	{
		return mathfu::vec2((-GetHalfWidth()) * std::cos(rotation) - (GetHalfHeight()) * std::sin(rotation),
			(-GetHalfWidth()) * std::sin(rotation) + (GetHalfHeight()) * std::cos(rotation)) + position;
	}

	mathfu::vec2 Sprite::GetBottomRightCorner() const
	{
		return mathfu::vec2((GetHalfWidth()) * std::cos(rotation) - (GetHalfHeight()) * std::sin(rotation),
			(GetHalfWidth()) * std::sin(rotation) + (GetHalfHeight()) * std::cos(rotation)) + position;
	}

	float Sprite::GetHalfWidth() const
	{
		return scale.x / 2.0f;
	}

	float Sprite::GetHalfHeight() const
	{
		return scale.y / 2.0f;
	}

	float Sprite::GetLongestSide() const
	{
		return std::max(scale.x, scale.y);
	}

	bool Sprite::IsPointInside(const mathfu::vec2 &point) const
	{
		mathfu::vec2 AP = point - GetTopLeftCorner();
		mathfu::vec2 AB = GetTopRightCorner() - GetTopLeftCorner();
		mathfu::vec2 AD = GetBottomLeftCorner() - GetTopLeftCorner();

		return (0.0f < mathfu::vec2::DotProduct(AP, AB) && mathfu::vec2::DotProduct(AP, AB) < mathfu::vec2::DotProduct(AB, AB)
			&& 0.0f < mathfu::vec2::DotProduct(AP, AD) && mathfu::vec2::DotProduct(AP, AD) < mathfu::vec2::DotProduct(AD, AD));
	}

	bool Sprite::IsSelected(const mathfu::vec2 &point, bool trigger) const
	{
		return IsPointInside(point) && trigger;
	}

	void Sprite::SetMaterial(const std::shared_ptr<Material> &material)
	{
		this->material = material;
	}

	void Sprite::SetDisableRender(bool disable)
	{
		this->rendererDisable = disable;
	}

	void Sprite::Initialize()
	{
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);

		glBindVertexArray(vao);

		GLuint size;
		auto vertices = GetVertices(size);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), vertices, GL_STATIC_DRAW);

		auto indices = GetIndices(size);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(float), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		// Unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		material = std::make_shared<Material>();
		material->shader = DefaultShader;
	}
}
