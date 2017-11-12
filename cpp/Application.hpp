#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <string>

#include "SdlManager.hpp"
//#include "Shader.hpp"
//#include "Camera.hpp"
//#include "Mesh.hpp"
//#include "Texture.hpp"

class Application final
{
public:
    Application();
    void start();
protected:
    void loop();
    void handleEvents();
    void update(float dt, double currentTime);
    void render();
    void finish();
private:
    static const float sTimePerFrame;
    static const unsigned int sInitialWindowWidth;
    static const unsigned int sInitialWindowHeight;
    static const std::string sTitleString;
    static const std::string sVertShader;
    static const std::string sFragShader;
    SdlManager mSdlManager; // must initialize early to create OpenGL context
//    Camera mCamera;
//    Mesh mMesh;
//    Texture mTexture;
    float mZoom;
    bool mZoomGoingUp;
    float mTimeOffset;

    //Text Renderer

//    Shader mShader;
    bool mAppIsRunning;
    float mAccumulator;
    float mTimeSinceLastUpdate;
    unsigned int mFrameCounter;
private:
    void printFrameData(float dt);
    void init();
    void sdlEvents(SDL_Event& event);
};

#endif // APPLICATION_HPP
