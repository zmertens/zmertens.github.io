#include "GlUtils.hpp"

#include "Utils.hpp"

/**
 * @brief GlUtils::checkForOpenGLError
 * @param file
 * @param line
 * @return
 */
bool GlUtils::CheckForOpenGLError(const std::string& file, int line)
{
    bool error = false;
    GLenum glErr;
    glErr = glGetError();
    while (glErr != GL_NO_ERROR)
    {
        std::string message = "";
        switch(glErr)
        {
            case GL_INVALID_ENUM:
                message = "Invalid enum";
                break;
            case GL_INVALID_VALUE:
                message = "Invalid value";
                break;
            case GL_INVALID_OPERATION:
                message = "Invalid operation";
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                message = "Invalid framebuffer operation";
                break;
            case GL_OUT_OF_MEMORY:
                message = "Out of memory";
                break;
            default:
                message = "Unknown error";
        }

        std::string fileError = "glError in file " + file + " @ line " + Utils::toString(line) + ", error message: " +  message;
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, fileError.c_str());
        glErr = glGetError();
        error = !error;
    }
    return error;
}
