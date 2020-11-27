// Lic:
// Test_June19.cpp
// June 19
// version: 20.11.27
// Copyright (C) 2020 Jeroen P. Broks
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not
// claim that you wrote the original software. If you use this software
// in a product, an acknowledgment in the product documentation would be
// appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
// misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
// EndLic
#include <SDL.h>
#include <SDL_main.h>
#include <TQSG.hpp>
#include <TQSE.hpp>
#include "src/june19.hpp"


#define FontFile "Test/Robotica.18.jfbf"

#define until(yeah) while(!(yeah))

using namespace june19;
using namespace TrickyUnits;
using namespace jcr6;

int main(int argcount, char** args) {
	init_JCR6();
	TQSG_Init("Test June19");
	TQSE_Init();
	j19chat("Window size: " << TQSG_ScreenHeight() << "x" << TQSG_ScreenHeight());
	auto WS{ WorkScreen() };
	auto TestLabel{ CreateLabel("Hello World",40,50,200,20,WS) }; TestLabel->SetFont(FontFile);
	TestLabel->SetForeground(255,255,0);
	TestLabel->SetBackground(255, 0, 0,255);
	do {
		TQSG_Cls();
		june19::Screen()->Draw();
		TQSG_Flip();
		TQSE_Poll();
	} until(TQSE_Quit());
	FreeJune19();
	TQSG_Close();
	return 0;
}