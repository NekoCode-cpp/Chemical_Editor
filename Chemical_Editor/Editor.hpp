#pragma once
#include "Bond.hpp"
#include "Common.hpp"
#include "Chemical.hpp"
#include "CustomButton.hpp"
#include "ChemicalView.hpp"
#include "ChemicalButton.hpp"

class Editor : public App::Scene
{

private:
	int now_chemical_view_num = 0;
	int selected_symbol_btn_index = 0;
	Array<Bond> bonds;
	Array<Chemical> chemicals;
	Array<ChemicalButton> chemical_symbol_btns;
	HashTable<int32_t,ChemicalView> chemical_views;
	CustomButton save_btn = { U"保存(S)",SizeF{ 100,50},Vec2 { 0,0} };
	CustomButton change_back_btn = { U"戻る(Z)",SizeF{ 100,50},Vec2 { 100,0} };
	CustomButton chemical_view_del_btn = { U"原子を削除(D)",SizeF{ 150,50},Vec2 { 200,0} };
	CustomButton chemical_view_add_btn = { U"選択中の原子を追加(A)",SizeF{ 220,50},Vec2 { 350,0} };
public:

	Editor(const InitData& init);

	void update() override;

	void draw() const override;

	void add_chemical_view();

	bool in_bond(const auto it,const auto ip) const;

	Array<Chemical> load_chemicals(void) const;

	Array<ChemicalButton> generate_chemicals_symbol_btn(Array<Chemical> chemicals) const;
};
