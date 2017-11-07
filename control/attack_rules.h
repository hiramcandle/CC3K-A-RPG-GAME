#ifndef _ATTACK_RULES_H_
#define _ATTACK_RULES_H_
#include <memory>

#include "../character/races.h"
class Character;
struct Modifier;

namespace Attack_Rules {

	std::unique_ptr<Modifier> calculate(std::weak_ptr<Character>,std::weak_ptr<Character>);
};


#endif