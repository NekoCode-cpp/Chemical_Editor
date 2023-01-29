#include "Editor.hpp"

Editor::Editor(const InitData& init)
	: IScene{ init }
{
	chemicals = load_chemicals();
	chemical_symbol_btns = generate_chemicals_symbol_btn(chemicals);
}

void Editor::update() {

	int symbol_btn_index = 0;
	if (Cursor::Pos().x < (Scene::Width() - chemical_symbol_btn::width) && Scene::Rect().leftClicked()) {
		add_chemical_view();
	}

	for (auto& chemical_symbol_btn : chemical_symbol_btns) {

		chemical_symbol_btn.update();

		if (last_click_time < chemical_symbol_btn.get_click_time()) {
			last_click_time = chemical_symbol_btn.get_click_time();
			selected_symbol_btn_index = symbol_btn_index;
		}

		if (symbol_btn_index != selected_symbol_btn_index) {
			chemical_symbol_btn.reset_clicked();
		}
		symbol_btn_index++;
	}

	for (auto& chemical_view : chemical_views) {
		chemical_view.update();
	}
}

void Editor::draw() const {

	int symbol_btn_index = 0;
	for (const auto& chemical_symbol_btn : chemical_symbol_btns) {
		chemical_symbol_btn.draw((symbol_btn_index == selected_symbol_btn_index) ? true : false);
		symbol_btn_index++;
	}
	for (const auto& chemical_view : chemical_views) {
		chemical_view.draw();
	}
}

void Editor::add_chemical_view() {

	chemical_views.emplace_back(
		chemicals[selected_symbol_btn_index], Cursor::Pos()
	);
}

Array<ChemicalButton> Editor::generate_chemicals_symbol_btn(Array<Chemical> chemicals) const {

	int chemical_index = 0;
	Array<ChemicalButton> buttons;

	for (const auto& chemical : chemicals) {

		Vec2 pos{ Scene::Width() - chemical_symbol_btn::width ,chemical_symbol_btn::height * chemical_index };

		buttons.emplace_back(chemical, pos);

		chemical_index++;
	}
	return buttons;
}

Array<Chemical> Editor::load_chemicals(void) const {

	TextReader reader{ U"Chemicals_info.txt" };

	if (not reader) {
		throw Error{ U"元素情報ファイルを開けませんでした" };
	}

	String line;
	Array<Chemical> chemicals;

	while (reader.readLine(line))
	{
		if (line.isEmpty()) {
			continue;
		}

		const Array<String> params = line.split(U' ');

		if (params.size() != 4) {
			throw Error{ U"不正なファイル形式です。" };
		}

		chemicals.emplace_back(
			params[0], params[1], Parse<int>(params[2]), Parse<Color>(params[3])
		);
	}
	return chemicals;
}
