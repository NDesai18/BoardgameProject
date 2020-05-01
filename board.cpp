#include"board.h"
void dungeon::add_character(const int x)
{
	switch (x)
	{
	case 1: {
		std::unique_ptr<character> pc(new warrior);
		character_list.push_back(std::move(pc));
		break;
	}
	case 2: {
		std::unique_ptr<character> pc(new mage);
		character_list.push_back(std::move(pc));
		break;
	}
	case 3: {
		std::unique_ptr<character> e(new skeleton);
		character_list.push_back(std::move(e));
		break;
	}
	case 4: {
		std::unique_ptr<character> e(new goblin);
		character_list.push_back(std::move(e));
		break;
	}
	case 5: {
		std::unique_ptr<character> e(new bat);
		character_list.push_back(std::move(e));
		break;
	}
	case 6: {
		std::unique_ptr<character> e(new gargoyle);
		character_list.push_back(std::move(e));
		break;
	}
	}
}

void dungeon::add_room(const int x)
{
	switch (x)
	{
	case 1: {
		std::unique_ptr<room> a(new spawn_room);
		room_list.push_back(std::move(a));
		break;
	}
	case 2: {
		std::unique_ptr<room> a(new skeleton_room);
		room_list.push_back(std::move(a));
		break;
	}
	case 3: {
		std::unique_ptr<room> a(new gargoyle_room);
		room_list.push_back(std::move(a));
		break;
	}
	}
}


character* dungeon::index_character_list(const int i)
{
	if (i >= character_list.size()) {
		std::cout << "Cannot index element" << std::endl;
	}
	else {
		character* temp = character_list[i].get();
		return temp;
	}
}

room* dungeon::index_room_list(const int i)
{
	if (i >= room_list.size()) {
		std::cout << "Cannot index element" << std::endl;
	}
	else {
		room* temp = room_list[i].get();
		return temp;
	}
}

void dungeon::get_info()
{
	std::cout << "The rooms traversed so far are " << std::endl;
	for (int i = 0; i < room_list.size(); i++) {
		room_list[i]->get_info();
	}
	std::cout << "The characters in the dungeon are/were " << std::endl;
	for (int i = 0; i < character_list.size(); i++) {
		character_list[i]->get_info();
	}
}

void dungeon::clear_board()
{
	for (int i = 0; i < character_list.size(); i++) {
		 character_list[i].~unique_ptr();
	}
	for (int i = 0; i < room_list.size(); i++) {
		room_list[i].~unique_ptr();
	}
}