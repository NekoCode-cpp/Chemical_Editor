#pragma once
#include "Common.hpp"
#include "Chemical.hpp"

class ValencyPoint {

private:
	int valency_index;
	bool is_clicked = false;
public:

	ValencyPoint(const int valency_index);

	void update();

	void draw(const Vec2 pos) const;

	int get_valency_index() const;

	bool get_is_clicked() const;
};
