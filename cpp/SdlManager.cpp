#include "SdlManager.hpp"

#include <sstream>
#include <cassert>

/**
 * @brief SdlManager::SdlManager
 * @param dimensions
 * @param title
 * @param context = Settings::Context()
 * @param window = Settings::Window()
 * @param logPriority = SDL_LOG_PRIORITY_VERBOSE
 */
SdlManager::SdlManager(const glm::uvec2& dimensions,
    const std::string& title,
    const Settings::Context& context,
    const Settings::Window& window,
    SDL_LogPriority logPriority)
: mDimensions(dimensions)
, cTitleString(title)
, mContextSettings(context)
, mWindowSettings(window)
{
    SDL_LogSetAllPriority(logPriority);

    initWindow(mWindowSettings.initFlags);
    if (mWindowSettings.initFlags & SDL_INIT_JOYSTICK)
        initJoysticks();
    if (mWindowSettings.initFlags & SDL_INIT_HAPTIC)
        initHaptic();

    // Only load OpenGL functions after SDL window is created
    loadGL();
}

SdlManager::~SdlManager()
{
    if (mSDL_Window)
        cleanUp();
}

void SdlManager::cleanUp()
{
    destroyWindow();
}

/**
 * @brief SdlManager::initWindow
 * @param flags
 */
void SdlManager::initWindow(Uint32 flags)
{
    if (SDL_Init(flags) < 0)
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, SDL_GetError());

    // Set up the GL attributes
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, mContextSettings.pixelSize.r);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, mContextSettings.pixelSize.g);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, mContextSettings.pixelSize.b);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, mContextSettings.pixelSize.a);

    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 24);

    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, mContextSettings.depthSize);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, mContextSettings.stencilSize);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, mContextSettings.openglContext);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, mContextSettings.openglMajorMinor.x);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, mContextSettings.openglMajorMinor.y);

#if defined(APP_DESKTOP)
    if (mWindowSettings.fullScreen)
    {
        mSDL_Window = SDL_CreateWindow(cTitleString.c_str(), 0, 0,
            static_cast<int>(mDimensions.x), static_cast<int>(mDimensions.y),
            mWindowSettings.windowFlags);
    }
    else
    {
        mSDL_Window = SDL_CreateWindow(cTitleString.c_str(),
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            static_cast<int>(mDimensions.x), static_cast<int>(mDimensions.y),
            mWindowSettings.windowFlags);
    }
#elif defined(APP_ANDROID)
    SDL_DisplayMode mode;
    SDL_GetDisplayMode(0, 0, &mode);
    mDimensions.x = static_cast<float>(mode.w);
    mDimensions.y = static_cast<float>(mode.h);

    mSDL_Window = SDL_CreateWindow(nullptr, 0, 0, mode.w, mode.h, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
#endif // defined

    if (mSDL_Window == 0)
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, SDL_GetError());

    mGL_Context = SDL_GL_CreateContext(mSDL_Window);

    // Sometimes Vsync is enabled by default
    if (mWindowSettings.vSync && SDL_GL_SetSwapInterval(1) < 0)
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Vsync mode is not available\n");
    else
        SDL_GL_SetSwapInterval(0);
}

void SdlManager::initJoysticks()
{
    // setup joystick
    mSDL_Joystick = SDL_JoystickOpen(0);
    if (!mSDL_Joystick)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Joystick 0 did not initialize\n");
    }
}

void SdlManager::initHaptic()
{
    mSDL_Haptic = SDL_HapticOpenFromJoystick(mSDL_Joystick);
    if (!mSDL_Haptic)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "This controller does not support haptic feedback\n");
    }
    else
    {
        if (SDL_HapticRumbleInit(mSDL_Haptic) < 0)
        {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL haptic did not initialize the rumble\n");
        }
    }
}

void SdlManager::destroyWindow()
{
    SDL_GL_DeleteContext(mGL_Context);
    SDL_DestroyWindow(mSDL_Window);
    SDL_Quit();
}

/**
 * Only loads on desktop since mobile uses OpenGL ES
 * @brief SdlManager::loadGL
 */
void SdlManager::loadGL()
{
#if defined(APP_DESKTOP)
    // Load the OpenGL functions (glLoadGen).
    if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Error loading glLoadGen");
        destroyWindow();
        throw new std::runtime_error("Could not load OpenGL functions\n");
    }
#endif // defined
}

std::string SdlManager::getContextString(int context) const
{
    switch (context)
    {
        case SDL_GL_CONTEXT_PROFILE_CORE: return "Core GL Context";
        case SDL_GL_CONTEXT_PROFILE_ES: return "ES GL Context";
        case SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG: return "Forward GL Context";
        //case SDL_GL_CONTEXT_DEBUG_FLAG: return "Debug GL Context";
        default: return "Unknown GL context";
    }
}

void SdlManager::printSDLInfo() const
{
    int context, major, minor;
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, &context);
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &major);
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minor);

    assert(major = mContextSettings.openglMajorMinor.x);
    assert(minor = mContextSettings.openglMajorMinor.y);

    std::string contextStr = getContextString(context);

    std::stringstream ss;
    ss << "\nPrinting SdlManager info:\n";
    ss << "Vsync: " << mWindowSettings.vSync << "\n";
    ss << "Fullscreen: " << mWindowSettings.fullScreen << "\n";
    ss << "Window (width, height): " << "(" << mDimensions.x << ", " << mDimensions.y << ")\n";
    ss << "The number of connected joysticks: " << SDL_NumJoysticks() << "\n";
    ss << "The GL context is : " << contextStr << "\n";
    ss << "Major, Minor versions: " << major << ", " << minor << "\n";
    SDL_Log(ss.str().c_str());
}

/**
 * @brief SdlManager::swapBuffers
 */
void SdlManager::swapBuffers() const
{
    SDL_GL_SwapWindow(mSDL_Window);
}

/**
 * @brief SdlManager::hapticRumblePlay
 * @param strength
 * @param length
 * @return
 */
bool SdlManager::hapticRumblePlay(float strength, float length) const
{
    return static_cast<bool>(SDL_HapticRumblePlay(mSDL_Haptic, strength, length));
}

/**
 * @brief SdlManager::buildBufferFromFile
 * @param filename
 * @param bufferSize
 * @return
 */
unsigned char*SdlManager::buildBufferFromFile(const std::string& filename, long& bufferSize) const
{
    SDL_RWops* rwOps = SDL_RWFromFile(filename.c_str(), "rb");

    if (rwOps)
    {
        long fileSize = SDL_RWsize(rwOps);
        unsigned char* result = static_cast<unsigned char*>(malloc(fileSize + 1));
        long numberReadTotal = 0;
        long numberRead = 1;

        unsigned char* buffer = result;

        while (numberRead < fileSize && numberRead != 0)
        {
            numberRead = SDL_RWread(rwOps, buffer, 1, (fileSize - numberReadTotal));
            numberReadTotal += numberRead;
            buffer += numberRead;
        }

        SDL_RWclose(rwOps);

        if (numberReadTotal != fileSize)
        {
            free(result);
        }

        result[numberReadTotal] = '\0';

        bufferSize = fileSize;

        return result;
    }
    else
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, SDL_GetError());
        return nullptr;
    }
}

/**
 * @brief SdlManager::buildStringFromFile
 * @param filename
 * @return
 */
std::string SdlManager::buildStringFromFile(const std::string& filename) const
{
    std::string returnStr;
    SDL_RWops* rwOps = SDL_RWFromFile(filename.c_str(), "r");

    if (rwOps)
    {
        long fileSize = SDL_RWsize(rwOps);
        char* result = static_cast<char*>(malloc(fileSize + 1));
        long numberReadTotal = 0;
        long numberRead = 1;

        char* buffer = result;

        while (numberRead < fileSize && numberRead != 0)
        {
            numberRead = SDL_RWread(rwOps, buffer, 1, (fileSize - numberReadTotal));
            numberReadTotal += numberRead;
            buffer += numberRead;
        }

        SDL_RWclose(rwOps);

        if (numberReadTotal != fileSize)
        {
            free(result);
        }

        result[numberReadTotal] = '\0';

        returnStr.assign(result, fileSize);
        free(result);
    }
    else
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, SDL_GetError());
    }

    return returnStr;
}

/**
 * @brief SdlManager::switchFullScreenMode
 */
void SdlManager::switchFullScreenMode()
{
    mWindowSettings.fullScreen = !mWindowSettings.fullScreen;
    if (mWindowSettings.fullScreen)
        SDL_SetWindowFullscreen(mSDL_Window, SDL_TRUE);
    else
        SDL_SetWindowFullscreen(mSDL_Window, SDL_FALSE);
}

bool SdlManager::isFullScreen() const
{
    return mWindowSettings.fullScreen;
}

void SdlManager::setDimensions(const glm::uvec2& dimensions)
{
    mDimensions = dimensions;
}

glm::uvec2 SdlManager::getDimensions() const
{
    return mDimensions;
}

SDL_Window*SdlManager::getSDL_Window() const
{
    return mSDL_Window;
}

Settings::Context SdlManager::getContextSettings() const
{
    return mContextSettings;
}

Settings::Window SdlManager::getWindowSettings() const
{
    return mWindowSettings;
}
