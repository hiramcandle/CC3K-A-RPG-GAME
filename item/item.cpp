#include <string>
#include "item.h"

using namespace std;

Item::Item(string type): type{type} {}

string Item::getType() {return type;}


