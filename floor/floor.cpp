#include "object.h"
#include "floor.h"
#include "../character/character.h"
#include "../item/potion.h"
#include "../item/item.h"
#include "../item/treasure.h"
#include "../character/races.h"
#include "chamber.h"
#include "../control/attack_rules.h"
#include "../floor/rulesout.h"
#include "spawner.h"
#include <vector>
#include <iostream>
#include <memory>
#include <utility>
#include <string>
#include <map>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <cmath>

using namespace std;


map<Race, string> racedisplay {
	{Race::Shade, "Shade"},
	{Race::Drow, "Drow"},
	{Race::Vampire, "Vampire"},
	{Race::Troll, "Troll"},
	{Race::Goblin, "Goblin"},
	{Race::Human, "Human"},
	{Race::Dwarf, "Dwarf"},
	{Race::Elf, "Elf"},
	{Race::Orc, "Orc"},
	{Race::Merchant, "Merchant"},
	{Race::Dragon, "Dragon"},
	{Race::Halfling, "Halfling"}
};

map<Direction, int> dir {
	{Direction::NW, 0},
	{Direction::NO, 1},
	{Direction::NE, 2},
	{Direction::SW, 3},
	{Direction::SO, 4},
	{Direction::SE, 5},
	{Direction::EA, 6},
	{Direction::WE, 7}
};

//init enemy and item, then trasfer map to terrain.
void initFloor(vector<vector<char>> &map, 
               vector<shared_ptr<Floor_Object>> &enemy, 
               vector<shared_ptr<Floor_Object>> &item, shared_ptr<Floor_Object> & thePlayer) {

	for(int r = 0; r < 25; r++) {
		for(int c = 0; c < 79; c++) {
			switch (map[r][c]) {
				case '0' : {auto i = make_shared<Potion>(ItemNames::RH); 
				           auto o = make_shared<Floor_Object>(i,r,c);
				           item.push_back(o); 
				           map[r][c] = '.';
				           break;}
				case '1' : {auto i = make_shared<Potion>(ItemNames::BA); 
				           auto o = make_shared<Floor_Object>(i,r,c);
				           item.push_back(o); 
				           map[r][c] = '.';
				           break;}
				case '2' : {auto i = make_shared<Potion>(ItemNames::BD); 
				           auto o = make_shared<Floor_Object>(i,r,c);
				           item.push_back(o); 
				           map[r][c] = '.';
				           break;}
				case '3' : {auto i = make_shared<Potion>(ItemNames::PH); 
				           auto o = make_shared<Floor_Object>(i,r,c);
				           item.push_back(o); 
				           map[r][c] = '.';
				           break;}           
				case '4' : {auto i = make_shared<Potion>(ItemNames::WA); 
				           auto o = make_shared<Floor_Object>(i,r,c);
				           item.push_back(o); 
				           map[r][c] = '.';
				           break;}        
				case '5' : {auto i = make_shared<Potion>(ItemNames::WD); 
				           auto o = make_shared<Floor_Object>(i,r,c);
				           item.push_back(o); 
				           map[r][c] = '.';
				           break;}
				case '6' : {auto i = make_shared<Treasure>(ItemNames::NORMAL); 
				           auto o = make_shared<Floor_Object>(i,r,c);
				           item.push_back(o); 
				           map[r][c] = '.';
				           break;}  
				case '7' : {auto i = make_shared<Treasure>(ItemNames::SMALL); 
				           auto o = make_shared<Floor_Object>(i,r,c);
				           item.push_back(o); 
				           map[r][c] = '.';
				           break;}     
				case '8' : {auto i = make_shared<Treasure>(ItemNames::MERCHANT); 
				           auto o = make_shared<Floor_Object>(i,r,c);
				           item.push_back(o); 
				           map[r][c] = '.';
				           break;}            
				case '9' : {auto i = make_shared<Treasure>(ItemNames::DRAGON);
				           auto o = make_shared<Floor_Object>(i,r,c);
				           item.push_back(o); 
				           map[r][c] = '.';
				           break;}     
				case 'M' : {auto i = make_shared<Character>(Merchant); 
				           auto o = make_shared<Floor_Object>(i,r,c);
				           enemy.push_back(o); 
				           map[r][c] = '.';
				           break;}      
				case 'H' : {auto i = make_shared<Character>(Human); 
				           auto o = make_shared<Floor_Object>(i,r,c);
				           enemy.push_back(o); 
				           map[r][c] = '.';
				           break; }     
				case 'W' : {auto i = make_shared<Character>(Dwarf); 
				           auto o = make_shared<Floor_Object>(i,r,c);
				           enemy.push_back(o); 
				           map[r][c] = '.';
				           break;  }  
				case 'E' : {auto i = make_shared<Character>(Elf); 
				           auto o = make_shared<Floor_Object>(i,r,c);
				           enemy.push_back(o); 
				           map[r][c] = '.';
				           break;} 
				case 'O' : {auto i = make_shared<Character>(Orc); 
				           auto o = make_shared<Floor_Object>(i,r,c);
				           enemy.push_back(o); 
				           map[r][c] = '.';
				           break;}      
				case 'D' : {auto i = make_shared<Character>(Dragon); 
				           auto o = make_shared<Floor_Object>(i,r,c);
				           enemy.push_back(o); 
				           map[r][c] = '.'; 
				           break;}       
				case 'L' : {auto i = make_shared<Character>(Halfling); 
				           auto o = make_shared<Floor_Object>(i, r,c);
				           enemy.push_back(o); 
				           map[r][c] = '.';
				           break;} 
				case '@' : {auto i = make_shared<Character>(Shade); 
				           thePlayer = make_shared<Floor_Object>(i,r,c);			           
				           map[r][c] = '.'; 
				           break; }
				default : break;           
			}
		}
	}
}

//store every potion in one chamber into pos.
void findChamber(int x, int y, vector<vector<char>> &map, vector<pair<int,int>> &pos) {
	char c = map[x][y];
	if((c == '.') || (c == '\\')) {
		map[x][y] = 'F';
		pos.push_back(make_pair(x,y));
		findChamber(x + 1, y, map, pos);
		findChamber(x - 1, y, map, pos);
		findChamber(x, y + 1, map, pos);
		findChamber(x, y - 1, map, pos);
	} else {
		return;
	}
}
//generate all Chamber and push back to vector<shared_ptr<Chamber>> chembers.
void creatChamber(vector<vector<char>> map, vector<shared_ptr<Chamber>> &chambers) {
	for(int r = 0; r < 25; r++) {
		for(int c = 0; c < 79; c++) {
			if(map[r][c] == '.' || map[r][c] == '\\') {
				vector<pair<int,int>> pos;
				findChamber(r, c, map, pos);
				auto chamb = make_shared<Chamber>(pos);
				chambers.push_back(chamb);
			}
		}
	}
}


Floor::Floor(vector<vector<char>> &map, int i,bool emepty):terrain(map), floornum(i), smove(false) {
	if(!emepty) {
	initFloor(terrain, enemy, item, thePlayer);	}
	creatChamber(terrain, chambers);	
}

void Floor::change_race(string r) {
	int x = thePlayer->get_x();
	int y = thePlayer->get_y();
	Race_Meta m;
	if(r == "s") {m = Shade;}
	if(r == "d") { m = Drow;}
	if(r == "v") { m = Vampire;}
	if(r == "g") { m = Goblin;}
	if(r == "t") { m = Troll;}
	auto c = make_shared<Character>(m);
	auto p = make_shared<Floor_Object>(c,x,y);
	thePlayer = p;
}

bool Floor::is_occupied(int x, int y) {
	if(!(terrain[x][y] == '.')) {return true;}
	for(auto &e : enemy) {
		if(!e->get_ch()) {continue;}
		int r = e->get_x();
		int c = e->get_y();
		if(r == x && c == y) {return true;}
	}
	for(auto &i : item) {
		if(!i->get_it()) {continue;}
		int r = i->get_x();
		int c = i->get_y();
		if(r == x && c == y) {return true;}
	}
	int px = thePlayer->get_x();
	int py = thePlayer->get_y();
	if(x == px && y == py) {return true;}
	return false;
}

pair<int,int> Floor::spawnPos(int i) {
	while(1) {
		auto p = chambers[i]->spawn_pos();
		int x = p.first;
		int y = p.second;
		if(!is_occupied(x,y)) {return p;}
	}
}

shared_ptr<Floor_Object> Floor::Catch(int x, int y) {
		for(auto &i : item) {
		int r = i->get_x();
		int c = i->get_y();
		if(r == x && c == y) {return i;}
	}
	for(auto &e : enemy) {
		int r = e->get_x();
		int c = e->get_y();
		if(r == x && c == y) {return e;}
	}
	
	return nullptr;
}

pair<int,int> Floor::get_des(int dx, int dy, Direction d) {
	if(d == Direction::NO) {dx -= 1;}
	if(d == Direction::SO) {dx += 1;}
	if(d == Direction::EA) {dy +=1;}
	if(d == Direction::WE) {dy -= 1;}
	if(d == Direction::NE) {dy +=1; dx -= 1;}
	if(d == Direction::NW) {dy -= 1; dx -= 1;}
	if(d == Direction::SE) {dy +=1; dx +=1;}
	if(d == Direction::SW) {dy -=1; dx += 1;}
	auto p = make_pair(dx,dy);
	return p;
}

int Floor::normal_move(shared_ptr<Floor_Object> &actor, Direction d) {
	int p;
	if(actor == thePlayer) { p = 1; }
	
	int dx = actor->get_x();
	int dy = actor->get_y();
    auto pa = get_des(dx, dy, d);
    dx = pa.first;
    dy = pa.second;
	
	if(p == 1) {
    	if(terrain[dx][dy] == '\\') {return 2;}
	    if(terrain[dx][dy] == '+' || terrain[dx][dy] == '#')
	    {actor->set_pos(dx,dy);
	    rules_out << "  PC moves in passage  ";
	    return 0;}
    }
   

	if(!is_occupied(dx,dy)) {
		if(p == 1) {rules_out << "  PC moves in chamber  ";}
		actor->set_pos(dx, dy);
		return 0;
	} else {
		auto o = Catch(dx, dy);
		if(o == nullptr) {
			if(p == 1) {rules_out << "  You can't go there!!!  ";}
			return 1;}
		if(p ==1) {
			if(o->get_it()) {
			if(o->get_it()->getType() == "treasure"){
				use_item(o);
				o->clearobject();
				actor->set_pos(dx, dy);
				return 0;  
			}
		}
		} 
	} 
	if(p == 1) {rules_out << "  You can't go there!!!  ";}
	return 1;
}

int Floor::player_move(Direction d) {
	return (normal_move(thePlayer, d));	
}

void Floor::random_move(std::shared_ptr<Floor_Object>e) {
	if(smove) {return;}
	int random = (rand() % 9);
	if(random == 8) {return;}
	Direction d;
	
	for(auto a : dir) {if(random == a.second) d = a.first;}
	int i = normal_move(e,d);
}

int Floor::is_death() {
	for(auto e = enemy.begin(); e != enemy.end(); ++e) {
		if(!(*e)->get_ch()) {continue;}
		int hp = (*e)->get_ch()->get_hp();
		if(hp == 0) {
			Race r = (*e)->get_ch()->get_race();
			int x = (*e)->get_x();
			int y = (*e)->get_y();
			rules_out << "  " << racedisplay[r] <<  "  got killed!  ";
			if(r == Race::Human) {
				shared_ptr<Treasure> g = make_shared<Treasure>(ItemNames::MERCHANT);
				auto o = make_shared<Floor_Object>(g,x,y);
				item.push_back(o);
			}else if(r == Race::Merchant) {
				auto g = make_shared<Treasure>(ItemNames::MERCHANT);
				auto o = make_shared<Floor_Object>(g,x,y);
				item.push_back(o);
			} else {
				int random = (rand() % 2);
				if(random == 0) {
					Character::modify(make_unique<Modifier>(thePlayer->get_ch(), Character_Field::GOLD,1));
				} else {
					Character::modify(make_unique<Modifier>(thePlayer->get_ch(), Character_Field::GOLD, 2));
				}
			}
			(*e)->clearobject();
		}
	}
	int playerhp = thePlayer->get_ch()->get_hp();
	if(playerhp == 0) {return 1;}
	return 0;
}

int Floor::use_item(shared_ptr<Floor_Object> &t){
	auto actor = thePlayer->get_ch();
	auto target = t->get_it();
	int i = 1;
	
	if(actor->get_race() == Race::Drow) {i = 1.5;}
	
		ItemNames pn = target->getName();
		int value = i * target->getValue();
		if(target->getType() == "potion") {
		if((pn == ItemNames::RH) || (pn == ItemNames::PH)) {
			if(value < 0) {
				rules_out << "  PC uses PH  ";
			} else {
				rules_out << "  PC uses RH  "; cout << value << endl;
			}			
			Character::modify(make_unique<Modifier>(thePlayer->get_ch(), Character_Field::HP, value));

		} else if(pn == ItemNames::BA || pn == ItemNames::WA) {
		
			if(value < 0) {
				rules_out << "  PC uses WA  ";
			} else {
				rules_out << "  PC uses BA  ";
			}
			Character::modify(make_unique<Modifier>(actor, Character_Field::ATK, value));
			
		} else if(pn == ItemNames::BD || pn == ItemNames::WD) {
			
			if(value < 0) {
				rules_out << "  PC uses WD  ";
			} else {
				rules_out << "  PC uses BD  ";
			}
			Character::modify(make_unique<Modifier>(actor, Character_Field::DEF, value));			
		} 
	} else {
		if(pn == ItemNames::DRAGON) {
			for(auto &e : enemy) {
				int x = e->get_x();
				int y = e->get_y();
				if(!e->get_ch()) {continue;}
				if(e->get_ch()->get_race() == Race::Dragon) {
					if(abs(x - t->get_x()) < 2 && abs(y - t->get_y()) < 2) {
						rules_out << "  You have to kill Dragon! ";
						return 1;
					}
				}
			}
		}
		rules_out << "PC gets " << value  << " Gold  ";
		Character::modify(make_unique<Modifier>(actor, Character_Field::GOLD, value));	
	}
    return 0;
}

void Floor::get_item(Direction d) {
	int x = thePlayer->get_x();
	int y = thePlayer->get_y();
    pair<int,int> p = get_des(x, y, d);
    x = p.first;
    y = p.second;
    
    auto o = Catch(x, y);
    if(o == nullptr) {
    	if(o->get_ch()==nullptr && o->get_it()==nullptr) {
    	rules_out << "  nothing there!   "; return;
  	  }	
  	  }
    if(o->get_type() == "item") {
    	int i;
    	if(o->get_it()->getType() == "potion") {
    	i = use_item(o);
    	o->clearobject();
    	return;
		}
		rules_out <<" Can't use this item. Try to walk over it! ";
   	}
	
 	return;
}

void Floor::attack(Direction d) {
	int x = thePlayer->get_x();
	int y = thePlayer->get_y();
	auto p = get_des(x, y, d);
	x = p.first;
	y = p.second;
	auto e = Catch(x,y);
	if(e == nullptr || e->get_ch() == nullptr) {rules_out << "   Do you want to attack air?   "; return;}
	if(e->get_type() == "character") {
		if(e->get_ch()->get_race() == Race::Merchant) {merchantattack();}
		Character::modify(Attack_Rules::calculate(thePlayer->get_ch(), e->get_ch()));
		rules_out << "You attack "<< racedisplay[e->get_ch()->get_race()] << " ( " <<e->get_ch()->get_hp()<<" HP )";
		int a = is_death();
	}
}

void Floor::stopmove() {
	smove = !smove;
}

void Floor::merchantattack() {
	mattack = true;
}

void Floor::update() {
	if(thePlayer->get_ch()->get_race() == Race::Troll) {
		Character::modify(make_unique<Modifier>(thePlayer->get_ch(), Character_Field::HP,5));
	}
	int x = thePlayer->get_x();
	int y = thePlayer->get_y();
	for(auto &e : enemy) {
		if(!e->get_ch()) {continue;}
		Race r = e->get_ch()->get_race();
		int ex = e->get_x();
		int ey = e->get_y();
		if((abs(x - ex) < 2) && (abs(y - ey) < 2)) {
			if(r == Race::Merchant && mattack == false) {random_move(e); continue;}
			int bhp = thePlayer->get_ch()->get_hp();
			Character::modify(Attack_Rules::calculate(e->get_ch(),thePlayer->get_ch()));
			int ahp = thePlayer->get_ch()->get_hp();
			rules_out << setw(2) << racedisplay[r] << " deals "<< bhp - ahp<< " damage to you ";
		} else {
		if(r == Race::Dragon) {continue;}
		random_move(e);
		}
	} 
}

int Floor::getplayer_hp() {
	return thePlayer->get_ch()->get_hp();
}

void Floor::setplayer_hp(int i) {
	thePlayer->get_ch()->set_hp(i);
}

int Floor::getscore() {
	float value = 1;
	if(thePlayer->get_ch()->get_race() == Race::Shade) {value = 1.5;}
	return (value * thePlayer->get_ch()->get_gold());
}

void Floor::textDisplay() {

	auto cpy = terrain;
	int x = thePlayer->get_x();
	int y = thePlayer->get_y();
	cpy[x][y] = '@';
	
		for(auto &i : item) {
		if(!i->get_it()) {continue;}
		int x = i->get_x();
		int y = i->get_y();
		string s = i->get_it()->getType();
		if(s == "potion") {
			cpy[x][y] = 'P';
			} else {cpy[x][y] = 'G';}  
	} 
	
	for(auto &e : enemy) {
		if(!e ->get_ch()) {continue;}
		int x = e->get_x();
		int y = e->get_y();
		Race r = e->get_ch()->get_race();
		switch (r) {
			case Race::Human : cpy[x][y] = 'H'; break;
			case Race::Dwarf : cpy[x][y] = 'W'; break;
			case Race::Elf : cpy[x][y] = 'E'; break;
			case Race::Orc : cpy[x][y] = 'O'; break;
			case Race::Merchant : cpy[x][y] = 'M'; break;
			case Race::Dragon : cpy[x][y] = 'D'; break;
			case Race::Halfling : cpy[x][y] = 'L'; break;
		}
	} 
	
	for(int r = 0; r < 25; r++) {
		 for(int c = 0; c < 79; c++) {
		 	cout << cpy[r][c];
		 }
		 cout << endl;
	} 

	cout << "Race: " << racedisplay[thePlayer->get_ch()->get_race()];
	cout << " Gold : " << thePlayer->get_ch()->get_gold();
	cout << setw(50) <<"Floor:  " << floornum << endl;
	cout << "HP:    " << thePlayer->get_ch()->get_hp() << endl;
	cout << "Atk:   " << thePlayer->get_ch()->get_atk() << endl;
	cout << "Def:   " << thePlayer->get_ch()->get_def() << endl;
	cout << "Action:   " << rules_out.str() << endl;
	rules_out.str("");
	
	if(enemy.size() == 0) {cout <<"here" << endl;}
}


void Floor::spawn(const Race_Meta &player){
	Spawner<Character, Race_Meta> character({{Human,4},{Dwarf,3},{Halfling,5},{Elf,2},{Orc,2},{Merchant,2}});
	Spawner<Potion, ItemNames> potion({{ItemNames::RH,1},{ItemNames::BA,1},{ItemNames::BD,1},{ItemNames::PH,1},{ItemNames::WA,1},{ItemNames::WD,1}});
	Spawner<Treasure, ItemNames> gold({{ItemNames::SMALL,2},{ItemNames::NORMAL,5},{ItemNames::DRAGON,1}});
	
	std::pair<int,int>	room_number = rand_diff(chambers.size()), location={};
	location=chambers[room_number.first]->spawn_pos();
	thePlayer=std::make_shared<Floor_Object>(std::make_shared<Character>(player),location.first,location.second);
	location=chambers[room_number.second]->spawn_pos();
	terrain[location.first][location.second]='\\';
	
	for(int i=0;i<10;++i) {
		int room=rand()%chambers.size();
		location=spawnPos(room);
		item.push_back(make_shared<Floor_Object>(potion.spawn(),location.first,location.second));
		room=rand()%chambers.size();
		location=spawnPos(room);
		std::shared_ptr<Treasure> g=gold.spawn();
		item.push_back(make_shared<Floor_Object>(g,location.first,location.second));
		if(g->getName()==ItemNames::DRAGON){
			while(1) {
				location=get_des(location.first,location.second,Direction(rand()%8));
				if(!is_occupied(location.first, location.second)) {
					enemy.push_back(std::make_shared<Floor_Object>(std::make_shared<Character>(Dragon),location.first,location.second));
					break;
				}
			}
		}	
	} 
	
	for(int i=0;i<20;++i){
		int room=rand()%chambers.size();
		location=spawnPos(room);
		auto e = character.spawn();

		enemy.push_back(make_shared<Floor_Object>(e,location.first,location.second));
	}
}



