#ifndef _FLOOR_OBJECT_H_
#define _FLOOR_OBJECT_H_
#include <memory>
#include <string>

class Character;
class Item;

// for Floor use
// !!!life cycle managed by Floor!!!
class Floor_Object {
	std::string type;
	std::shared_ptr<Character> ch;
	std::shared_ptr<Item> it;
	int x, y;
	
	public:

	Floor_Object(std::shared_ptr<Character> ch, int x, int y);
	Floor_Object(std::shared_ptr<Item> it, int x, int y);
	int get_x();
	int get_y();
	std::shared_ptr<Character> get_ch();
	void clearobject();
	std::shared_ptr<Item> get_it();
	std::string get_type();
	void set_pos(int x, int y);
	~Floor_Object();
};


#endif