#include "june19_checkbox.hpp"

using namespace std;
using namespace TrickyUnits;

namespace june19 {
	static string _error{ "" };

	static void DrawCheckBox(j19gadget* g) {
		auto Enab{ g->RecEnabled() };
		auto Deler{ 1 }; if (!Enab) Deler = 2;
		j19chat("Drawing Checkbox: " << g->Caption << "(" << g->DrawX() << "," << g->DrawY() << ")");
		_error = "";
		auto F{ g->Font() };
		if (!F) { _error = "No font for checkbox"; j19chat("Font issue");  return; }
		if (g->BA) {
			TQSG_ACol(g->BR, g->BG, g->BB, g->BA);
			TQSG_Rect(g->DrawX(), g->DrawY(), g->W(), g->H());
		}
		TQSG_ACol(g->FR / Deler, g->FG / Deler, g->FB / Deler, g->FA);
		auto sqs{ g->FontHeight() };
		TQSG_Rect(g->DrawX(), g->DrawY(), sqs, sqs, !g->checked);
		if (Enab && TQSE_MouseHit(1) && TQSE_MouseX() >= g->DrawX() && TQSE_MouseY() >= g->DrawY() && TQSE_MouseX() <= g->DrawX() + sqs && TQSE_MouseY() <= g->DrawY() + sqs) {
			g->checked = !g->checked;
			auto a{ j19action::Check };
			if (!g->checked) a = j19action::UnCheck;
			if (g->CBAction) g->CBAction(g, a);
		}
		F->Draw(g->Caption, g->DrawX() + (sqs * 1.5), g->DrawY());
	}


    j19gadget* CreateCheckBox(std::string Caption, int x, int y, int w, int h, j19gadget* parent, bool checkedbydefault) {
		static auto init{ false };
		auto ret{ new j19gadget() };
		if (!init) {
			j19gadget::RegDraw(j19kind::CheckBox, DrawCheckBox);
		}
		_error = "";
		ret->SetKind(j19kind::CheckBox);
		ret->Caption = Caption;
		ret->X(x);
		ret->Y(y);
		ret->W(w);
		ret->H(h);
		ret->SetParent(parent);
		ret->IntFlag = 0;
		ret->checked = checkedbydefault;
		return ret;
		return nullptr;
	}
}

