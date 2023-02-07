#include "ChemicalButton.hpp"

ChemicalButton::ChemicalButton(const Chemical chemical, const Vec2 pos)
	: chemical{ chemical },
	pos{ pos } {}

void ChemicalButton::update() {

	RectF btn{ pos, chemical_symbol_btn::width,chemical_symbol_btn::height };

	if (btn.leftClicked() != true && MouseL.pressed() && Cursor::Pos().x > (Scene::Width() - chemical_symbol_btn::width)) {
		btn_is_selected = false;
	}
	if (btn.leftPressed()) {
		btn_is_selected = not btn_is_selected;
	}
}

void ChemicalButton::draw() const {

	const String symbol = chemical.get_symbol();
	const Color symbol_color = chemical.get_symbol_color();
	const Vec2 symbol_pos{ pos.movedBy(chemical_symbol_btn::width / 2,chemical_symbol_btn::height / 2) };
	const RectF btn{ pos, chemical_symbol_btn::width,chemical_symbol_btn::height };

	const Color btn_background = btn.mouseOver() ? Palette::White : UI::background_color;

	btn.draw(btn_background).drawFrame(1, Palette::Black);

	if (btn_is_selected) {
		btn.drawFrame(5, 0, Palette::Orange);
	}
	FontAsset(U"Symbol")(symbol).drawAt(symbol_pos, symbol_color);
}
bool ChemicalButton::is_selected() const {
	return btn_is_selected;
}
void ChemicalButton::set_selected(){
	btn_is_selected = true;
}
