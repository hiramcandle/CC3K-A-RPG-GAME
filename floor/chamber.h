#ifndef _CHAMBER_H_
#define _CHAMBER_H_
#include <vector>
#include <utility>
#include <cstdlib>

using namespace std;



class Chamber {

	vector<pair<int,int>> pos;
	public:

	Chamber(vector<pair<int,int>> pos);
	bool is_in_chamber(int x, int y);
	pair<int,int> spawn_pos();
	~Chamber();
};


#endif