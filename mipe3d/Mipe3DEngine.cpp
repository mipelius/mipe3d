#include "Mipe3DEngine.h"
#include "Mipe3DRenderSystem.h"

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

void Engine::run()
{
	if (startUp())
	{
		startGameLoop();
		shutDown();
	}
}

bool Engine::startUp()
{
	return m_renderSystem->startUp();
}

bool Engine::shutDown()
{
	return m_renderSystem->shutDown();
}

void Engine::startGameLoop()
{
	m_isRunning = true;

	while (m_isRunning)
	{
		m_renderSystem->update();

		if (SDL_QuitRequested())
		{
			m_isRunning = false;
		}
	}
}

} // namespace mipe3d