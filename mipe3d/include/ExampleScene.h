#pragma once

#include "Mipe3DIScene.h"

namespace mipe3d
{
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
};

} // namespace example
} // namespace mipe3d
