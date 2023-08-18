#pragma once
#include "IView.h"
#include "Font.h"
#include "WindowSize.h"

class OrthoView : public IView {
public:
    enum TransformType {
        Top     = 0x00000001,
        Bottom  = 0x00000002,
        Left    = 0x00000010,
        Right   = 0x00000020
    };
protected:
    Shader* shader;
    glm::vec3 color     = { 1.0f, 1.0f, 1.0f };
    glm::vec2 offset    = { 0.0f, 0.0f };
    glm::vec2 scale     = { 1.0f, 1.0f };
    float layer         = 0.0f;
    int transformType   = TransformType::Top | TransformType::Left;
    WindowSize windowSize;

    glm::mat4 calculateModel() {
        glm::mat4 model(1.0f);
        glm::vec2 maxScale(
            std::fminf(scale.x, windowSize.getSize().x),
            std::fminf(scale.y, windowSize.getSize().y)
        );
        model[0].x = maxScale.x;
        model[1].y = maxScale.y;

        if (transformType & OrthoView::Top) {
            auto top = windowSize.getSize().y - maxScale.y / 2.0f;
            auto bottom = maxScale.y / 2.0f;
            auto value = top - offset.y;
            model[3].y = value; // std::clamp(value, bottom, top);
        }

        if (transformType & OrthoView::Bottom) {
            model[3].y = offset.y;
        }

        if (transformType & OrthoView::Left) {
            auto left = maxScale.x / 2.0f;
            auto right = windowSize.getSize().x - maxScale.x / 2.0f;
            auto value = offset.x + left;
            model[3].x = value; // std::clamp(value, left, right);
        }

        if (transformType & OrthoView::Right) {
            model[3].x = offset.x + windowSize.getSize().x;
        }
        model[3].z = layer;

        return model;
    }
public:
    OrthoView(
        Shader* _shader = Shader::get(Shader::PrimitiveOrtho)
    ) : shader(_shader) {}

    virtual void setColor(glm::vec3 _color) { color = _color; }

    virtual void setOffset(const glm::vec2& value) {
        offset = value;
    }

    const glm::vec2& getOffset() {
        return offset;
    }

    virtual void setLayer(const float& value) {
        layer = value / 100.0f;
    }

    const float& getLayer() {
        return layer;
    }

    virtual void setScale(const glm::vec2& value) {
        scale = value;
    }

    const glm::vec2& getScale() {
        return scale;
    }

    virtual void setTransformType(int _transformType) {
        transformType = _transformType;
    }
};
