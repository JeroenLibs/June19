#include <SDL.h>
#include <SDL_main.h>
#include <TQSG.hpp>
#include "src/june19.hpp"

using namespace TrickyUnits;

int main(int argcount, char** args) {
	TQSG_Init("Test June19");
	TQSG_Close();
	return 0;
}