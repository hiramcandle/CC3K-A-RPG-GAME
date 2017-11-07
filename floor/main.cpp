#include <iostream>
#include <memory>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <utility>
#include <ctime>
#include <stdexcept>
#include "floor.h"
#include "../character/races.h"

using namespace std;

void read_map(int startRow, const string fileName, vector<vector<char>> &map) {
	string line;
	ifstream emptyMap (fileName);
	if(emptyMap.fail()) {cout << "NO SUCH FILE!" << endl; throw 2;}
	
	for (int r=0; r<startRow+25;r++){		
		getline (emptyMap,line);	
		if(r < startRow) {continue;}
		for (int c=0; c<79;c++){
			map[r - startRow][c] = line[c];
		}
	}
	emptyMap.close();
}

int main (int argc, char *argv[]) {
	bool emptymap = true;
	srand((unsigned)time(0));
	bool endgame = false;
	bool chooserace = false;
    int floornum = 1;
    int playerhp = 125;
	string fileName = "stdFloor.txt";
    vector<vector<char>> map(25,vector<char>(79));
    int startRow = 0;
    string s;
    string race = "s";
    shared_ptr<Floor> f;

	if(argc == 2) { emptymap = false; fileName = argv[1];}
		
		while(!endgame) {
   		    
			try{read_map(startRow, fileName, map);}
			catch(int) {return 1;}
			f = make_shared<Floor>(map,floornum, emptymap);
			if(emptymap) {f->spawn(Shade);}
			if(floornum == 1) {
		  		 cout << "Welcom to the CC3K World!" << endl << endl;
   		  		  cout << "Choose a Race first!"  << endl;
   		    } else { f->textDisplay();}

			if(!(race == "s")) {f->change_race(race);}
			f->setplayer_hp(playerhp);

			while(cin >> s) {
				if(s == "r") {floornum = 1; startRow = 0; race = "s"; 
				              chooserace = false; playerhp = 125; break;}
				if(s == "q") {endgame = true; cout << "YOU COWARD!" << endl; break;}
				
				if(chooserace == false) {
				if(s == "d" || s == "v" || s == "g" || s == "t") {
 		       	  f->change_race(s);
 		       	  f->textDisplay();
 		       	  chooserace = true;
 		       	  race = s;
 		       	  continue;
 		       	  } else {
 		       	  	cout << "You choose to be a Shade! Bad option."<< endl; 
 		       	  	f->textDisplay();
 		       	  	chooserace = true;
 		       	  	continue;
 		       	  	}
 		       	}

 		       		if(s == "f") {f->stopmove(); f->textDisplay(); continue;}
 		       		if(s == "no" || s == "so" || s == "ea" || s == "we" || s == "ne" || s == "nw" || s == "se" || s == "sw") {
 		       			int i;
 		       			if(s == "no") {i = f->player_move(Direction::NO);}
 		       			if(s == "so") {i = f->player_move(Direction::SO);}
 		       			if(s == "ea") {i = f->player_move(Direction::EA);}
 		       			if(s == "we") {i = f->player_move(Direction::WE);}
 		       			if(s == "ne") {i = f->player_move(Direction::NE);}
 		       			if(s == "nw") {i = f->player_move(Direction::NW);}
 		       			if(s == "se") {i = f->player_move(Direction::SE);}
 		       			if(s == "sw") {i = f->player_move(Direction::SW);}
 		       			if(i == 0 || i == 1) {
 		       				f->update();
 		       				if(f->is_death() == 1) {cout <<"You Died!" << endl; return 1;}
 		       				f->textDisplay();
 		       				continue;
 		       			} else {
 		       				if(floornum == 5) {
 		       					cout << "You Win! Score: " << f->getscore()<< endl;
 		       					return 0;
 		       				}
 		       				++floornum;
 		       				if(!emptymap) {startRow += 25;}
 		       				playerhp = f->getplayer_hp();
 		       				break;
 		       			}
 		       		}
 		       		if(s == "u") { 
 		       			cin >> s;
 		       			if(s == "no") {f->get_item(Direction::NO);}
 		       			if(s == "ne") {f->get_item(Direction::NE);}
 		       			if(s == "nw") {f->get_item(Direction::NW);}
 		       			if(s == "so") {f->get_item(Direction::SO);}
 		       			if(s == "se") {f->get_item(Direction::SE);}
 		       			if(s == "sw") {f->get_item(Direction::SW);}
 		       			if(s == "we") {f->get_item(Direction::WE);}
 		       			if(s == "ea") {f->get_item(Direction::EA);} 
 		       			f->update();
 		       			if(f->is_death() == 1) {cout <<"You Died!" << endl; return 1;}
 		       			f->textDisplay(); 
 		       			continue;		       			
 		       		}
 		       		if(s == "a") {
 		       			cin >> s;
 		       			if(s == "no") {f->attack(Direction::NO);}
 		       			if(s == "ne") {f->attack(Direction::NE);}
 		       			if(s == "nw") {f->attack(Direction::NW);}
 		       			if(s == "so") {f->attack(Direction::SO);}
 		       			if(s == "se") {f->attack(Direction::SE);}
 		       			if(s == "sw") {f->attack(Direction::SW);}
 		       			if(s == "we") {f->attack(Direction::WE);}
 		       			if(s == "ea") {f->attack(Direction::EA);} 
 		       			f->update();
 		       			if(f->is_death() == 1) {cout <<"You Died!" << endl; return 1;}
 		       			f->textDisplay();
 		       			continue;
 		       		}
 		       	}
 		   }
 		   
 	return 0;
}
