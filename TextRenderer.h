#pragma once

#include <vector>

#include "Shader.h"
#include "TextObject.h"
#include "Vector2.h"
#include "Character.h"
#include "constants.h"

const std::string DEFAULT_FONT = "Fonts/TNR.ttf";

class TextRenderer {
private:
	Shader _textShader;
	unsigned int _VAO, _VBO;

	std::string _font;
	unsigned int _fontSize;

	std::map<char, Character> _characters;

	void setValues(std::string font = DEFAULT_FONT, unsigned int font_size = 24);
public:
	TextRenderer(const TextRenderer& other) { setValues(other._font, other._fontSize); }
	TextRenderer(std::string font = DEFAULT_FONT, unsigned int font_size = 24) { setValues(font, font_size); }

	void init();
	void renderText(float x, float y, std::string text = "", const Color& color = { 0, 0, 0 });
};
