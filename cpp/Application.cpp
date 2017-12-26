#include "Application.hpp"

#include "Utils.hpp"

#if APP_DEBUG == 1
//#include "GlUtils.hpp"
#endif

const float Application::sTimePerFrame = 1.0f / 60.0f;
const unsigned int Application::sInitialWindowWidth = 480u;
const unsigned int Application::sInitialWindowHeight = 800u;
const std::string Application::sTitleString = "Julia";
const std::string Application::sVertShader = "shaders/julia.vert.glsl";
const std::string Application::sFragShader = "shaders/julia.frag.glsl";

Application::Application()
: mSdlManager(sInitialWindowWidth, sInitialWindowHeight, sTitleString,
    Settings::Context(glm::ivec4(5, 6, 5, 8),
        8, 8, 0, glm::vec2(3, 0), SDL_GL_CONTEXT_PROFILE_ES),
    Settings::Window(SDL_INIT_VIDEO,
        SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN,
        false, true),
    SDL_LOG_PRIORITY_VERBOSE)
//, mCamera(glm::vec3(0.0f, 0.0f, 1.0f))
//, mMesh()
//, mTexture(128, 1, 0)
, mTimeOffset(0.0f)
// , mImGuiHelper(mSdlManager)
//, mShader(mSdlManager)
, mAppIsRunning(false)
, mAccumulator(0.0f)
, mTimeSinceLastUpdate(0.0f)
, mFrameCounter(0u)
{
    init();

    glClearColor(0.3f, 0.2f, 0.4f, 1.0f);

    if (APP_DEBUG)
    {
        mSdlManager.printSDLInfo();
    }
}

void Application::start()
{
    mAppIsRunning = true;
    loop();
}

void Application::loop()
{
    while (mAppIsRunning)
    {
        static float lastTime = static_cast<float>(SDL_GetTicks()) / 1000.0f;
        double currentTime = static_cast<double>(SDL_GetTicks()) / 1000.0f;
        float deltaTime = static_cast<float>(currentTime) - lastTime;
        lastTime = currentTime;
        mAccumulator += deltaTime;

        while (mAccumulator > sTimePerFrame)
        {
            mAccumulator -= sTimePerFrame;
            handleEvents();
            update(sTimePerFrame, currentTime);
        }

        render();

        printFrameData(deltaTime);
    }

    finish();
}

void Application::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        sdlEvents(event);
    } // end while
}

void Application::update(float dt, double currentTime)
{
    float r = currentTime + mTimeOffset;

}

void Application::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::uvec2 dimens = mSdlManager.getDimensions();
    float ar = static_cast<float>(dimens.x) / static_cast<float>(dimens.y);

//    mShader.bind();

//    mShader.setUniform("uZoom", mZoom);
//    mShader.setUniform("uOffset", mZoffset);
//    mShader.setUniform("C", mC);

//    mTexture.bind();


#if APP_DEBUG == 1
//    GlUtils::CheckForOpenGLError(__FILE__, __LINE__);
#endif

//    mMesh.draw(GL_TRIANGLES);

#if APP_DEBUG == 1
//    GlUtils::CheckForOpenGLError(__FILE__, __LINE__);
#endif

    // mImGuiHelper.render();

#if APP_DEBUG == 1
//    GlUtils::CheckForOpenGLError(__FILE__, __LINE__);
#endif

    mSdlManager.swapBuffers();
}

void Application::finish()
{
    mAppIsRunning = false;
//    mMesh.cleanUp();
//    mShader.cleanUp();
    // mImGuiHelper.cleanUp();
    mSdlManager.cleanUp();
}

/**
 * @brief Application::printFrameData
 * @param dt
 */
void Application::printFrameData(float dt)
{
    ++mFrameCounter;
    mTimeSinceLastUpdate += dt;
    if (mTimeSinceLastUpdate >= 1.0f)
    {
        std::string fpsLog = "FPS: " + Utils::toString(mFrameCounter) + "\n";
        std::string timePerFrame = "time: (us) / frame: " + Utils::toString(mTimeSinceLastUpdate / mFrameCounter) + "\n";
        if (APP_DEBUG)
        {
            SDL_Log(fpsLog.c_str());
            SDL_Log(timePerFrame.c_str());
        }

        // use ImGUi helper to update overlay
        std::vector<std::string> fpsStrings = {
                std::string("FPS: " + Utils::toString(mFrameCounter)),
                std::string("time: (us) / frame: " + Utils::toString(mTimeSinceLastUpdate / mFrameCounter))
        };
        // mImGuiHelper.updateOverlay(fpsStrings);

        mFrameCounter = 0;
        mTimeSinceLastUpdate -= 1.0f;
    }
}

void Application::init()
{
//    mShader.compileAndAttachShader(ShaderTypes::VERTEX_SHADER, sVertShader);
//    mShader.compileAndAttachShader(ShaderTypes::FRAGMENT_SHADER, sFragShader);
//    mShader.linkProgram();
//    mShader.bind();
}

void Application::sdlEvents(SDL_Event& event)
{
    if (event.type == SDL_QUIT)
    {
        mAppIsRunning = false;
    }
    else if (event.type == SDL_WINDOWEVENT)
    {
        if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
        {
            unsigned int newWidth = event.window.data1;
            unsigned int newHeight = event.window.data2;
            glViewport(0, 0, newWidth, newHeight);
//        mSdlManager.setDimensions(glm::uvec2(newWidth, newHeight));
            if (APP_DEBUG)
            {
                std::string resizeDimens = "Resize Event -- Width: "
                                           + Utils::toString(newWidth) + ", Height: "
                                           + Utils::toString(newHeight) + "\n";
                SDL_Log(resizeDimens.c_str());
            }
        }
    }
    else if (event.type == SDL_FINGERMOTION)
    {
//            glm::vec2 dimensions = mSdlManager.getDimensions();
//            touchX = event.tfinger.x * dimensions.x;
//            touchY = event.tfinger.y * dimensions.y;
//        if (mZoomGoingUp)
//            mZoom *= 1.02f;
//        else
//            mZoom /= 1.02f;
//
//        if (mZoom > 50.0f || mZoom < 1.0f)
//            mZoomGoingUp = !mZoomGoingUp;
    }
    else if (event.type == SDL_FINGERDOWN)
    {
//            glm::vec2 dimensions = mSdlManager.getDimensions();
//            touchX = event.tfinger.x * dimensions.x;
//            touchY = event.tfinger.y * dimensions.y;
    }
} // sdlEvents
