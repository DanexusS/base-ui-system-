
#pragma once

#include <string>
#include <map>

#include "UIObject.h"
#include "Shader.h"
#include "Character.h"

enum TextAlignment {
	TopLeft,
	MidLeft,
	ButtomLeft,
	TopMiddle,
	MidMiddle,
	ButtomMiddle,
	TopRight,
	MidRight,
	ButtomRight
};

/*
// A renderer class for rendering text displayed by a font loaded using the
// FreeType library. A single font is loaded, processed into a list of Character
// items for later rendering.
class TextRenderer
{
public:
	// holds a list of pre-compiled Characters
	std::map<char, Character> Characters;
	// shader used for text rendering
	Shader TextShader;
	// constructor
	TextRenderer(unsigned int width, unsigned int height);
	// pre-compiles a list of characters from the given font
	void Load(std::string font, unsigned int fontSize);
	// renders a string of text using the precompiled list of characters
	void RenderText(std::string text, float x, float y, float scale, Color color = { 1, 1, 1 });
private:
	// render state
	unsigned int VAO, VBO;
};*/



class TextObject : public UIObject {
private:
	std::string _text;
	Vector2 _textPosition;
	Color _textColor;

	Shader _textShader;
	std::map<char, Character> _characters;

	unsigned int _textVAO, _textVBO;

	std::string _font;
	unsigned int _fontSize;

	Vector2 GetTextBoxSize();
public:
	// [TODO] screen size temporarly
	TextObject(std::string text, const Vector2& pos, int scr_w, int scr_h);

	void init();
	void renderText();

	std::string getText() { return _text; }
};




/*
class TextObject : public UIObject {
private:
	std::string _text;
	Color _textColor;

	std::map<char, Character> _characters;

	Shader TextShader;

	// TODO: alignment WIP

	TextAlignment _alignment;
	Vector2 _textOffset;

	void setValues(const char* text, TextAlignment alignment, const Vector2& extra_offset);

	Vector2 getAlignmentTextOffset(TextAlignment alignment);

	Vector2 getSize(const char* text, TextAlignment alignment, const Vector2& extra_offset);

public:

	TextObject() : UIObject() { setValues(nullptr, MidMiddle, { 0, 0 }); }
	TextObject(const char* text);
	TextObject(const Vector2& pos) : UIObject(pos) { setValues(nullptr, MidMiddle, { 0, 0 }); }
	TextObject(const Vector2& pos, const char* text);
	TextObject(const Vector2& pos, TextAlignment alignment, const char* text);
	TextObject(const Vector2& pos, TextAlignment alignment, const Vector2& extra_offset, const char* text);

	void changeText(const char* new_text) { this->_text = new_text; }

};
*/
