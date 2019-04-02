#pragma once

#include "apidef.h"

namespace mipe3d
{

class RenderSystem;
class ResourceManager;
class IScene;

class Engine
{
    friend MIPE3D_API Engine& engine();
    friend MIPE3D_API ResourceManager& resourceManager();
    friend MIPE3D_API RenderSystem& renderSystem();

public:
    MIPE3D_API void run(IScene& scene);

private:
    Engine();
    virtual ~Engine();

    bool startUp();
    bool shutDown();
    void startGameLoop();

    bool m_isRunning = false;
    RenderSystem* m_renderSystem = nullptr;
    ResourceManager* m_resourceManager = nullptr;

    IScene* m_scene = nullptr;
};

MIPE3D_API Engine& engine();

} // namespace mipe3d