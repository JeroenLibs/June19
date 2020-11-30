// Lic:
// src/june19_textfield.cpp
// June 19
// version: 20.11.30
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
#include "june19_textfield.hpp"

using namespace std;

namespace june19 {

	void DrawTextfield(j19gadget*g){
	}

	static string _error{ "" };
    j19gadget* june19::CreateTextfield(int x, int y, int w, j19gadget* ouwe, std::string defaultvalue) {
        return CreateTextfield(x, y, w, 0, ouwe, defaultvalue);
    }

    j19gadget* CreateTextfield(int x, int y, int w, int h, j19gadget* ouwe, std::string defaultvalue) {
		static auto init{ false };
		auto ret{ new j19gadget() };
		if (!init) {
			j19gadget::RegDraw(j19kind::Textfield, DrawTextfield);
		}
		_error = "";
		ret->SetKind(j19kind::Textfield);
		ret->Caption = "";
		ret->Text = defaultvalue;
		ret->X(x);
		ret->Y(y);
		ret->W(w);
		ret->H(h);
		ret->SetParent(ouwe);
		ret->IntFlag = w<=0;
		return ret;

    }
}