#pragma once

#include <glm/glm.hpp>

/// <summary>
/// Holds all state information relevant to a character as loaded using FreeType
/// </summary>
/// <param name="textureID"> - ID handle of the glyph texture.</param>
/// <param name="size"> - size of glyph.</param>
/// <param name="bearing"> - offset from baseline to left/top of glyph.</param>
/// <param name="advance"> - horizontal offset to advance to next glyph.</param>
struct Character {
	unsigned int textureID = 0;

	glm::ivec2 size;
	glm::ivec2 bearing;

	unsigned int advance = 0;
};
