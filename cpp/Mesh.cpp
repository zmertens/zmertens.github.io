#include "Mesh.hpp"

#include <vector>

Mesh::Mesh()
: mNumVertices(16)
, mNumIndices(6)
{
    genBuffers();
    initMesh();
}

/**
 * @brief Mesh::update
 * @param dt
 * @param timeSinceInit
 */
void Mesh::update(float dt, double timeSinceInit)
{

}

void Mesh::draw(GLenum type) const
{
    glBindVertexArray(mVaoHandle);
    glDrawElements(type, mNumIndices, GL_UNSIGNED_SHORT, 0);
    if (APP_DEBUG)
    {
        glBindVertexArray(0);
    }
}

/**
 * @brief Mesh::cleanUp
 */
void Mesh::cleanUp()
{
    glDeleteVertexArrays(1, &mVaoHandle);
    glDeleteBuffers(1, &mVboHandle);
    glDeleteBuffers(1, &mIboHandle);
}

/**
 * @brief Mesh::genBuffers
 */
void Mesh::genBuffers()
{
    glGenVertexArrays(1, &mVaoHandle);
    glGenBuffers(1, &mVboHandle);
    glGenBuffers(1, &mIboHandle);
}

/**
 * @brief Mesh::initMesh
 */
void Mesh::initMesh()
{
    static GLfloat vertices[] = {
            -1.0f,  -1.0f, 0.0f, 1.0f,   // top left
             1.0f,  -1.0f, 0.0f, 1.0f,  // bottom left
             1.0f,   1.0f, 0.0f, 1.0f,   // bottom right
            -1.0f,   1.0f, 0.0f, 1.0f }; // top right

    static GLushort indices[] = { 0, 1, 2, 0, 2, 3 }; // order to draw vertices

    glBindVertexArray(mVaoHandle);
    glBindBuffer(GL_ARRAY_BUFFER, mVboHandle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // vertex position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(0));
    // indices data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIboHandle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    if (APP_DEBUG == 1)
        glBindVertexArray(0);
}
