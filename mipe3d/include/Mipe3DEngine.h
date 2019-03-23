#pragma once

#include <memory>

namespace mipe3d
{

class RenderSystem;
class ResourceManager;
class IScene;

class Engine
{
public:
	Engine();
	void run(IScene& scene);
	virtual ~Engine();

private:
	bool startUp();
	bool shutDown();
	void startGameLoop();

	bool m_isRunning = false;
	RenderSystem* m_renderSystem = nullptr;
	ResourceManager* m_resourceManager = nullptr;

	IScene* m_scene = nullptr;
};

} // namespace mipe3d