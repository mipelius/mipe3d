#include "Mipe3DRenderSystem.h"

#include <SDL.h>
#include <gl\glew.h>
#include <SDL_opengl.h>
#include <gl\glu.h>

#include <iostream>

namespace mipe3d
{

RenderSystem::RenderSystem() { }
RenderSystem::~RenderSystem() { }

bool RenderSystem::startUp()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Unable to initialize SDL video! SDL error: " << SDL_GetError() << std::endl;
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

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
		std::cout << "Unable to create window! SDL error: " << SDL_GetError() << std::endl;
		return false;
	}

	// create context
	m_glContext = SDL_GL_CreateContext(m_window);

	if (m_glContext == NULL)
	{
		std::cout << "Unable to create OpenGL context! SDL error: " << SDL_GetError() << std::endl;
		return false;
	}

	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
	{
		std::cout << "GLEW initialization failed! GLEW error: " << glewGetErrorString(glewError) << std::endl;
	}

	if (SDL_GL_SetSwapInterval(1) < 0)
	{
		std::cout << "Warning: Unable to set VSync! SDL error: " << SDL_GetError() << std::endl;
	}

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
	SDL_GL_SwapWindow(m_window);
}

} // namespace mipe3d