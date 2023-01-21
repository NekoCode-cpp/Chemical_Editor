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
	int click_time = -1;
	Chemical chemical;
	bool is_clicked = false;
public:

	ChemicalButton(const Chemical chemical, const Vec2 pos);

	void update();

	void draw(bool is_selected) const;

	bool is_selected() const;

	int get_click_time() const;

	void reset_clicked();
};
