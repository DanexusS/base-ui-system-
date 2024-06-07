#include <iostream> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "TextObject.h"

/// <summary>
/// Setter for all values needed for TextObject init.
/// </summary>
/// <param name="text"></param>
/// <param name="alignment"> - alignment variant.</param>
/// <param name="offset"> - Vector2 of offsets, like (Horizontal, Vertical), from top-left corner.</param>
/*
void TextObject::setValues(const char* text, TextAlignment alignment, const Vector2& offset) {
    this->_text = text;
    this->_alignment = alignment;
    this->_textOffset = this->getAlignmentTextOffset(this->_alignment) + offset;
    */
    //}

    /// <summary>
    /// Text alignment inside AbstractObject box will be defined by offsets.
    /// This function determines this offset and return it, like (Vertical, Horizontal).
    /// </summary>
    /// <param name="alignment"> - alignment type.</param>
    /// <returns></returns>
    // TODO: add proper text offsets based on alignment.
    /*
    Vector2 TextObject::getAlignmentTextOffset(TextAlignment alignment) {
        switch (alignment)
        {
        case TopLeft:
            break;
        case MidLeft:
            break;
        case ButtomLeft:
            break;
        case TopMiddle:
            break;
        case MidMiddle:
            break;
        case ButtomMiddle:
            break;
        case TopRight:
            break;
        case MidRight:
            break;
        case ButtomRight:
            break;
        default:
            return {};
        }
        return{};
    }*/

    /// <summary>
    /// Get proper AbstractObject box size, based on text inside, alignment and text offset.
    /// </summary>
    /// <param name="text"></param>
    /// <param name="alignment"> - alignment type.</param>
    /// <param name="extra_offset"> - offset of the text.</param>
    /// <returns>Vector2, like (Width, Height).</returns>
    //Vector2 TextObject::getSize(const char* text, TextAlignment alignment, const Vector2& extra_offset) {
        /*
        Vector2 align_text_offset = getAlignmentTextOffset(alignment);
        double width = 2 * (align_text_offset[0] + extra_offset[0]) + strlen(text) * FONT_SYMBOL_SIZE[0];
        double height = 2 * (align_text_offset[1] + extra_offset[1]) + FONT_SYMBOL_SIZE[1];
        return Vector2(width, height);
        */

        //	return Vector2(0, 0);
        //}

        /*
        TextObject::TextObject(const Vector2& pos, const char* text) :
            UIObject(pos, this->getSize(text, MidMiddle, { 0, 0 }))
        {
            this->setValues(text, MidMiddle, { 0, 0 });
        }

        TextObject::TextObject(const Vector2& pos, TextAlignment alignment, const char* text) :
            UIObject(pos, this->getSize(text, alignment, { 0, 0 }))
        {
            this->setValues(text, alignment, { 0, 0 });
        }

        TextObject::TextObject(const Vector2& pos, TextAlignment alignment, const Vector2& extra_offset, const char* text) :
            UIObject(pos, this->getSize(text, alignment, extra_offset))
        {
            this->setValues(text, alignment, extra_offset);
        }
        */

const char* DEFAULT_FONT = "Fonts/TNR.ttf";

Vector2 TextObject::GetTextBoxSize() {
    float textW = 0, textH = 0;

    for (auto c = this->_text.begin(); c != this->_text.end(); c++) {
        Character ch = _characters[*c];
        int ch_advance = ch.advance;

        textW += ch.size.x + ch_advance;
        textH = std::max(textH, (float)ch.size.y);
    }

    return Vector2(textW, textH);
}

TextObject::TextObject(std::string text, const Vector2& pos, int scr_w, int scr_h) : UIObject(pos) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    this->_text = text;
    this->_textPosition = pos;
    this->_textColor = { 0, 0, 0 };

    this->_font = DEFAULT_FONT;
    this->_fontSize = 24;

    this->_textShader = Shader("Shaders/text.vs", "Shaders/text.fs");
    this->_textShader.SetMatrix4("projection", glm::ortho(0.0f, static_cast<float>(scr_w), static_cast<float>(scr_h), 0.0f), true);
    this->_textShader.SetInteger("text", 0);

    glGenVertexArrays(1, &this->_textVAO);
    glGenBuffers(1, &this->_textVBO);
    glBindVertexArray(this->_textVAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->_textVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void TextObject::init() {
    this->_characters.clear();

    FT_Library ft;
    if (FT_Init_FreeType(&ft))
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

    FT_Face face;
    if (FT_New_Face(ft, this->_font.c_str(), 0, &face))
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

    FT_Set_Pixel_Sizes(face, 0, this->_fontSize);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    for (GLubyte c = 0; c < 128; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        
        unsigned int texture;

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        this->_characters.insert(std::pair<char, Character>(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void TextObject::renderText() {
    this->_textShader.Use();
    this->_textShader.SetVector3f("textColor", _textColor.r, _textColor.g, _textColor.b);

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(this->_textVAO);

    for (auto c = this->_text.begin(); c != this->_text.end(); c++) {
        Character ch = _characters[*c];

        float xpos = this->_textPosition[0] + ch.bearing.x;
        float ypos = this->_textPosition[1] + (this->_characters['H'].bearing.y - ch.bearing.y);

        float w = ch.size.x;
        float h = ch.size.y;

        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 0.0f },
            { xpos,     ypos,       0.0f, 0.0f },

            { xpos,     ypos + h,   0.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 0.0f }
        };

        glBindTexture(GL_TEXTURE_2D, ch.textureID);

        glBindBuffer(GL_ARRAY_BUFFER, this->_textVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        this->_textPosition[0] += (ch.advance >> 6);
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

    this->_textPosition[0] = this->_position[0];
    this->_textPosition[1] = this->_position[1];
}