#include <string>
#include "treasure.h"

using namespace std;

Treasure::Treasure(ItemNames hoard):Item("treasure"), hoard{hoard} {
    switch (hoard) {
    	case ItemNames::SMALL : value = 1; break;
    	case ItemNames::NORMAL : value = 2; break;
    	case ItemNames::MERCHANT : value = 4; break;
    	case ItemNames::DRAGON : value = 6; break;
    }
}

ItemNames Treasure::getName() {return hoard;}

int Treasure::getValue() {return value;}

Treasure::~Treasure() {}


