#ifndef _FLOOR_H_
#define _FLOOR_H_
#include <vector>
#include <memory>
#include <iostream>

class Floor_Object;
class Character;
class Chamber;
class Item;
struct Race_Meta;
// Management Interface

enum class Event {DEATH};
enum class Direction { NW=0,NO,NE,EA,SE,SO,SW,WE }; 

class Floor {
	int floornum;
	bool smove;
	bool mattack;

	std::vector<std::shared_ptr<Floor_Object>> enemy;
	std::vector<std::shared_ptr<Floor_Object>> item;
	std::vector<std::vector<char>> terrain;
	std::vector<std::shared_ptr<Chamber>> chambers;

	std::shared_ptr<Floor_Object> thePlayer;
	
	public:

	Floor(std::vector<std::vector<char>>&, int, bool);

	bool is_occupied(int, int);
	void stopmove();
	void merchantattack();
	std::pair<int,int> spawnPos(int i);
	std::pair<int,int> get_des(int dx, int dy, Direction d);
	std::shared_ptr<Floor_Object> Catch(int, int);
	int normal_move(std::shared_ptr<Floor_Object>&, Direction);
	void random_move(std::shared_ptr<Floor_Object>);
	void change_race(std::string r);
	int getplayer_hp();
	void setplayer_hp(int);
	int getscore();
	

	int use_item(std::shared_ptr<Floor_Object>&);
	
	void get_item(Direction);
	int player_move(Direction d);
	void attack(Direction);
	
	int is_death();
	void update();

	void textDisplay();

	void spawn(const Race_Meta &);
};


#endif