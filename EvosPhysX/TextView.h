#pragma once
#include "OrthoView.h"

class TextView: public OrthoView {
private:
    enum WrapResult {
        Continue,
        Break,
        Draw
    };

    Font* font;
    std::string text;

    void beforeDraw() {
        // activate corresponding render state	
        shader->useProgram();
        glUniform3f(shader->getUniformLocation("fragColor"), color.x, color.y, color.z);
        glUniform1f(shader->getUniformLocation("layer"), layer);
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(font->getVertexArray());
    }

    WrapResult wrap(
        char c,
        Font::Character& ch,
        const glm::vec2& range,
        const glm::vec2& origin,
        glm::vec2& position
    ) {
        if (c == '\n') {
            position.y -= font->getMaxVerticalBearing();
            position.x = origin.x;
            return WrapResult::Continue;
        }

        if (position.x + ch.size.x > range.x) {
            position.y -= font->getMaxVerticalBearing();
            position.x = origin.x;
        }

        if (position.y < range.y) {
            return WrapResult::Break;
        }

        return WrapResult::Draw;
    }

    void draw(Font::Character& ch, glm::vec2& position, glm::vec2& scale) {
        float xpos = position.x + ch.bearing.x * scale.x;
        float ypos = position.y - (ch.size.y - ch.bearing.y) * scale.y;

        float w = ch.size.x * scale.x;
        float h = ch.size.y * scale.y;

        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.textureId);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, font->getVertexBuffer());
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        position.x += (ch.advance >> 6) * scale.x; // bitshift by 6 to get value in pixels (2^6 = 64)
    }

    void afterDraw() {
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
public:
    TextView(
        Shader* _shader = Shader::get(Shader::Ortho),
        Font* _font = Font::get()
    ): OrthoView(_shader), font(_font) {
        setOffset({ 0.0f, font->getMaxVerticalBearing() });
    }

    void setText(std::string_view str) { text = str; }

	virtual void draw() override {
        if (text.empty()) return;

        auto model = calculateModel();

        beforeDraw();

        // iterate through all characters
        std::string::const_iterator c;
        glm::vec2 position = { model[3].x, model[3].y };
        glm::vec2 scale = { model[0].x, model[1].y };
        for (c = text.begin(); c != text.end(); c++)
        {
            auto& ch = font->getCharacter(*c);

            if (*c == '\n') {
                position.y -= font->getMaxVerticalBearing();
                position.x = model[3].x;
                continue;
            }

            draw(ch, position, scale);
        }

        afterDraw();
	};

    virtual void draw(const glm::vec2& range) {
        if (text.empty()) return;

        auto model = calculateModel();

        beforeDraw();

        // iterate through all characters
        std::string::const_iterator c;
        glm::vec2 origin = { model[3].x, model[3].y };
        glm::vec2 position = origin;
        glm::vec2 scale = { model[0].x, model[1].y };
        for (c = text.begin(); c != text.end(); c++)
        {
            auto& ch = font->getCharacter(*c);

            auto result = wrap(*c, ch, range, origin, position);
            if (result == WrapResult::Break) break;
            if (result == WrapResult::Continue) continue;

            draw(ch, position, scale);
        }

        afterDraw();
    };
};
