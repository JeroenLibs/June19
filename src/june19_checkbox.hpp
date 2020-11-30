#pragma once

#include "june19_core.hpp"

namespace june19 {
	j19gadget* CreateCheckBox(std::string Caption, int x, int y, int w, int h, j19gadget* parent, bool checkedbydefault = false);
}