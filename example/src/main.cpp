// Copyright (c) Miika Pelkonen. All rights reserved.
// Licensed under the MIT License.

#include "Mipe3DEngine.h"
#include "ExampleScene.h"

int main(int argc, char *argv[])
{
	mipe3d::example::ExampleScene exampleScene;
	mipe3d::engine().run(exampleScene);
	return 0;
}