#include "UI.hpp"
#include "ChemicalView.hpp"

ChemicalView::ChemicalView(const Chemical chemical, const Vec2 pos)
	: chemical{ chemical },
	pos{ pos }
{
	const int valency_point_num = this->chemical.get_valency();
	for (auto i : step(valency_point_num)) {
		valency_points.emplace_back(i);
	}
}

void ChemicalView::update() {

	const int valency_point_offset = UI::chemical_view_r;
	Circle shap{ pos,valency_point_offset };

	if (shap.leftClicked() != true && MouseL.pressed()) {
		is_selected = false;
	}
	if (shap.leftPressed()) {
		is_selected = not is_selected;
		is_drag_start = not is_drag_start;
	}
	if (is_drag_start && Cursor::OnClientRect() && Cursor::Pos().x > 50) {
		pos = Cursor::Pos();
	}
	if (is_drag_start && MouseL.pressed() == false) {
		is_drag_start = false;
	}
	/*
	for (auto& valency_point : valency_points) {
		valency_point.update();
	}
	*/
}

void ChemicalView::draw() const {

	const int valency_point_offset = UI::chemical_view_r;
	const String symbol = chemical.get_symbol();
	const int valency_point_num = chemical.get_valency();
	const Color symbol_color = chemical.get_symbol_color();

	const double angle_step = 360_deg / valency_point_num;

	Circle{ pos,valency_point_offset }.draw(symbol_color);
	FontAsset(U"Symbol")(symbol).drawAt(pos, Palette::White);

	if (is_selected) {
		Circle{ pos,valency_point_offset }.drawFrame(1.5,0,Palette::Gray);
	}
	/*
	for (const auto& valency_point : valency_points) {

		const double angle = valency_point.get_valency_index() * angle_step;

		const Vec2 valency_point_pos = OffsetCircular{ pos,valency_point_offset, angle };

		valency_point.draw(valency_point_pos);
	}
	*/
}

bool ChemicalView::selected() const {
	return is_selected;
}

void ChemicalView::set_select() {
	is_selected = true;
}

Circle ChemicalView::get_shap() const {
	const int valency_point_offset = UI::chemical_view_r;
	return Circle{ pos,valency_point_offset }.drawFrame(1.5, 0, Palette::Gray);
}

Vec2 ChemicalView::get_pos() const {
	return pos;
}

bool ChemicalView::can_add_bond() const {

	if (now_active_bond < chemical.get_valency()) return true;
	return false;
}

void ChemicalView::add_bond() {

	now_active_bond++;
}
