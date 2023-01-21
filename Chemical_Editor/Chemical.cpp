#include "Chemical.hpp"

Chemical::Chemical(const String symbol, const String name, const int valency, const Color symbol_color)
	: symbol{ symbol },
	name{ name },
	valency{ valency },
	symbol_color{ symbol_color } {}

void Chemical::update() {

}

void Chemical::draw() const {

}
String Chemical::get_name() const {
	return name;
}

String Chemical::get_symbol() const {
	return symbol;
}

int Chemical::get_valency() const {
	return valency;
}

Color Chemical::get_symbol_color() const {
	return symbol_color;
}
