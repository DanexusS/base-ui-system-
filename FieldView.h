#pragma once

#include <vector>

#include "TextRenderer.h"

class FieldView : UIObject {
private:
	TextRenderer _fieldTextRenderer;
	std::vector<std::vector<char>> _field;
public:
	FieldView() : _field(FIELD_SIZE, std::vector<char>(FIELD_SIZE)) { this->_fieldTextRenderer = TextRenderer(); }

	void init() { _fieldTextRenderer.init(); }
	void draw();

	void setTurn(char turn, unsigned int x, unsigned int y);
};
