#include "CustomButton.hpp"

CustomButton::CustomButton(const String text,const SizeF size ,const Vec2 pos)
	: text { text },
	  size { size },
	  pos { pos }{}

void CustomButton::draw() const {

	RectF rect{ pos ,size };

	if (is_active && rect.mouseOver()) {
		rect.draw(Palette::White);
	}
	rect.drawFrame(1, Palette::Black);

	FontAsset(U"custom_btn_font")(text).drawAt(Vec2{ pos.x + size.x / 2, pos.y + size.y / 2}, is_active ? Palette::Black:Palette::Gray);
}

bool CustomButton::is_clicked() const {

	RectF rect{ pos ,size };

	if (not is_active) return false;

	return rect.leftClicked();
}

void CustomButton::set_active(bool status) {
	is_active = status;
}
