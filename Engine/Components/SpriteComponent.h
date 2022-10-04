#pragma once
#include "RenderComponent.h"
#include "Math/Rect.h"

namespace Ethrl
{
	class Texture;

	class SpriteComponent : public RenderComponent
	{
	public:
		CLASS_DECLARATION(SpriteComponent)

		virtual void Update() override;
		virtual void Draw(Renderer& renderer) override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		std::shared_ptr<Texture> m_texture;
	};
}
