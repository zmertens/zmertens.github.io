#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <memory>
#include <unordered_map>

#include <glm/glm.hpp>

#include "SdlManager.hpp"

namespace ShaderTypes
{
    const int VERTEX_SHADER = 0;
    const int FRAGMENT_SHADER = 1;
}

class Shader final
{
public:
    typedef std::unique_ptr<Shader> Ptr;
public:
    explicit Shader(const SdlManager & sdlManager);
    virtual ~Shader();

    void compileAndAttachShader(const int shaderType, const std::string& filename);
    void linkProgram();
    void bind() const;
    void release() const;

    void cleanUp();

    void printUniforms() const;
    void printActiveAttribs() const;
    void setUniform(const std::string& str, const glm::mat3& matrix);
    void setUniform(const std::string& str, const glm::mat4& matrix);
    void setUniform(const std::string& str, const glm::vec2& vec);
    void setUniform(const std::string& str, const glm::vec3& vec);
    void setUniform(const std::string& str, const glm::vec4& vec);
    void setUniform(const std::string& str, GLfloat arr[][2], unsigned int count);
    void setUniform(const std::string& str, GLint arr[], unsigned int count);
    void setUniform(const std::string& str, GLfloat arr[], unsigned int count);
    void setUniform(const std::string& str, GLfloat value);
    void setUniform(const std::string& str, GLint value);
    void setUniform(const std::string& str, GLuint value);
    void setSubroutine(GLenum shaderType, GLuint count, const std::string& name);
    void setSubroutine(GLenum shaderType, GLuint count, GLuint index);
    void bindFragDataLocation(const std::string& str, unsigned int loc);
    void bindAttribLocation(const std::string& str, unsigned int loc);
    unsigned int getProgramHandle() const;
    GLenum getShaderType(const int shaderType) const;
    const SdlManager& getSdlManager() const;
    std::unordered_map<std::string, GLint> getGlslLocations() const;
    std::unordered_map<int, std::string> getFileLocations() const;

private:
    const SdlManager& mSdlManager;
    GLint mProgram;
    std::unordered_map<std::string, GLint> mGlslLocations;
    std::unordered_map<int, std::string> mFileLocations;
private:
    Shader(const Shader& other);
    Shader& operator=(const Shader& other);
    unsigned int compile(const int shaderType, const std::string& shaderCode);
    void attach(unsigned int shaderId);
    void createProgram();
    void deleteShader(GLuint shaderId);
    void deleteProgram(GLint shaderId);
    GLint getUniformLocation(const std::string& str);
    GLint getAttribLocation(const std::string& str);
    std::string getStringFromType(GLenum shaderType) const;
};

#endif // SHADER_HPP
