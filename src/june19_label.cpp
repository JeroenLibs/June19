
#include "june19_core.hpp"
#include "june19_label.hpp"

namespace june19{

	static std::string _error;

	static void DrawLabel(j19gadget*g){
		_error = "";
		auto F{ g->Font() };
		if (!F) { _error = "No font for label"; return; }
		switch (g->IntFlag) {
		case 0:
			F->Draw(g->Caption, g->DrawX(), g->DrawY());
			break;
		case 1:
			F->Draw(g->Caption, g->DrawX()+g->W(), g->DrawY(),1);
			break;
		case 2:
			F->Draw(g->Caption, g->DrawX() + floor(g->W()/2), g->DrawY(), 2);
			break;
		default:
			_error = "Unknown label alignment flag: " + std::to_string(g->IntFlag);
		}
		
	}

	j19gadget* CreateLabel(std::string name, int x, int y, int w, int h, j19gadget* group, int style) {
		static auto init{ false };
		auto ret{ new j19gadget() };
		if (!init) {
			j19gadget::RegDraw(j19kind::Label,DrawLabel);
		}
		_error = "";
		ret->Caption = name;
		ret->X(x);
		ret->Y(y);
		ret->W(w);
		ret->H(h);
		ret->SetParent(group);
		ret->IntFlag = style;
		return ret;
	}
	j19gadget* CreateLabelR(std::string name, int x, int y, int w, int h, j19gadget* group, int style) {
		auto ret{ CreateLabel(name,x,y,w,h,group,style) };
		ret->X(x, j19ctype::Percent);
		ret->Y(y, j19ctype::Percent);
		ret->W(w, j19ctype::Percent);
		ret->H(h, j19ctype::Percent);
		return ret;
	}
}

