#include "races.h"

bool Race_Meta::operator<(const Race_Meta &other) const {
	return this->race < other.race;
}
extern const Race_Meta Shade = {
	Race::Shade,125,25,25,0,true
};

extern const Race_Meta Drow = {
	Race::Drow,150,25,15,0,true
};

extern const Race_Meta Vampire = {
	Race::Vampire,50,25,25,0,false
};

extern const Race_Meta Troll = {
	Race::Troll,120,25,15,0,true
};

extern const Race_Meta Goblin = {
	Race::Goblin,110,15,20
};

// Enemies
extern const Race_Meta Human = {
	Race::Human,140,20,20,4,true
};

extern const Race_Meta Dwarf = {
	Race::Dwarf,100,20,30,0,true
};

extern const Race_Meta Elf = {
	Race::Elf,140,30,10
};

extern const Race_Meta Orc = {
	Race::Orc,180,30,25
};

extern const Race_Meta Merchant = {
	Race::Merchant,30,70,5,4,true
};

extern const Race_Meta Dragon = {
	Race::Dragon,150,20,20
};

extern const Race_Meta Halfling = {
	Race::Halfling,100,15,20
};
