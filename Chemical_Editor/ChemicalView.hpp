#pragma once
#include "Common.hpp"
#include "Chemical.hpp"
#include "ValencyPoint.hpp"

class ChemicalView {

private:
	Vec2 pos;
	Chemical chemical;
	Array<ValencyPoint> valency_points;
	bool is_selected = false;
	bool is_drag_start = false;

public:

	ChemicalView(const Chemical chemical, const Vec2 pos);

	void update();

	void draw() const;
};
