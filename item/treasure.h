#ifndef _TREASURE_H_
#define _TREASURE_H_
#include "item.h"
#include "itemnames.h"
#include <string>

using namespace std;

class Treasure: public Item {
    
  	int value;
  	ItemNames hoard;
	
  public:
    Treasure(ItemNames hoard);
    ItemNames getName();
    int getValue();
    ~Treasure();
};


#endif
