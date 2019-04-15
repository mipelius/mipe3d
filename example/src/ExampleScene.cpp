// Copyright (c) Miika Pelkonen. All rights reserved.
// Licensed under the MIT License.

#include "ExampleScene.h"

#include "Mipe3DEngine.h"
#include "Mipe3DRenderSystem.h"
#include "Mipe3DResourceManager.h"
#include "Mipe3DRenderable.h"
#include "Mipe3DShaderProgram.h"
#include "Mipe3DMesh.h"
#include "Mipe3DMaterial.h"
#include "Mipe3DTexture.h"
#include "Mipe3DLog.h"
#include "Mipe3DCamera.h"
#include "Mipe3DInput.h"
#include "Mipe3DTime.h"

namespace mipe3d
{
namespace example
{

ExampleScene::ExampleScene() { }
ExampleScene::~ExampleScene() { }

bool ExampleScene::startUp()
{
    // cube
    auto cubeMesh = resourceManager().get<Mesh>("cube_mesh");
    auto cubeMaterial = resourceManager().get<Material>("cube_material");
    m_cube = renderSystem().createRenderable();
    m_cube->setMesh(cubeMesh);
    m_cube->setMaterial(cubeMaterial);
    m_cube->getTransform().setPosition({ 0.0f, 0.0f, 0.0f });
    m_cube->getTransform().setScale({ 2.0f, 2.0f, 2.0f });

    // plane
    auto planeMesh = resourceManager().get<Mesh>("plane_mesh");
    auto planeMaterial = resourceManager().get<Material>("plane_material");
    m_plane = renderSystem().createRenderable();
    m_plane->setMesh(planeMesh);
    m_plane->setMaterial(planeMaterial);
    m_plane->getTransform().setPosition({ 0.0f, -2.0f, 0.0f });
    m_plane->getTransform().setEulerAngles({ 0.0f, 0.0f, 0.0f });
    m_plane->getTransform().setScale({ 10.0f, 10.0f, 10.0f });

    // camera
    camera().setPosition({ 0.0f, 10.0f, 20.0f });
    camera().setEulerAngles({ glm::radians(-30.0f), 0.0f, 0.0f });

	return true;
}

bool ExampleScene::shutDown()
{
	return true;
}

void ExampleScene::update()
{
    static float phase = 0.0f;
    phase += time().getDeltaTime();

    m_cube->getTransform().setEulerAngles(
        {
            cos(phase),
            phase,
            sin(phase)
        });

    if (input().keyboard().isKeyDown(Key::ESC))
    {
        engine().stop();
    }
}

} // namespace example
} // namespace mipe3d