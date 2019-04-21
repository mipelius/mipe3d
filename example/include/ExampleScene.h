// Copyright (c) Miika Pelkonen. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include "Mipe3DIScene.h"

namespace mipe3d
{

class Renderable;

namespace example
{

class ExampleScene : public IScene
{
public:
    ExampleScene();
    ~ExampleScene() override;

    bool startUp() override;
    bool shutDown() override;
    void update() override;

private:
    Renderable* m_cube;
    Renderable* m_plane;
};

} // namespace example
} // namespace mipe3d
