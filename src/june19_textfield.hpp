#pragma once


#include "june19_core.hpp"

namespace june19 {

	// Creates a text field. When you don't set the "height" paramater, the textfield will automatically adjust the height based on the chosen font.
	j19gadget* CreateTextfield(int x, int y, int w, j19gadget* ouwe, std::string defaultvalue = "");
	// Creates a text field.
	j19gadget* CreateTextfield(int x, int y, int w, int h, j19gadget* ouwe, std::string defaultvalue = "");
}
