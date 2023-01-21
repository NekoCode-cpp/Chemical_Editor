#pragma once
#include "Common.hpp"
#include "Chemical.hpp"

class Joint {

private:
	Array<Chemical> chemicals;
public:

	Joint();

	void addChemical(const Chemical& chemical);
};
