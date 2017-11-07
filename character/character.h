#ifndef _CHARACTER_H_
#define _CHARACTER_H_
#include <vector>
#include <memory>
#include "races.h"

// Management Interface
// !!!life sycle managed by self!!!

class Character;


struct Modifier{
	std::weak_ptr<Character> ch;
	Character_Field field;
	int change;
	std::unique_ptr<Modifier> next;
	
	Modifier(std::weak_ptr<Character> ch, Character_Field field, int change, std::unique_ptr<Modifier> next = {}):
	ch{ch}, field{field}, change{change}, next{std::move(next)} {}
};

class Character {
   private:

	const Race race;
    int hp_max;
	int hp;
	int atk;
	int def;
	int gold;

	void validate();
	// END Instance

	// Manager
	//static std::vector<std::shared_ptr<Character>> list;
	//static void remove(std::weak_ptr<Character> c);  Character(Race_Meta&);
public:

	static void modify(std::unique_ptr<Modifier>);
	//static std::weak_ptr<Character> create(Race_Meta, std::weak_ptr<Character_Observer> o = {});
	//static void delete_all(); 
	// END Manager


	// Instance
	Race get_race();
	int get_atk();
	int get_def();
	int get_hp();
	int get_gold();
	Character(const Race_Meta&);
	void set_hp(int);
	
	~Character();


};



#endif