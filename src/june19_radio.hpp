#pragma once
#include "june19_core.hpp"

namespace june19{
	j19gadget* CreateRadioButton(std::string caption, int x, int y, int w, int h, j19gadget* mommy, bool defaultvalue = false);
}
