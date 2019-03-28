#pragma once

#include "apidef.h"

#include <list>

struct SDL_Window;
typedef void* SDL_GLContext;

namespace mipe3d
{

class Renderable;

class RenderSystem
{
	friend class Engine;

public:
	MIPE3D_API Renderable* createRenderable();

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
	std::list<Renderable*> m_renderables;

	static const int WINDOW_WIDTH = 1024;
	static const int WINDOW_HEIGHT = 768;
};

// ---- singleton accessor ----

MIPE3D_API RenderSystem& renderSystem();

} // namespace mipe3d