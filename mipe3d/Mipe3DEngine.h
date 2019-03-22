#pragma once

#include <memory>

namespace mipe3d
{

class RenderSystem;

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
	RenderSystem* m_renderSystem;
};

} // namespace mipe3d