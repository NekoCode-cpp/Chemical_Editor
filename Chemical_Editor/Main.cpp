#include "Common.hpp"
#include "Editor2.hpp"
#include "UI.hpp"

void Main()
{
	Scene::SetBackground(UI::background_color);

	FontAsset::Register(U"font30", 30);
	FontAsset::Register(U"Symbol", 35, Typeface::Heavy);

	App manager;

	manager.add<Editor2>(U"Editor");

	while (System::Update())
	{
		if (not manager.update()) {
			break;
		}
	}
}
