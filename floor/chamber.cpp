#include <vector>
#include <utility>
#include <cstdlib>
#include "chamber.h"

using namespace std;



bool Chamber::is_in_chamber(int x, int y) {
	for(auto &c:pos) {
		if((c.first == x) && (c.second == y)) {
			return true;
		}
	}
	return false;
}

Chamber::Chamber(vector<pair<int,int>> pos): pos{pos} {}

pair<int,int> Chamber::spawn_pos() {
	int size = pos.size();
	int random = (rand() % size);
	return pos[random];
}

Chamber::~Chamber() {}

