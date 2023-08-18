#include "Renderer.h"

void Renderer::updateProjectionMatrix()
{
    for (auto& shader : Shader::getAll()) {
        auto& projection = shader->isOrthoProjection() ?
            camera->getOrthoProjectionMatrix() :
            camera->getProjectionMatrix();

        shader->useProgram();
        glUniformMatrix4fv(
            shader->getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));
    }
}

void Renderer::renderChunk(int xOffset, int zOffset, float cameraChunkPosX, float cameraChunkPosZ)
{
    auto& chunk = world->find({
        cameraChunkPosX + Chunk::chunkSize * xOffset,
        cameraChunkPosZ + Chunk::chunkSize * zOffset
    });

    for (auto& view : chunk.views) {
        view->draw();
    }
}

void Renderer::updateViewport(int width, int height)
{
	glViewport(0, 0, width, height);
    updateProjectionMatrix();
}

void Renderer::initialize(Camera* _camera, World* _world)
{
    camera = _camera;
    world  = _world;
    CylinderMesh::createRaw();
    SphereMesh::createRaw(10, 10);
    ui.initialize();
}

void Renderer::render(GLFWwindow* window)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera->updateView(world->getPlayer().getPosition());
    auto& view = camera->getViewMatrix();

    for (auto& shader : Shader::getAll()) {
        shader->useProgram();

        glUniformMatrix4fv(shader->getUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(view));
        world->getSun().setLightUniforms(shader);

        if (shader->isTimeBased()) {
            world->getWind().setUniforms(shader);
        }
    }

    auto viewPosition = world->getPlayer().getPosition();
    float viewChunkCenterX = viewPosition.x - (float)fmod(viewPosition.x, Chunk::chunkSize);
    float viewChunkCenterZ = viewPosition.z - (float)fmod(viewPosition.z, Chunk::chunkSize);

    for (int i = -renderHalfSize; i < renderHalfSize; i++) {
        for (int j = -renderHalfSize; j < renderHalfSize; j++)
        {
            auto& chunk = world->find({
                viewChunkCenterX + Chunk::chunkSize * i,
                viewChunkCenterZ + Chunk::chunkSize * j
            });

            for (auto& view : chunk.views) {
                view->draw();
            }
        }
    }

    world->getPlayer().getView()->draw();
    ui.draw();
    glfwSwapBuffers(window);
}
