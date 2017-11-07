#ifndef _FLOOR_SPAWNER_H_
#define _FLOOR_SPAWNER_H_
#include <memory>
#include <cstdlib>
#include <map>

/* 
 * Note:
 * Object must implement Object(Object_t)
 */

template<typename Object, typename Object_t>
class Spawner{
	std::map<Object_t,int> strategy;
	int sum;
	public:
	Spawner(std::map<Object_t,int> map): strategy{map}, sum{0} {
		for(auto &pair : strategy){
			sum+=pair.second;
			pair.second=sum;
		}
	} 
	
	std::shared_ptr<Object> spawn(){
		int token=rand()%sum;
		for (auto pair : strategy){
			if(pair.second>token) return std::make_shared<Object>(pair.first);
		}
		return  nullptr;
	}
	
};

std::pair<int,int> rand_diff(int range){
	int first=rand()%range,second=rand()%range;
	while(first==second){
		second=rand()%range;
	}
	return {first,second};
}


#endif