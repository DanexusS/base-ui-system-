#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "Vector2.h"

// NOTE: just a placeholder before OpenGL implementation
struct Color {
	float r, g, b;

	Color() {
		r = 0;
		g = 0;
		b = 0;
	}

	Color(float _r, float _g, float _b) {
		r = _r;
		g = _g;
		b = _b;
	}

	bool operator==(const Color& other) const { return r == other.r && b == other.b && g == other.g; }
};

class UIObject {
protected:
	Vector2 _position;
	double _w, _h;

	Color _backgroundColor, _outlineColor;

	Shader _shader;

	bool _visibility;

	unsigned int _VAO, _VBO, _EBO;

	void setValues(const Vector2& pos, double w, double h);
public:
	UIObject() { setValues({}, 1, 1); }
	UIObject(double w, double h) { setValues({}, w, h); }
	UIObject(const Vector2& pos) { setValues(pos, 1, 1); }
	UIObject(const Vector2& pos, const Vector2& size) { setValues(pos, size[0], size[1]); }
	UIObject(const Vector2& pos, double w, double h) { setValues(pos, w, h); }

	virtual ~UIObject() { glDeleteVertexArrays(1, &_VAO); }

	virtual void setSize(double w, double h);
	virtual void changeSize(double dw, double dh);

	virtual void setVisibility(bool visibility) { _visibility = visibility; }
	virtual void hide() { _visibility = false; }
	virtual void show() { _visibility = true; }

	virtual void setPosition(Vector2 new_pos) { _position = new_pos; }
	virtual void changePosition(Vector2 delta) { _position += delta; }

	void init();
	void draw();

	// TODO: Implement OpenGL
	// virtual void render(SomeOpenGlStuff* canvas_or_painter, const GraphicOptions& opts) = 0;
};
