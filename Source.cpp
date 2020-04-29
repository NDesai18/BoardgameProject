#include"board_pieces.h"

int main()
{
	std::cout << "Welcome to Boardgame.exe" << std::endl;
	std::vector<character*> character_list;
	warrior pc;
	character* player_pointer = &pc;
	character_list.push_back(player_pointer);
	skeleton e;
	character* enemy_pointer = &e;
	character_list.push_back(enemy_pointer);
	pc.set_position(3,2);
	e.set_position(2, 1);
	for (int i = 0; i < character_list.size(); i++) {
		character_list[i]->get_info();
	}
	pc.set_damage_modifier(2.0);
	pc.attack_character(e);
	return 0;
}