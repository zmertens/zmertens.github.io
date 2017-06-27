#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "SdlManager.hpp"

class Texture
{
public:
    explicit Texture(const SdlManager& sdlManager,
        const std::string& fileName,
        unsigned int channel = 0);
    explicit Texture(const unsigned int width, const unsigned int height,
        unsigned int channel = 0);

    void cleanUp();
    void bind() const;
    void release() const;
    unsigned int getHandle() const;

protected:
    void genTexture();
    void init(unsigned char* str, long bufferSize);
    void init(const unsigned int width, const unsigned int height);

private:
    static const GLubyte scPalette[];
    GLuint mChannel;
    GLenum mTarget;
    GLenum mInternalFormat;
    GLenum mPixelFormat;
    GLenum mWrapS;
    GLenum mWrapT;
    GLenum mMinFilter;
    GLenum mMagFilter;
    GLuint mHandle;
};

#endif // TEXTURE_HPP
