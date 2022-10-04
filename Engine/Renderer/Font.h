#pragma once
#include "Resource/Resource.h"
#include <string>

// !! add necessary includes
// !! forward declare the _TTF_Font struct
struct _TTF_Font;
struct SDL_Surface;

namespace Ethrl
{
	struct Color;

	class Font : public Resource
	{
	public:
		Font() = default;
		Font(const std::string& filename, int fontSize);
		~Font();

		bool Create(std::string filename, ...) override;
		SDL_Surface* CreateSurface(const std::string& text, const Color& color);

		bool Load(const std::string& filename, int fontSize);

		friend class Text;

	private:
		_TTF_Font* m_ttfFont = nullptr;
	};
}