#pragma once

namespace mipe3d
{

class IScene
{
public:
	virtual ~IScene() {};

	virtual bool startUp() = 0;
	virtual bool shutDown() = 0;
	virtual void update() = 0;
};

} // namespace mipe3d