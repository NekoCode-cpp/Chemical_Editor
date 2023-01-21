#include "Joint.hpp"

Joint::Joint(void) {

}

void Joint::addChemical(const Chemical& chemical) {
	chemicals.push_back(chemical);
}
