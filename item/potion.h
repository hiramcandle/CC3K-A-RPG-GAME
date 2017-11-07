#ifndef _POTION_H_
#define _POTION_H_
#include "item.h"
#include "itemnames.h"
#include <string>

using namespace std;

class Potion: public Item {
	
	int value;
    ItemNames potion;
    
  public:
    Potion(ItemNames potion);
    int getValue();
    ItemNames getName();
    ~Potion();
};


#endif