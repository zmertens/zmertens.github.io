#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>
#include <memory>

#include <glm/glm.hpp>

#include "Config.hpp"

#if defined(APP_DESKTOP)
#include <SDL2/SDL.h>
#include <SDL2/SDL_log.h>
#include "../extlibs/gl_core_3_3.h"
#elif defined(APP_ANDROID)
#include <SDL.h>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#endif // defined

namespace Settings
{
struct Context {
    glm::ivec4 pixelSize;
    int depthSize;
    int stencilSize;
    int numSamples;
    glm::vec2 openglMajorMinor;
    SDL_GLprofile openglContext;

    Context(const glm::ivec4& pixel_size = glm::ivec4(8, 8, 8, 8),
        int depth = 8, int stencil = 8, int antialias = 0,
        const glm::ivec2& glVersion = glm::ivec2(3, 3),
        SDL_GLprofile GL_Context = SDL_GL_CONTEXT_PROFILE_CORE)
    : pixelSize(pixel_size)
    , depthSize(depth)
    , stencilSize(stencil)
    , numSamples(antialias)
    , openglMajorMinor(glVersion)
    , openglContext(GL_Context)
    {

    }
};

/**
 * Possible window flag values:
 * SDL_INIT_TIMER
 * SDL_INIT_AUDIO
 * SDL_INIT_VIDEO
 * SDL_INIT_JOYSTICK
 * SDL_INIT_HAPTIC // force feedback
 * SDL_INIT_GAMECONTROLLER
 * SDL_INIT_EVENTS
 * SDL_INIT_EVERYTHING // all of the above
 * SDL_INIT_NOPARACHUTE
 * compatibility; this flag is ignored
 * @brief The Window struct
 */
struct Window {
    Uint32 initFlags;
    Uint32 windowFlags;
    bool vSync;
    bool fullScreen;
    Window(Uint32 init_flags = SDL_INIT_EVERYTHING,
        Uint32 window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN,
        bool vsync = false, bool fullscreen = false)
    : initFlags(init_flags)
    , windowFlags(window_flags)
    , vSync(vsync)
    , fullScreen(fullscreen)
    {

    }
};
} // namespace

/**
 * Uber class that manages SDL2 library and OpenGL context.
 * @brief The SdlManager class
 */
class SdlManager final
{
public:
    typedef std::unique_ptr<SdlManager> Ptr;
public:
    explicit SdlManager(const glm::uvec2& dimensions,
        const std::string& title,
        const Settings::Context& context = Settings::Context(),
        const Settings::Window& window = Settings::Window(),
        SDL_LogPriority logPriority = SDL_LOG_PRIORITY_VERBOSE);
    virtual ~SdlManager();

    void cleanUp();

    void printSDLInfo() const;
    void swapBuffers() const;
    bool hapticRumblePlay(float strength, float length) const;

    unsigned char* buildBufferFromFile(const std::string& filename, long& bufferSize) const;
    std::string buildStringFromFile(const std::string& filename) const;

    void switchFullScreenMode();
    bool isFullScreen() const;
    void setDimensions(const glm::uvec2& dimensions);
    glm::uvec2 getDimensions() const;
    SDL_Window* getSDL_Window() const;
    Settings::Context getContextSettings() const;
    Settings::Window getWindowSettings() const;
private:
    glm::uvec2 mDimensions;
    const std::string cTitleString;
    Settings::Context mContextSettings;
    Settings::Window mWindowSettings;
    SDL_Window* mSDL_Window;
    SDL_GLContext mGL_Context;
    SDL_Joystick* mSDL_Joystick;
    SDL_Haptic* mSDL_Haptic;
private:
    SdlManager(const SdlManager & other);
    SdlManager & operator=(const SdlManager & other);
    void initWindow(Uint32 flags);
    void initJoysticks();
    void initHaptic();
    void destroyWindow();
    void loadGL();
    std::string getContextString(int context) const;
};

#endif // WINDOW_HPP
