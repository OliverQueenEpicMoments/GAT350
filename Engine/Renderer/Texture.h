#pragma once
#include "Math/Vector2.h"
#include "Resource/Resource.h"
#include <string>

struct SDL_Texture;
struct SDL_Surface;
// !! forward declaration for SDL pointers below (SDL likes to use structs)

namespace Ethrl
{
	// !! forward declaration for Renderer below
	class Renderer;

	class Texture : public Resource
	{
	public:
		Texture() = default;
		~Texture();

		bool Create(std::string filename, ...) override;
		bool CreateFromSurface(SDL_Surface* surface, Renderer& renderer);

		bool Load(const std::string& filename, Renderer& renderer);

		Vector2 GetSize() const;

		friend class Renderer;

	private:
		SDL_Texture* m_texture = nullptr;
	};
}
