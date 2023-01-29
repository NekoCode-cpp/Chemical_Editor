#pragma once
#include "Common.hpp"
#include "Chemical.hpp"
#include "ChemicalView.hpp"
#include "ChemicalButton.hpp"

class Editor : public App::Scene
{

private:
	int last_click_time = 0;
	int selected_symbol_btn_index = 0;
	Array<Chemical> chemicals;
	Array<ChemicalView> chemical_views;
	Array<ChemicalButton> chemical_symbol_btns;
public:

	Editor(const InitData& init);

	void update() override;

	void draw() const override;

	void add_chemical_view();

	Array<Chemical> load_chemicals(void) const;

	Array<ChemicalButton> generate_chemicals_symbol_btn(Array<Chemical> chemicals) const;
};
