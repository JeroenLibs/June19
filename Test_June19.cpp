#include <SDL.h>
#include <SDL_main.h>
#include <TQSG.hpp>
#include <TQSE.hpp>
#include "src/june19.hpp"


#define until(yeah) while(!(yeah))

using namespace TrickyUnits;

int main(int argcount, char** args) {
	TQSG_Init("Test June19");
	TQSE_Init();
	do {
		TQSG_Cls();
		june19::Screen()->Draw();
		TQSG_Flip();
		TQSE_Poll();
	} until(TQSE_Quit());
	TQSG_Close();
	return 0;
}