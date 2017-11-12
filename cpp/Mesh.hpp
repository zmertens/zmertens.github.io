#ifndef MESH_HPP
#define MESH_HPP

#include <vector>

#include "SdlManager.hpp"

class Mesh
{
public:
    explicit Mesh();

    void update(float dt, double timeSinceInit);
    void draw(GLenum type) const;
    void cleanUp();

private:
    void genBuffers();
    void initMesh();
private:
    GLuint mVaoHandle;
    GLuint mVboHandle;
    GLuint mIboHandle;
    GLuint mNumVertices;
    GLuint mNumIndices;
};

#endif // MESH_HPP
