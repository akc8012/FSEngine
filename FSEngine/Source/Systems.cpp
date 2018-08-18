#include "../Header/Systems.h"

Systems::Systems()
{
	fileSystem = new FileSystem();
	input = new Input();
}

Systems::~Systems()
{
	delete input;
	delete fileSystem;
}
