#pragma once

struct SDL_Window;
typedef void* SDL_GLContext;

namespace mipe3d
{

class Engine
{
public:
	Engine();
	void run();
	virtual ~Engine();

private:
	bool startUp();
	bool shutDown();
	void startGameLoop();

	bool m_isRunning = false;
	SDL_Window* m_window;
	SDL_GLContext m_glContext;

	static const int WINDOW_WIDTH = 1024;
	static const int WINDOW_HEIGHT = 768;
};

} // namespace mipe3d