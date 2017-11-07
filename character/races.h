#ifndef _RACES_H_
#define _RACES_H_


enum class Character_Field{
	HP,ATK,DEF,GOLD
};

enum class Race {
	Shade, Drow, Vampire, Troll, Goblin,
	Human, Dwarf, Elf, Orc, Merchant, Dragon, Halfling
};

struct Race_Meta{
	Race race;
	int hp,atk,def,gold=0;
	bool hp_max=true;
	bool operator<(const Race_Meta &) const;
};


// This is CS246 course staff :D
extern const Race_Meta Shade;

extern const Race_Meta Drow;

extern const Race_Meta Vampire;

extern const Race_Meta Troll;

extern const Race_Meta Goblin;

// Enemies
extern const Race_Meta Human;

extern const Race_Meta Dwarf;

extern const Race_Meta Elf;

extern const Race_Meta Orc;

extern const Race_Meta Merchant;

extern const Race_Meta Dragon;

extern const Race_Meta Halfling;


#endif