#include "Mipe3DRenderSystem.h"
#include "Mipe3DEngine.h"
#include "Mipe3DRenderable.h"
#include "Mipe3DLog.h"

#include <SDL.h>
#include <gl\glew.h>
#include <SDL_opengl.h>
#include <gl\glu.h>

#include <string>

namespace mipe3d
{

Renderable* RenderSystem::createRenderable()
{
    auto renderable = new Renderable();
    m_renderables.push_back(renderable);
    return renderable;
}

RenderSystem::RenderSystem() { }

RenderSystem::~RenderSystem() 
{ 
    for (auto renderable : m_renderables)
    {
        delete renderable;
    }
}

bool RenderSystem::startUp()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        MIPE3D_LOG(
            std::string("Unable to initialize SDL video! SDL error: ") + 
            SDL_GetError());
        return false;
    }

    // Set hints for window & context
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Create Window
    m_window = SDL_CreateWindow(
        "Mipe3D",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );

    if (m_window == NULL)
    {
        MIPE3D_LOG(
            std::string("Unable to create window! SDL error: ") +
            SDL_GetError());
        return false;
    }

    // Create context
    m_glContext = SDL_GL_CreateContext(m_window);

    if (m_glContext == NULL)
    {
        MIPE3D_LOG_ERROR(
            std::string("Unable to create OpenGL context! SDL error: ") + 
            SDL_GetError());
        return false;
    }

    // Init glew
    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();

    if (glewError != GLEW_OK)
    {
        // I guess there is no easier way to get just a normal c-string
        const GLubyte* glewErrorString = glewGetErrorString(glewError);
        const char* errorString = reinterpret_cast<const char*>(glewErrorString);

        MIPE3D_LOG_ERROR(
            std::string("GLEW initialization failed! GLEW error: ") +
            errorString);
    }

    // Enable vsync if possible
    if (SDL_GL_SetSwapInterval(1) < 0)
    {
        MIPE3D_LOG_WARNING(
            std::string("Unable to set VSync! SDL error: ") +
            SDL_GetError());
    }

    // Set openGL defaults 
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    return true;
}

bool RenderSystem::shutDown()
{
    SDL_GL_DeleteContext(m_glContext);
    SDL_DestroyWindow(m_window);

    return true;
}

void RenderSystem::update()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // just a dummy implemetation,
    // missing to-world and to-view transformations
    for (auto renderable : m_renderables)
    {
        renderable->render();
    }

    SDL_GL_SwapWindow(m_window);
}

RenderSystem& renderSystem()
{
    return *(engine().m_renderSystem);
}

} // namespace mipe3d