#pragma once
#include "OrthoView.h"
#include "RectangleMesh.h"

class ContainerView: public OrthoView {
private:
    OrthoMesh* mesh;
public:
    ContainerView(
        Shader* _shader = Shader::get(Shader::PrimitiveOrtho)
    ) : OrthoView(_shader), mesh(RectangleMesh::createOrtho()) {}
    ~ContainerView() {
        delete mesh;
    }

    void draw() override {
        auto model = calculateModel();
        draw(model);
    }

    void draw(glm::mat4& model) {
        shader->useProgram();
        mesh->bind();

        glUniformMatrix4fv(
            shader->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniform3fv(
            shader->getUniformLocation("color"), 1, glm::value_ptr(color));

        glDrawElements(GL_TRIANGLES, mesh->getElementsCount(), GL_UNSIGNED_INT, 0);
    }

    void onMouseEnter(const glm::dvec2 position, bool press) {
        
    }
    void onMouseHower(const glm::dvec2& position, const glm::dvec2& positionOffset, bool press) {
        setColor({ 1.0f, 0.0f, 0.0f });
        if (press) {
            offset += positionOffset;
        }
    }
    void onMouseLeft(const glm::dvec2& position, bool press) {
        setColor({ 0.0f, 0.0f, 1.0f });
    }
};
