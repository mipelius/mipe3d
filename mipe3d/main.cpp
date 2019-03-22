#include "Mipe3DEngine.h"
#include "ExampleScene.h"

int main(int argc, char *argv[])
{
	mipe3d::example::ExampleScene exampleScene;
	mipe3d::Engine engine;
	engine.run(exampleScene);
	return 0;
}