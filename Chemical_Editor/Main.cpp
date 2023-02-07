#include "Common.hpp"
#include "Editor.hpp"
#include "UI.hpp"

void Main()
{
	Scene::SetBackground(UI::background_color);

	FontAsset::Register(U"font30", 30);
	FontAsset::Register(U"custom_btn_font", 20);
	FontAsset::Register(U"Symbol", 40, Typeface::Heavy);

	App manager;

	manager.add<Editor>(U"Editor");

	while (System::Update())
	{
		if (not manager.update()) {
			break;
		}
	}
}
