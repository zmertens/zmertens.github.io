#include "Sprite.hpp"

#include "../ResourceManager.hpp"
#include "../Camera.hpp"
#include "../SdlWindow.hpp"

/**
 * @brief Sprite::Sprite
 * @param config
 * @param position = glm::vec3(0.0f)
 * @param rotation = glm::vec3(0.0f)
 * @param scale = glm::vec3(1.0f)
 */
Sprite::Sprite(const Draw::Config& config,
    const glm::vec3& position,
    const glm::vec3& rotation,
    const glm::vec3& scale)
: mConfig(config)
, mTransform(position, rotation, scale)
, mCounter(0.0f)
{

}

/**
 * @brief Sprite::update
 * @param dt
 * @param timeSinceInit
 */
void Sprite::update(float dt, double timeSinceInit)
{
    // mCounter += glm::two_pi<float>() / dt;
    // if (mCounter > glm::two_pi<float>())
    //     mCounter -= glm::two_pi<float>();

    // mTransform.setRotation(glm::vec3(mCounter * glm::radians(0.15f),
    //     mCounter * glm::radians(0.25f),
    //     0));
}

/**
 * @brief Sprite::draw
 * @param sdlManager
 * @param rm
 * @param camera
 * @param type = IMesh::Draw::TRIANGLES
 */
void Sprite::draw(const SdlWindow& sdlManager,
    ResourceManager& rm,
    const Camera& camera,
    const IMesh::Draw type) const
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    auto& shader = rm.getShader(mConfig.shaderId);
    shader->bind();

    auto& tex = rm.getTexture(mConfig.textureId);
    tex->bind();

    auto mv = mTransform.getModelView(camera.getLookAt());
    auto persp = camera.getPerspective(sdlManager.getAspectRatio());
    shader->setUniform("uProjMatrix", persp);
    shader->setUniform("uModelViewMatrix", mv);
    shader->setUniform("uTexOffset0", mConfig.texAtlasOffset);

    auto& mesh = rm.getMesh(mConfig.meshId);
    mesh->draw(type, 1);

    glDisable(GL_BLEND);
} // draw

void Sprite::cleanUp()
{

}

Transform Sprite::getTransform() const
{
    return mTransform;
}

void Sprite::setTransform(const Transform& transform)
{
    mTransform = transform;
}
