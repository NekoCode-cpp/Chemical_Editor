#pragma once
#include "Common.hpp"
#include "Chemical.hpp"
#include "ValencyPoint.hpp"

class ChemicalView {

private:
	Vec2 pos;
	Chemical chemical;
	int now_active_bond = 0;
	Array<ValencyPoint> valency_points;
	bool is_selected = false;
	bool is_drag_start = false;

public:

	ChemicalView(const Chemical chemical, const Vec2 pos);

	void update();

	void draw() const;

	bool selected() const;

	void set_select();

	void add_bond();

	bool can_add_bond() const;

	Vec2 get_pos() const;

	Circle get_shap() const;
};
