#pragma once

#include "june19_core.hpp"


namespace june19{
	const int LABEL_LEFT = 0;
	const int LABEL_RIGHT = 1;
	const int LABEL_CENTER = 2;

	j19gadget* CreateLabel(std::string name, int x, int y, int w, int h, j19gadget* group, int style = LABEL_LEFT);
	j19gadget* CreateLabelR(std::string name, int x, int y, int w, int h, j19gadget* group, int style = LABEL_LEFT);
}

