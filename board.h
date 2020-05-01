#include"board_pieces.h"
#ifndef board
#define board
class dungeon
{
protected:
	std::vector<std::unique_ptr<room>> room_list;
	std::vector<std::unique_ptr<character>> character_list;

public:
	dungeon() {};
	~dungeon() {};
	void get_info();
	void add_room(const int x);
	void add_character(const int x);
	int get_room_list_size() { return room_list.size(); }
	int get_character_list_size() { return character_list.size(); }
	character* index_character_list(const int i);
	room* index_room_list(const int i);
	void clear_board();
};
#endif
