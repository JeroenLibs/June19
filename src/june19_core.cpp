#include <TQSG.hpp>
#include <TQSE.hpp>

#include "june19_core.hpp"

using namespace std;
using namespace TrickyUnits;

// Macros are evil! I know!
// But I am evil, as well!

#define ggc(ac,tc,rc)\
	_error = "";\
	if (pure)\
		return ac;\
	switch (tx) { \
		case j19ctype::Absolute: return ac;\
		case j19ctype::Percent: \
			if (!parent) { _error = "No parent"; return 0; }\
			return (int)floor(parent->rc() * (ac / 100)); \
		default: \
			_error = "Unknown coordinate calculation type! (bug?) ("+to_string((int)tx)+")"; \
			return 0; \
	}

#define sgc(ac,tc)\
	if (kind == j19kind::Unknown || kind == j19kind::EntireScreen || kind == j19kind::WorkScreen) { _error = "This gadget type may not be modified"; return; } \
	ac = value; tc = t;



namespace june19 {

	static string _error{ "" };
	static j19gadget _Screen;
	static j19gadget _WorkScreen;

	static void DrawScreen(j19gadget* self) {} // This just had to exist, that's all!
	static bool DS_Success{ j19gadget::RegDraw(j19kind::EntireScreen,DrawScreen) };

	std::map<j19kind, j19draw> j19gadget::HowToDraw;

	bool j19gadget::haspulldown{ false };
	bool j19gadget::hasstatus{ false };
	bool j19gadget::RegDraw(j19kind k, j19draw v) {
		_error = "";
		if (HowToDraw.count(k)) {
			_error = "Duplicate kind draw registration";
			return false;
		}
		HowToDraw[k] = v;
		return true;
	}

	void j19gadget::SetKind(j19kind value) { 
		_error = "";
		if (kind != j19kind::Unknown)
			_error = "Kind already set for this gadget";
		kind = value;
	}

	void j19gadget::SetParent(j19gadget* value) {
		if (parent)
			return;
		else {
			parent = value;
			value->kids.push_back(this);
		}
	}

	void j19gadget::X(int value) { X(value, tx); }

	void j19gadget::X(int value, j19ctype t) {
		/* proto
		if (kind == j19kind::Unknown || kind == j19kind::EntireScreen || kind == j19kind::WorkScreen) { _error = "This gadget type may not be modified"; return; }
		_x = value; tx = t;
		// */
		sgc(_x, tx);
	}

	int j19gadget::X(bool pure) {
		/* proto
		_error = "";
		if (pure)
			return _x;
		switch (tx) {
		case j19ctype::Absolute: return _x;
		case j19ctype::Percent:
			if (!parent) { _error = "No parent"; return 0; }
			return (int)floor(parent->W() * (_x / 100));
		default:
			_error = "Unknown coordinate calculation type! (bug?)";
			return 0;
		}
		*/
		if (kind == j19kind::EntireScreen || kind == j19kind::WorkScreen) return 0;
		ggc(_x, tx, W)
	}
	void j19gadget::W(int value) { W(value, tw); }
	void j19gadget::W(int value, j19ctype t) { sgc(_w, tw); }
	int j19gadget::W(bool pure) {
		switch (kind) {
		case j19kind::EntireScreen:
		case j19kind::WorkScreen:
			return TQSG_ScreenWidth();
		default:
			ggc(_w, tw, W);
		}
	}
	void j19gadget::Y(int value) { Y(value, ty); }
	void j19gadget::Y(int value, j19ctype t) { sgc(_y, ty); }
	int j19gadget::Y(bool pure) {
		switch (kind) {
		case j19kind::EntireScreen:
			return 0;
		case j19kind::WorkScreen:
		{
			auto h{ TQSG_ScreenHeight() }; // Pulldown menus and status bar can play a role here!
			auto fh{ FontHeight() };
			if (haspulldown) h += fh;
			return h;
		}
		default:
			ggc(_y, ty, H);
		}
	}
	void j19gadget::H(int value) { H(value, th); }
	void j19gadget::H(int value, j19ctype t) { sgc(_h, th); }
	int j19gadget::H(bool pure) {
		switch (kind) {
		case j19kind::EntireScreen:
			return TQSG_ScreenHeight();
		case j19kind::WorkScreen:
		{
			auto h{ TQSG_ScreenHeight() }; // Pulldown menus and status bar can play a role here!
			auto fh{ FontHeight() };
			if (haspulldown) h -= fh;
			if (hasstatus) h -= fh;
			return h;
		}
		default:
			ggc(_h, th, H);
		}
	}

	int j19gadget::DrawX() {
		switch (kind) {
		case j19kind::EntireScreen:
		case j19kind::WorkScreen:
			return 0;
		default:
			return X() + parent->X();
		}

	}

	int j19gadget::DrawY() {
		switch (kind) {
		case j19kind::EntireScreen:
			return 0;
		case j19kind::WorkScreen:
			_error = "Workscreen not fully supported yet!";
			return 0; // Pulldown menus and status bar can play a role here!
		default:
			return Y() + parent->Y();
		}
	}

	TQSG_ImageFont* j19gadget::Font() {
		if (!fontloaded)
			return nullptr;
		return &_Font;
	}

	void j19gadget::KillFont() {
		if (fontloaded) _Font.Kill();
		fontloaded = false;
	}

	void j19gadget::SetFont(std::string FFile) {
		auto J = jcr6::Dir(FFile);
		SetFont(&J, "");
	}

	void j19gadget::SetFont(std::string MFile, std::string FFile) {
		auto J = jcr6::Dir(MFile);
		SetFont(&J, FFile);
	}

	void j19gadget::SetFont(jcr6::JT_Dir* MFile, std::string FFile) {
		KillFont();
		_Font.LoadFont(*MFile, FFile);
		fontloaded = true;
	}

	int j19gadget::FontHeight() {
		if (!fontloaded) return 0;
		return Font()->TextHeight("THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG 1234567890 the quick brown fox jumps over the lazy dog");
	}

	void j19gadget::SetForeground(j19byte R, j19byte G, j19byte B, j19byte Alpha) {
		FR = R; 
		FG = G;
		FB = B;
		FA = Alpha;
	}

	void j19gadget::SetBackground(j19byte R, j19byte G, j19byte B, j19byte Alpha) {
		BR = R;
		BG = G;
		BB = B;
		BA = Alpha;
	}

	void j19gadget::Draw(bool force) {
		_error = "";
		if (force || Visible) {
			if (!HowToDraw.count(kind)) {
				_error = "Kind of type " + to_string((int)kind) + " has no draw routine";
				return;
			}
			HowToDraw[kind](this);
			for (auto kid : kids) kid->Draw(force);
		}
	}

	void j19gadget::KillKids() {
		auto copykids{ kids };
		for (auto kid : copykids) {
			FreeGadget(kid);
		}
	}

	void j19gadget::DetachParent() {
		parent->RemoveKid(this);
	}

	void j19gadget::RemoveKid(j19gadget* kid) {
		_error = "";
		int f{ -1 };
		do {
			if (f >= kids.size()) { _error = "Kid to remove not found!"; return; }
		} while (kids[f++] != kid);
		kids.erase(kids.begin() + f);
	}

	j19gadget* Screen() {
		static bool initiated{ false };
		if (!initiated) {
			WorkScreen();
			_Screen.SetKind(j19kind::EntireScreen);
			initiated = true;
		}
		return &_Screen;
	}

	j19gadget* WorkScreen() {
		static bool initiated{ false };
		if (!initiated) {
			_WorkScreen.SetParent(Screen());
			_WorkScreen.SetKind(j19kind::WorkScreen);
			initiated = true;
		}
		return &_WorkScreen;
	}

	void FreeGadget(j19gadget* gadget) {
		_error = "";
		if (gadget == &_Screen || gadget == &_WorkScreen) {
			_error = "Screen and WorkScreen cannot be disposed!";
			return;
		}
		gadget->KillKids();
		gadget->DetachParent();
		gadget->KillFont();
		delete gadget;
	}

}