#include "ChemicalButton.hpp"

ChemicalButton::ChemicalButton(const Chemical chemical, const Vec2 pos)
	: chemical{ chemical },
	pos{ pos } {}

void ChemicalButton::update() {

	RectF btn{ pos, chemical_symbol_btn::width,chemical_symbol_btn::height };

	if (btn.leftClicked()) {
		is_clicked = not is_clicked;
		if (is_clicked) {
			click_time = Scene::FrameCount();
		}
	}

}

void ChemicalButton::draw(bool is_selected) const {

	const String symbol = chemical.get_symbol();
	const Color symbol_color = chemical.get_symbol_color();
	const Vec2 symbol_pos{ pos.movedBy(chemical_symbol_btn::width / 2,chemical_symbol_btn::height / 2) };
	const RectF btn{ pos, chemical_symbol_btn::width,chemical_symbol_btn::height };

	const Color btn_background = btn.mouseOver() ? Palette::White : UI::background_color;

	btn.draw(btn_background).drawFrame(1, Palette::Black);

	if (is_selected) {
		btn.drawFrame(5, 0, Palette::Orange);
	}
	FontAsset(U"Symbol")(symbol).drawAt(symbol_pos, symbol_color);
}
int ChemicalButton::get_click_time() const {
	return is_clicked ? click_time : -1;
}
bool ChemicalButton::is_selected() const {
	return is_clicked;
}
void ChemicalButton::reset_clicked() {
	is_clicked = false;
}
