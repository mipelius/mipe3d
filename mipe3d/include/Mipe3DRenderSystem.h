#pragma once

#include "apidef.h"

struct SDL_Window;
typedef void* SDL_GLContext;

namespace mipe3d
{

class MIPE3D_API RenderSystem
{
	friend class Engine;

private:
	RenderSystem();
	virtual ~RenderSystem();

	RenderSystem(const RenderSystem& other) = delete;
	RenderSystem& operator=(const RenderSystem& other) = delete;

	bool startUp();
	bool shutDown();

	void update();

	SDL_Window* m_window;
	SDL_GLContext m_glContext;

	static const int WINDOW_WIDTH = 1024;
	static const int WINDOW_HEIGHT = 768;
};

} // namespace mipe3d