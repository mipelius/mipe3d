#include "Mipe3DEngine.h"
#include "Mipe3DRenderSystem.h"
#include "Mipe3DIScene.h"

#include <SDL.h>

#include <iostream>

namespace mipe3d
{

Engine::Engine()
{
	m_renderSystem = new RenderSystem();
}

Engine::~Engine() 
{
	delete m_renderSystem;
}

void Engine::run(IScene& scene)
{
	m_scene = &scene;

	if (startUp())
	{
		startGameLoop();
		shutDown();
	}

	m_scene = nullptr;
}

bool Engine::startUp()
{
	if (!m_renderSystem->startUp())
	{
		return false;
	}
	if (!m_scene->startUp())
	{
		return false;
	}
}

bool Engine::shutDown()
{
	bool success = true;

	success = m_scene->shutDown() && success;
	success = m_renderSystem->shutDown() && success;

	return success;
}

void Engine::startGameLoop()
{
	m_isRunning = true;

	while (m_isRunning)
	{
		m_scene->update();
		m_renderSystem->update();

		if (SDL_QuitRequested())
		{
			m_isRunning = false;
		}
	}
}

} // namespace mipe3d