#include <string>
#include "potion.h"
using namespace std;

Potion::Potion(ItemNames potion): Item("potion"), potion{potion} {
	switch (potion) {
        case ItemNames::RH : value = 10; break;
		case ItemNames::BA : value = 5; break;
		case ItemNames::BD : value = 5; break;
		case ItemNames::PH : value = -10; break;
		case ItemNames::WA : value = -5; break;
		case ItemNames::WD : value = -5; break;
	}
}

int Potion::getValue() {return value;}

ItemNames Potion::getName() {return potion;}

Potion::~Potion() {}




