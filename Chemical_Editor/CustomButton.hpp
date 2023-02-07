#pragma once
#include "Common.hpp"
#include "UI.hpp"

class CustomButton {

private:
	String text;
	SizeF size;
	Vec2 pos;
	bool is_active = true;
	bool is_shap_clicked = false;
public:

	CustomButton(const String text, const SizeF size,const Vec2 pos);

	void draw() const;

	bool is_clicked() const;

	void set_active(bool status);
};
