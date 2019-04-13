#include "Mipe3DEngine.h"
#include "Mipe3DRenderSystem.h"
#include "Mipe3DResourceManager.h"
#include "Mipe3DInput.h"
#include "Mipe3DIScene.h"
#include "Mipe3DLog.h"
#include "Mipe3DTime.h"

#include <SDL.h>

namespace mipe3d
{

Engine::Engine()
{
    m_renderSystem = new RenderSystem();
    m_resourceManager = new ResourceManager();
    m_input = new Input();
    m_time = new Time();
}

Engine::~Engine() 
{
    delete m_renderSystem;
    delete m_resourceManager;
    delete m_input;
    delete m_time;
}

void Engine::run(IScene& scene)
{
    if (m_scene)
    {
        MIPE3D_LOG_ERROR("Engine is already running!");
        assert(false);
    }

    m_scene = &scene;

    if (startUp())
    {
        startGameLoop();
        shutDown();
    }

    m_scene = nullptr;
}

void Engine::stop()
{
    m_isRunning = false;
}

bool Engine::startUp()
{
    if (!m_renderSystem->startUp())
    {
        return false;
    }
    if (!m_resourceManager->startUp())
    {
        return false;
    }
    if (!m_input->startUp())
    {
        return false;
    }
    if (!m_time->startUp())
    {
        return false;
    }
    if (!m_scene->startUp())
    {
        return false;
    }
    return true;
}

bool Engine::shutDown()
{
    bool success = true;

    success = m_scene->shutDown() && success;
    success = m_time->shutDown() && success;
    success = m_input->shutDown() && success;
    success = m_resourceManager->shutDown() && success;
    success = m_renderSystem->shutDown() && success;

    return success;
}

void Engine::startGameLoop()
{
    m_isRunning = true;

    while (m_isRunning)
    {
        m_time->update();
        m_input->update();
        m_scene->update();
        m_renderSystem->update();
        
        if (SDL_QuitRequested())
        {
            m_isRunning = false;
        }
    }
}

Engine& engine()
{
    static Engine engine;
    return engine;
}

} // namespace mipe3d