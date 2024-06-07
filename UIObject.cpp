#include "UIObject.h"

/// <summary>
///	Setter to all values needed for AbstractObject init.
/// </summary>
/// <param name="pos"> - Vector2 of coordinates (X, Y) (counting from center of the screen).</param>
/// <param name="w"> - width of the object.</param>
/// <param name="h"> - height of the object.</param>
void UIObject::setValues(const Vector2& pos, double w, double h) {
    this->_shader = Shader("Shaders/color_shader.vs", "Shaders/color_shader.fs");
	this->_position = pos;
	this->_w = w;
	this->_h = h;
    this->_backgroundColor = Color(1, 1, 1);
    this->_visibility = true;
}

void UIObject::setSize(double w, double h) {
    this->_w = w;
    this->_h = h;
}

/// <summary>
/// Change size of the object according to its inner properties.
/// </summary>
/// <param name="dw"> - width delta.</param>
/// <param name="dh"> - height delta.</param>
void UIObject::changeSize(double dw, double dh) {
	this->_w += dw;
	this->_h += dh;
}

void UIObject::init() {
    float width = (float)this->_w / 640;
    float height = (float)this->_h / 480;

    Vector2 pos = { this->_position[0] / 640, this->_position[1] / 480 };

    float vertices[] = {
         width / 2 + (float)pos[0],  height / 2 + (float)pos[1], 0.0f, 1.0f, 0.0f, 1.0f,
         width / 2 + (float)pos[0], -height / 2 + (float)pos[1], 0.0f, 1.0f, 1.0f, 0.0f,
        -width / 2 + (float)pos[0], -height / 2 + (float)pos[1], 0.0f, 1.0f, 0.0f, 1.0f,
        -width / 2 + (float)pos[0],  height / 2 + (float)pos[1], 0.0f, 0.0f, 1.0f, 0.0f
    };
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    glGenVertexArrays(1, &this->_VAO);
    glGenBuffers(1, &this->_VBO);
    glGenBuffers(1, &this->_EBO);
    glBindVertexArray(this->_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, this->_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void UIObject::draw() {
    if (!this->_visibility)
        return;

    int vertexColorLocation = glGetUniformLocation(this->_shader.ID, "ourColor");
    glUniform4f(vertexColorLocation, _backgroundColor.r, _backgroundColor.g, _backgroundColor.b, 1.0f);

    this->_shader.Use();

    glBindVertexArray(this->_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
