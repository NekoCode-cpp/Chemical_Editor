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

	const int valency_point_offset = 20;
	Circle shap{ pos,valency_point_offset };
	if (shap.leftPressed()) {
		is_drag_start = true;
	}
	if (is_drag_start) {
		pos = Cursor::Pos();
	}
	if (is_drag_start && MouseL.pressed() == false) {
		is_drag_start = false;
	}
	for (auto& valency_point : valency_points) {
		valency_point.update();
	}
}

void ChemicalView::draw() const {

	const int valency_point_offset = 20;
	const String symbol = chemical.get_symbol();
	const int valency_point_num = chemical.get_valency();
	const Color symbol_color = chemical.get_symbol_color();

	const double angle_step = 360_deg / valency_point_num;

	Circle{ pos,valency_point_offset }.draw(symbol_color);
	FontAsset(U"Symbol")(symbol).drawAt(pos, Palette::White);

	for (const auto& valency_point : valency_points) {

		const double angle = valency_point.get_valency_index() * angle_step;

		const Vec2 valency_point_pos = OffsetCircular{ pos,valency_point_offset, angle };

		valency_point.draw(valency_point_pos);
	}
}
