#include "character.h"
#include "races.h"
#include <climits>
int max(int a, int b){ return a>b?a:b;}
int min(int a, int b){ return a>b?b:a;}


void Character::validate(){
	hp = min(hp,hp_max);
	hp = max(hp,0);
	atk = max(atk,0);
	def = max(def,0);
	gold = max(gold,0);
}

Character::Character(const Race_Meta &meta):
 race{meta.race}, hp_max{meta.hp_max?meta.hp:INT_MAX}, 
 hp{meta.hp}, atk{meta.atk}, def{meta.def}, gold{meta.gold}
{
	validate();
	//observer.lock()->update(list.back(), Character_Event::SPAWN);
}


Character::~Character(){
}
/*
void Character::remove(std::weak_ptr<Character> c){
	std::shared_ptr<Character> d=c.lock();
	for(auto i=list.begin(),end=list.end();i!=end;++i){
		if(*i == d){
			list.erase(i);
			break;
		}
	}
	if(auto obs = d->observer.lock()) obs->update(c,Character_Event::DEATH);
}
*/
Race Character::get_race(){ return race; }
int Character::get_atk(){ return atk; }
int Character::get_def(){ return def; }

int Character::get_hp(){ return hp; }

int Character::get_gold(){ return gold; }   

 
/*
int Character::attack(Character &other){
	int damage =  ceiling( 100 * this->get_atk(),(100+other.get_def()));
	other.HP_ -= damage;
	return damage;
}

*/
// Manager, static


void Character::modify(std::unique_ptr<Modifier> m){
	if(!m) return;
	{
		std::shared_ptr<Character> c = (m->ch).lock();
		if(c){
			int amount_=0;
			switch(m->field){
				case Character_Field::HP: 
					amount_ = c->hp += m->change;
					break;
				case Character_Field::ATK: 
					amount_ = c->atk += m->change;
					break;
				case Character_Field::DEF: 
					amount_ = c->def += m->change;
					break;	
				case Character_Field::GOLD:
					amount_ = c->gold += m->change;
					break;
			}
			c->validate();
			//if(auto obs=c->observer.lock()) obs->update(c,m->field,amount_);
			//if(c->hp<=0) remove(c) ;
		}
	}
	modify(std::move(m->next));
}

void Character::set_hp(int i) {this->hp = i;}
/*
std::weak_ptr<Character> Character::create(Race_Meta r,std::weak_ptr<Character_Observer> o){
	list.push_back(std::shared_ptr<Character>(new Character(r,o)));
	return list.back();
}

void Character::delete_all(){
	for(Character * ch : list) delete ch;
	list.clear();
}  */