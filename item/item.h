#ifndef _ITEM_H_
#define _ITEM_H_
#include <string>
#include "itemnames.h"

using namespace std;

class Item {
	
	string type;	
  public:
  
    Item(string type);
    string getType();
    virtual int getValue() = 0;
    virtual ItemNames getName() = 0;
};



#endif