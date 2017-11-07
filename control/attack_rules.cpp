#include "attack_rules.h"
#include "../character/character.h"
#include "../character/races.h"
#include "../floor/rulesout.h"
#include <sstream>
#include <cstdlib>
int ceiling(int a,int b){ return (a/b) + (a%b!=0); }


class Attack_Rule {
	public:
	static std::shared_ptr<Character> attacker;
	static std::shared_ptr<Character> target;
	//
	static int damage;
	virtual std::unique_ptr<Modifier> calculate()=0;
};
std::shared_ptr<Character> Attack_Rule::attacker={};
std::shared_ptr<Character> Attack_Rule::target={};
int Attack_Rule::damage=0;

class Attack_Base : public Attack_Rule {
	public:
	std::unique_ptr<Modifier> calculate() override{
		damage = -ceiling( 100 * attacker->get_atk(),(100+target->get_def()));
		return std::make_unique<Modifier>(
			target,
			Character_Field::HP,
			damage
		);
	}
};

class Decorator : public Attack_Rule {
	std::unique_ptr<Attack_Rule> next;
	virtual bool condition()=0;
	virtual std::unique_ptr<Modifier> apply(std::unique_ptr<Modifier>)=0;
	public:
	Decorator(std::unique_ptr<Attack_Rule> next):next{std::move(next)} { }

	std::unique_ptr<Modifier> calculate() override {
		std::unique_ptr<Modifier> m=next->calculate();
		if(condition()){
			return std::move(apply(std::move(m)));
		}else{
			return std::move(m);
		}
	}
};
// Inner most!!!
class Miss_Rate : public Decorator{
	bool condition() override {
		Race r=target->get_race();
		return r==Race::Shade || r== Race::Drow ||
		r==Race::Vampire || r==Race::Troll || r==Race::Goblin || 
		r==Race::Halfling;
	}
	
	std::unique_ptr<Modifier> apply(std::unique_ptr<Modifier> m) {
		if(rand()%2) return std::move(m);
		rules_out << "Attack missed! " ;
		damage=0;
		return nullptr;
	}
	public:
	Miss_Rate(std::unique_ptr<Attack_Rule> next):Decorator{std::move(next)} { }
};



class Vampire_Allergic : public Decorator {
	
	bool condition() override {
		return attacker->get_race()==Race::Vampire && 
			target->get_race()==Race::Dwarf;
	}
	
	std::unique_ptr<Modifier> apply(std::unique_ptr<Modifier> m) override {
		rules_out << "Vampire allergic applied. " ;
		return std::make_unique<Modifier>(
			attacker,
			Character_Field::HP,
			-5,
			std::move(m)
		); 
	}
	public:
	Vampire_Allergic(std::unique_ptr<Attack_Rule> next):Decorator{std::move(next)} { }
};

class Vampire_Regular : public Decorator {
	
	bool condition() override {
		return attacker->get_race()==Race::Vampire &&
		target->get_race()!=Race::Dwarf && damage <0;
	}

	std::unique_ptr<Modifier> apply(std::unique_ptr<Modifier> m) override {
		rules_out << "Vampire regular applied. ";
		return std::make_unique<Modifier>(
			attacker,
			Character_Field::HP,
			+5,
			std::move(m)
		); 
	}
	public:
	Vampire_Regular(std::unique_ptr<Attack_Rule> next):Decorator{std::move(next)} { }
	
};

class Goblin_Steal : public Decorator {
	
	bool condition() override {
		return attacker->get_race()==Race::Goblin && damage<0;
	}

	std::unique_ptr<Modifier> apply(std::unique_ptr<Modifier> m) override {
		rules_out << "Goblin is stealing. " ;
		return std::make_unique<Modifier>(
			attacker,
			Character_Field::GOLD,
			+5,
			std::move(m)
		); 
	}
	public:
	Goblin_Steal(std::unique_ptr<Attack_Rule> next):Decorator{std::move(next)} { }
	
};

class Orcs_Goblin : public Decorator{
	bool condition() override {
		return attacker->get_race()==Race::Orc && target->get_race()==Race::Goblin && damage<0;
	}
	std::unique_ptr<Modifier> apply(std::unique_ptr<Modifier> m) override {
		rules_out << "Orcs is killing Goblin. ";
		return std::make_unique<Modifier>(
			target,
			Character_Field::HP,
			damage/2,
			std::move(m)
		);
	}
	public:
	Orcs_Goblin(std::unique_ptr<Attack_Rule> next):Decorator{std::move(next)} { }

};

namespace Attack_Rules {
	//std::stringstream rules_out=std::stringstream{};
	
	static std::unique_ptr<Attack_Rule> rule=
	std::make_unique<Orcs_Goblin>(
	std::make_unique<Goblin_Steal>(
	std::make_unique<Vampire_Regular>(
	std::make_unique<Vampire_Allergic>(
	std::make_unique<Miss_Rate>(
	std::make_unique<Attack_Base>()
	)))));

	std::unique_ptr<Modifier>  calculate(std::weak_ptr<Character> attacker,std::weak_ptr<Character> target){
			Attack_Rule::attacker=attacker.lock();
			Attack_Rule::target=target.lock();
			Attack_Rule::damage=0;
			//rules_out=std::stringstream{};
			if(Attack_Rule::attacker&&Attack_Rule::target) return std::move(rule->calculate());
			return nullptr;
	}
}


