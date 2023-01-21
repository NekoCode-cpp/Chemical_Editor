#include "ValencyPoint.hpp"

ValencyPoint::ValencyPoint(const int valency_index)
	: valency_index{ valency_index } {}

void ValencyPoint::update() {

}

void ValencyPoint::draw(const Vec2 pos) const {

	Circle{ pos , 4 }.draw(Palette::White);
}

int ValencyPoint::get_valency_index() const {
	return valency_index;
}

bool ValencyPoint::get_is_clicked() const {
	return is_clicked;
}
