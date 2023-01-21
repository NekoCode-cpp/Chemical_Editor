#pragma once
#include "Common.hpp"

class Chemical {

private:
	int valency;
	String name;
	String symbol;
	Color symbol_color;
public:

	Chemical(const String symbol, const String name, const int valency, const Color symbol_color);

	void update();

	void draw() const;

	String get_name() const;

	int get_valency() const;

	String get_symbol() const;

	Color get_symbol_color() const;
};
