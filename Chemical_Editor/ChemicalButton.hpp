#pragma once
#include "Common.hpp"
#include "Chemical.hpp"
#include "UI.hpp"

namespace chemical_symbol_btn {
	const int width = 50;
	const int height = 50;
}

class ChemicalButton {
private:
	Vec2 pos;
	Chemical chemical;
	bool is_clicked = false;
	bool btn_is_selected = false;
public:

	ChemicalButton(const Chemical chemical, const Vec2 pos);

	void update();

	void draw() const;

	bool is_selected() const;

	void set_selected();
};
