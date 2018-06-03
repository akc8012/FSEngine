#include "Engine.h"

int main(int argc, char* args[])
{
	Engine* engine = new Engine();

	engine->init();
	engine->quit();

	return 0;
}
