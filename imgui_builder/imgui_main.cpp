// em++ -O2 -s USE_SDL=2 -s FULL_ES2=1 -I ../.. imgui_main.cpp imgui_impl_sdl.cpp imgui*.cpp -o html/index.html

// ImGui - standalone example application for SDL2 + OpenGL ES 2 + Emscripten

// #include <imgui/imgui.h>
// #include "imgui_impl_sdl.h"
#include <cstdio>
#include <SDL.h>
#include <SDL_opengl.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

bool g_done = false;
SDL_Window* g_window;
bool g_show_test_window = true;
bool g_show_another_window = false;
// ImVec4 g_clear_color = ImColor(114, 144, 154);

void main_loop()
{
    // SDL_Event event;
    // while (SDL_PollEvent(&event))
    // {
    //     ImGui_ImplSdl_ProcessEvent(&event);
    //     if (event.type == SDL_QUIT)
    //         g_done = true;
    // }
    // ImGui_ImplSdl_NewFrame(g_window);
    //
    // // 1. Show a simple window
    // // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
    // {
    //     static float f = 0.0f;
    //     ImGui::Text("Hello, world!");
    //     ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
    //     ImGui::ColorEdit3("clear color", (float*)&g_clear_color);
    //     if (ImGui::Button("Test Window")) g_show_test_window ^= 1;
    //     if (ImGui::Button("Another Window")) g_show_another_window ^= 1;
    //     ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    // }
    //
    // // 2. Show another simple window, this time using an explicit Begin/End pair
    // if (g_show_another_window)
    // {
    //     ImGui::SetNextWindowSize(ImVec2(200,100), ImGuiSetCond_FirstUseEver);
    //     ImGui::Begin("Another Window", &g_show_another_window);
    //     ImGui::Text("Hello");
    //     ImGui::End();
    // }
    //
    // // 3. Show the ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
    // if (g_show_test_window)
    // {
    //     ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
    //     ImGui::ShowTestWindow(&g_show_test_window);
    // }

typedef struct g_clear_color {
    float x, y, z, w;

    g_clear_color(float xx = 0.0081f,
        float yy = 0.323f,
        float zz = 0.7711f,
        float ww = 0.01233f)
    : x(xx), y(yy), z(zz), w(ww)
    {

    }
} g_clear_color;

    g_clear_color clearColor;

    // Rendering
    // glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
    glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
    glClear(GL_COLOR_BUFFER_BIT);
    // ImGui::Render();
    SDL_GL_SwapWindow(g_window);
}

int main(void)
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    // Setup SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    // Setup window
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_DisplayMode current;
    SDL_GetCurrentDisplayMode(0, &current);
    g_window = SDL_CreateWindow("ImGui SDL2+OpenGLES+Emscripten example",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
    SDL_GLContext glcontext = SDL_GL_CreateContext(g_window);

    // // Setup ImGui binding
    // ImGui_ImplSdl_Init(g_window);

    // Main loop
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(main_loop, 0, 1);
#else
    while (!g_done)
    {
        main_loop();
    }
#endif

    // Cleanup
    // ImGui_ImplSdl_Shutdown();
    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(g_window);
    SDL_Quit();

    return 0;
}
