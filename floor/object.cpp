#include "object.h"
#include <string>
#include <memory>

using namespace std;

Floor_Object::Floor_Object(shared_ptr<Character> c, int x = 0, int y = 0):
type{"character"}, ch{c}, it{nullptr}, x{x}, y{y} {}

Floor_Object::Floor_Object(shared_ptr<Item> i, int x = 0, int y = 0):
type{"item"}, ch{nullptr}, it{i}, x{x}, y{y} {}

Floor_Object::~Floor_Object(){}

int Floor_Object::get_x() {return x;}

int Floor_Object::get_y() {return y;}

string Floor_Object::get_type() {return type;}

void Floor_Object::clearobject() {ch = nullptr; it = nullptr;}


void Floor_Object::set_pos(int x, int y) {this->x = x; this->y = y;}

//bool Floor_Object::get_is_player() { return is_player;}

shared_ptr<Character> Floor_Object::get_ch() {
	return ch;
}

shared_ptr<Item> Floor_Object::get_it() {
	return it;
}
