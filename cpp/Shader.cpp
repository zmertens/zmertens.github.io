#include "Shader.hpp"

#include <cstring>

#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const SdlManager& sdlManager)
: mSdlManager(sdlManager)
{
    createProgram();
}

Shader::~Shader()
{
    if (mProgram)
        cleanUp();
}

void Shader::compileAndAttachShader(const int shaderType, const std::string& filename)
{
    std::string shaderCode = mSdlManager.buildStringFromFile(filename);

    mFileLocations.emplace(shaderType, filename);
    unsigned int shaderId = compile(shaderType, shaderCode);

    attach(shaderId);

    deleteShader(shaderId);
}

void Shader::linkProgram()
{
    glLinkProgram(mProgram);

    GLint success;
    GLchar infoLog[512];

    glGetProgramiv(mProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(mProgram, 512, nullptr, infoLog);
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Program link failed: %s\n", infoLog);
    }
}

void Shader::bind() const
{
    glUseProgram(mProgram);
}

void Shader::release() const
{
    glUseProgram(0);
}

unsigned int Shader::compile(const int shaderType, const std::string& shaderCode)
{
    GLint length = shaderCode.length();
    const GLchar* glShaderString = shaderCode.c_str();

    GLenum glType = getShaderType(shaderType);

    GLint success;
    GLchar infoLog[512];

    GLuint shaderId = glCreateShader(glType);

    glShaderSource(shaderId, 1, &glShaderString, &length);
    glCompileShader(shaderId);
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(shaderId, 512, nullptr, infoLog);
        SDL_LogError(SDL_LOG_CATEGORY_ERROR,
            "\n%s -- Shader Compilation Failed: %s\n", mFileLocations.at(shaderType).c_str(), infoLog);
    }
    else if (success && APP_DEBUG)
    {
        SDL_Log("\n%s compiled successfully\n", mFileLocations.at(shaderType).c_str(), infoLog);
    }

    return shaderId;
}

void Shader::attach(unsigned int shaderId)
{
    glAttachShader(mProgram, static_cast<GLuint>(shaderId));
}

void Shader::createProgram()
{
    mProgram = glCreateProgram();
}

void Shader::deleteShader(GLuint shaderId)
{
    glDeleteShader(shaderId);
}

void Shader::deleteProgram(GLint shaderId)
{
    glDeleteProgram(shaderId);
}

void Shader::cleanUp()
{
    deleteProgram(mProgram);
    mGlslLocations.clear();
    mFileLocations.clear();
}

void Shader::setUniform(const std::string& str, const glm::mat3& matrix)
{
    glUniformMatrix3fv(getUniformLocation(str), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setUniform(const std::string& str, const glm::mat4& matrix)
{
    glUniformMatrix4fv(getUniformLocation(str), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setUniform(const std::string& str, const glm::vec2& vec)
{
    glUniform2f(getUniformLocation(str), vec.x, vec.y);
}

void Shader::setUniform(const std::string& str, const glm::vec3& vec)
{
    glUniform3f(getUniformLocation(str), vec.x, vec.y, vec.z);
}

void Shader::setUniform(const std::string& str, const glm::vec4& vec)
{
    glUniform4f(getUniformLocation(str), vec.x, vec.y, vec.z, vec.w);
}

void Shader::setUniform(const std::string& str, GLfloat arr[][2], unsigned int count)
{
    glUniform2fv(getUniformLocation(str), count, arr[0]);
}

void Shader::setUniform(const std::string& str, GLint arr[], const unsigned int count)
{
    glUniform1iv(getUniformLocation(str), count, arr);
}

void Shader::setUniform(const std::string& str, GLfloat arr[], unsigned int count)
{
    glUniform1fv(getUniformLocation(str), count, arr);
}

void Shader::setUniform(const std::string& str, GLfloat value)
{
    glUniform1f(getUniformLocation(str), value);
}

void Shader::setUniform(const std::string& str, GLint value)
{
    glUniform1i(getUniformLocation(str), value);
}

void Shader::setUniform(const std::string& str, GLuint value)
{
    glUniform1ui(getUniformLocation(str), value);
}

GLint Shader::getUniformLocation(const std::string& str)
{
    auto iter = mGlslLocations.find(str);
    if (iter == mGlslLocations.end())
    {
        GLint loc = glGetUniformLocation(mProgram, str.c_str());
        if (loc == -1 && APP_DEBUG)
        {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "\n%s does not exist in the shader\n", str.c_str());
        }
        else
        {
            mGlslLocations.emplace(str, loc);
        }

        return loc;
    }
    else
    {
        return mGlslLocations.at(str);
    }
}

GLint Shader::getAttribLocation(const std::string& str)
{
    return glGetAttribLocation(mProgram, str.c_str());
}

/**
 * @brief Shader::getStringFromType
 * @param type
 * @return
 */
std::string Shader::getStringFromType(GLenum type) const
{
    switch (type)
    {
        case GL_FLOAT: return std::string("float");
        case GL_FLOAT_VEC2: return std::string("vec2");
        case GL_FLOAT_VEC3: return std::string("vec3");
        case GL_FLOAT_VEC4: return std::string("vec4");
#if defined(APP_DESKTOP)
        case GL_DOUBLE: return std::string("double");
#endif // defined
        case GL_INT: return std::string("int");
        case GL_UNSIGNED_INT: return std::string("unsigned int");
        case GL_BOOL: return std::string("bool");
        case GL_FLOAT_MAT2: return std::string("mat2");
        case GL_FLOAT_MAT3: return std::string("mat3");
        case GL_FLOAT_MAT4: return std::string("mat4");
        default: return std::string("Unknown GLenum type.");
    }
}

void Shader::bindAttribLocation(const std::string& str, unsigned int loc)
{
    glBindAttribLocation(mProgram, loc, str.c_str());
}

unsigned int Shader::getProgramHandle() const
{
    return static_cast<unsigned int>(mProgram);
}

const SdlManager & Shader::getSdlManager() const
{
    return mSdlManager;
}

std::unordered_map<int, std::string> Shader::getFileLocations() const
{
    return mFileLocations;
}

GLenum Shader::getShaderType(const int shaderType) const
{
    switch (shaderType)
    {
        case ShaderTypes::VERTEX_SHADER:
            return GL_VERTEX_SHADER;

        case ShaderTypes::FRAGMENT_SHADER:
            return GL_FRAGMENT_SHADER;
    }
}

std::unordered_map<std::string, GLint> Shader::getGlslLocations() const
{
    return mGlslLocations;
}
