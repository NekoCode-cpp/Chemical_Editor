#include "Editor.hpp"

Editor::Editor(const InitData& init)
	: IScene{ init }
{
	chemicals = load_chemicals();
	chemical_symbol_btns = generate_chemicals_symbol_btn(chemicals);
	chemical_symbol_btns[0].set_selected();
}

void Editor::update() {

	bool is_chemical_view_selected = false;

	int symbol_btn_index = 0;
	auto now_selected_chemical_view_index = -1;
	int btn_end_y = chemical_symbol_btn::height * chemical_symbol_btns.size();
	int btn_start_x = Scene::Width() - chemical_symbol_btn::width - UI::chemical_view_r;

	for (auto& chemical_symbol_btn : chemical_symbol_btns) {
		chemical_symbol_btn.update();
		if (chemical_symbol_btn.is_selected()) {
			selected_symbol_btn_index = symbol_btn_index;
		}
		symbol_btn_index++;
	}

	for (auto it = chemical_views.begin(); it != chemical_views.end(); ++it) {
		it->second.update();

		if (it->second.selected()) {
			now_selected_chemical_view_index = it->first;
			break;
		}

		for (auto ip = chemical_views.begin(); ip != chemical_views.end(); ++ip) {
			
			if (ip->first != it->first) {
				if (it->second.get_shap().intersects(ip->second.get_shap()) && in_bond(ip->first,ip->first)) {
					if (it->second.can_add_bond() && ip->second.can_add_bond()) {
						it->second.add_bond();
						ip->second.add_bond();
						bonds.emplace_back(it->first, ip->first);
					}
				}
			}/*
			if (it->second.get_shap().intersects(ip->second.get_shap())) {
				it->second.add_bond();
				ip->second.add_bond();
				bonds.emplace_back(it->first, ip->first);
			}*/
		}
	}
	
	if (Scene::Rect().leftClicked() && Cursor::Pos().x < btn_start_x && Cursor::Pos().y > 50 && now_selected_chemical_view_index == -1) {
		add_chemical_view();
		now_selected_chemical_view_index = now_chemical_view_num;
	}

	if (KeyA.down()) {
		add_chemical_view();
		now_selected_chemical_view_index = now_chemical_view_num;
	}

	if (KeyD.down()) {
		chemical_views.erase(now_selected_chemical_view_index);
		chemical_view_del_btn.set_active(false);
		//now_selected_chemical_view_index = -1;
	}
	/*
	ClearPrint();
	Print << now_selected_chemical_view_index;
	Print << chemical_views.contains(now_selected_chemical_view_index);
	Print << U"-----------";
	for (auto it = chemical_views.begin(); it != chemical_views.end(); ++it) {
		Print << it->first;
	}*/

	if (now_selected_chemical_view_index != -1) {
		chemical_view_del_btn.set_active(true);
	}
	else chemical_view_del_btn.set_active(false);

	if (chemical_view_del_btn.is_clicked()) {
		Console << now_selected_chemical_view_index;
		Console << chemical_views.contains(now_selected_chemical_view_index);
		chemical_views.erase(now_selected_chemical_view_index);
		chemical_view_del_btn.set_active(false);
	}
}

void Editor::draw() const {

	int symbol_btn_index = 0;
	for (const auto& chemical_symbol_btn : chemical_symbol_btns) {
		chemical_symbol_btn.draw();
		symbol_btn_index++;
	}
	for (const auto& bond : bonds) {
		if (chemical_views.contains(bond.to_chemical_view_key) && chemical_views.contains(bond.from_chemical_view_key)) {

			Vec2 to_pos = chemical_views.at(bond.to_chemical_view_key).get_pos();
			Vec2 from_pos = chemical_views.at(bond.from_chemical_view_key).get_pos();

			Line{ to_pos,from_pos }.draw(2,Palette::White);
		}	
	}
	for (const auto& [key, chemical_view] : chemical_views) {
		chemical_view.draw();
	}
	{
		save_btn.draw();
		change_back_btn.draw();
		chemical_view_del_btn.draw();
		chemical_view_add_btn.draw();
	}
}

void Editor::add_chemical_view() {

	ChemicalView chemical_view{ chemicals[selected_symbol_btn_index],Cursor::Pos() };

	chemical_views.emplace(
		now_chemical_view_num,chemical_view
	);

	//chemical_views[now_chemical_view_num].set_select();
	now_chemical_view_num++;
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

bool Editor::in_bond(const auto it, const auto ip) const {

	for (const auto& bond : bonds) {
		if (not(bond.to_chemical_view_key != it && bond.from_chemical_view_key != ip)) return false;
		if (not(bond.to_chemical_view_key != ip && bond.from_chemical_view_key != it)) return false;
	}
	return true;
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
