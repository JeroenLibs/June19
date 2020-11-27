// Lic:
// src/june19_core.hpp
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
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>

#include <TQSG.hpp>

#define j19byte unsigned char

#define j19nullgadget(gadget) {FreeGadget(gadget); gadget=nullptr;}

#undef j19loudmouth

#ifdef j19loudmouth
#define j19chat(A) std::cout << "LOUDMOUTH:> " << A << std::endl
#else
#define j19chat(A)
#endif

namespace june19 {

	enum class j19kind {
		Unknown,
		EntireScreen,
		WorkScreen,
		Group,
		Label,
		TextField,
		RadioButton,
		CheckBox,
		Picture,
		ListBox
	};

	enum class j19ctype {  Absolute, Percent };

	class j19gadget;

	typedef void (*j19draw)(j19gadget* g);

	class j19gadget {
	private:
		j19gadget* parent{ nullptr };
		std::vector<j19gadget*> kids;
		j19kind kind{ j19kind::Unknown };
		int _x{ 0 }, _y{ 0 }, _w{ 100 }, _h{ 100 };
		j19ctype tx{ j19ctype::Absolute }, ty{ j19ctype::Absolute }, tw{ j19ctype::Absolute }, th { j19ctype::Absolute };
		static std::map<j19kind, j19draw> HowToDraw;
		bool fontloaded{ false };
		TrickyUnits::TQSG_ImageFont _Font;
		static bool haspulldown;
		static bool hasstatus;
		static j19gadget* active;

		static bool defaultfontloaded;
		static TrickyUnits::TQSG_ImageFont _DefaultFont;
	public:
		bool Active();
		void Activate();
		static void DeActivate();

		int IntFlag{ 0 };
		static bool RegDraw(j19kind k, j19draw v);

		void SetKind(j19kind value); // Please note this only works once, and most creation fuctions take care of this automatically.
		void SetParent(j19gadget* value); // Please note this only works once, and most creation fuctions take care of this automatically.

		void X(int value);
		void X(int value, j19ctype t);
		int X(bool pure = false);

		void W(int value);
		void W(int value, j19ctype t);
		int W(bool pure = false);

		void Y(int value);
		void Y(int value, j19ctype t);
		int Y(bool pure = false);

		void H(int value);
		void H(int value, j19ctype t);
		int H(bool pure = false);

		int DrawX();
		int DrawY();

		bool Visible{ true };
		bool Enabled{ true };

		TrickyUnits::TQSG_ImageFont *Font();
		void KillFont();
		void SetFont(std::string FFile);
		void SetFont(std::string MFile, std::string FFile);
		void SetFont(jcr6::JT_Dir* MFile, std::string FFile);
		static void SetDefaultFont(std::string FFile);
		static void SetDefaultFont(std::string MFile, std::string FFile);
		static void SetDefaultFont(jcr6::JT_Dir* MFile, std::string FFile);
		static void KillDefaultFont();
		int FontHeight();

		std::string Caption{ "" };
		std::string Text{ "" };

		j19byte FR{ 255 }, FG{ 255 }, FB{ 255 }, FA{ 255 };
		j19byte BR{ 0 }, BG{ 0 }, BB{ 0 }, BA{ 0 };

		

		void SetForeground(j19byte R, j19byte G, j19byte B, j19byte Alpha = 255);
		void SetBackground(j19byte R, j19byte G, j19byte B, j19byte Alpha = 0);

		void Draw(bool force=false); // Draw a gadget and all its children (if visible)

		// These methods should NEVER be called directly! FreeGadget() needs them
		void KillKids(); // Called by "FreeGadget". Don't call this directly unless you know what you are doing
		void DetachParent(); // Remove Gadget from parent's kids. NEVER call this yourself unless you know what you doing! FreeGadget needs this method, that's all!
		void RemoveKid(j19gadget *kid); // Remove kid from parent. NEVER call this yuourself, unless youknow what you are doing! FreeGadget needs this methid, and that's all!

	};

	j19gadget* Screen();
	j19gadget* WorkScreen();
	void FreeGadget(j19gadget* gadget); // Disposes a gadget and all its children. 

	std::string GetCoreError();

	j19gadget* CreateGroup(int x, int y, int w, int h, j19gadget* Parent, j19ctype coordtype = j19ctype::Absolute);

	void FreeJune19(); // Frees all gadgets tried to Screen or WorkScreen. Recommended to do before closing down!

}