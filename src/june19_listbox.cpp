// Lic:
// src/june19_listbox.cpp
// Listbox - June19
// version: 21.04.02
// Copyright (C) 2021 Jeroen P. Broks
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
#include "june19_listbox.hpp"

using namespace TrickyUnits;

namespace june19 {
	static std::string _error;

	static void DrawListBox(j19gadget* g) {
		TQSG_ACol(g->BR, g->BG, g->BB, g->BA);
		TQSG_Rect(g->DrawX(), g->DrawY(), g->W(), g->H());
	}

	j19gadget* CreateListBox(int x, int y, int w, int h, j19gadget* parent, j19ctype ct) {
		static auto init{ false };
		auto ret{ new j19gadget() };
		if (!init) {
			j19gadget::RegDraw(j19kind::ListBox, DrawListBox);
		}
		_error = "";
		ret->SetKind(j19kind::ListBox);
		ret->X(x, ct);
		ret->Y(y, ct);
		ret->W(w, ct);
		ret->H(h, ct);
		ret->BA = 255;
		ret->SetParent(parent);
		return ret;
	}

}