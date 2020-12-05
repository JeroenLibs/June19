#pragma once

#include "june19_core.hpp"

namespace june19 {
	j19gadget* CreateButton(std::string Caption, int x, int y, j19gadget* Parent);
	j19gadget* CreateButton(std::string Caption, int x, int y, int w, int h, j19gadget* Parent);
	
}