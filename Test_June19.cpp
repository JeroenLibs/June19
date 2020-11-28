// Lic:
// Test_June19.cpp
// June 19
// version: 20.11.28
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
#include <iostream>
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
using namespace std;

int main(int argcount, char** args) {
	init_JCR6();
	TQSG_Init("Test June19");
	TQSE_Init();
	j19chat("Window size: " << TQSG_ScreenHeight() << "x" << TQSG_ScreenHeight());
	auto WS{ WorkScreen() };
	auto TestLabel{ CreateLabel("Hello World",40,50,200,20,WS) }; j19gadget::SetDefaultFont(FontFile);
	TestLabel->SetForeground(255,255,0);
	TestLabel->SetBackground(255, 0, 0,255);
	auto TestPicture{ CreatePicture(100,10,300,200,WS,Pic_FullStretch) };
	TestPicture->Image("Test/Cute-Girl.png"); // Just a public domain picture I downloaded for testing this gadget type
	//*
	auto TestTab{ CreateTabber(0,400,500,200,WS) };
	//*/
	//*
	auto Pan1{ AddTab(TestTab,"First tab") };
	auto Pan2{ AddTab(TestTab,"Second tab") };
	auto Pan3{ AddTab(TestTab,"Third tab") };
	auto Pan1Text{ CreateLabel("Hello from the first tab!",20,20,200,50,Pan1) };
	auto Pan2Text{ CreateLabel("Are were there on the second tab?",10,10,200,30,Pan2) };
	auto Pan2Img(CreatePicture(0, 0, 100, 100, Pan3,Pic_FullStretch)); 
	Pan2Img->Image("Test/Cute-Girl.png");
	Pan2Img->SetForeground(255, 180, 0);
	Pan2Img->W(100, j19ctype::Percent);
	Pan2Img->H(100, j19ctype::Percent);
	//*/
	cout << "Default font: " << WS->Font() << endl;
	do {
		static auto gb{ 0 }; gb = (gb + 1) % 256;
		Pan2Img->FB = gb;
		TQSG_Cls();
		june19::Screen()->Draw();
		TQSG_Flip();
		TQSE_Poll();
	} until(TQSE_Quit());
	cout << "Cleaning up June 19\n";
	FreeJune19();
	cout << "Closing SDL and TQSG\n";
	TQSG_Close();
	cout << "Ending program";
	return 0;
}