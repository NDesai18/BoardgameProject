#include"board.h"

int check_input(int upper_limit, int lower_limit) //Checks input value is between two limits
{
	bool validated = false;
	int x_in;
	while (!validated) {
		std::cin >> x_in;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore();
			std::cout << "Please enter a number within the limits of the room" << std::endl;
			continue;
		}
		else if (x_in >= lower_limit && x_in <= upper_limit) {
			validated = true;
			return x_in;
		}
	}	
}

int validate_input(int in_1, int in_2) //Validates an input is one of two ints
{
	int a;
	bool input_validated = false;
	while (!input_validated) {
		std::cin >> a;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore();
			std::cout << "Please enter " << in_1 << " or " << in_2 << std::endl;
		}
		else if (a == in_1) {
			input_validated = true;
			return in_1;
		}
		else if (a == in_2) {
			input_validated = true;
			return in_2;
		}
		else {
			std::cin.clear();
			std::cin.ignore();
			std::cout << "Please enter " << in_1 << " or " << in_2 << std::endl;
			continue;
		}
	}
}

int main()
{
	dungeon game_board;
	std::cout << "Welcome to this tile-based boardgame. In this game, you will traverse rooms and encounter enemies, defeating the enemy will give you an item which will increase your character's strength." << std::endl;
	std::cout << "To beat the game you must enter the boss room and defeat the boss. You will enter the boss room after defeating one enemy." << std::endl;
	std::cout << "Every character has the following stats: HP, Attack, Defense, Speed and Range" << std::endl;
	std::cout << "HP stands for hit points, if these reach 0 the character dies. Attack determines how much damage you do, Defense determines how much damage you take, Speed determines how many tiles you can move and Range is how many tiles your attacks can reach over" << std::endl;
	warrior pc1;
	mage pc2;
	std::cout << "You can choose to play as either a Warrior [1] or a Mage [2], their stats are as follows" << std::endl;
	pc1.get_info();
	std::cout << std::endl;
	pc2.get_info();
	pc1.~warrior();
	pc2.~mage();
	int a;
	a = validate_input(1, 2);
	game_board.add_room(1);
	game_board.add_character(a);
	std::cout << "In order to fight you must approach an enemy, and then attack it. You can move and attack in the same turn but the enemy will attack in retaliation everytime you attack" << std::endl;

	//Player character chosen, start game setup
	const int character_index = 0; //Since the player character is the first character added to the vector, it will always be at position 0
	int room_counter = 1; //Room counter will keep a track of the current enemy since there is only one enemy per room

	game_board.add_character(3); //Add skeleton
	game_board.add_room(2); //Add skeleton room
	game_board.index_character_list(character_index)->set_position(3, 1);
	game_board.index_character_list(room_counter)->set_position(3, 4);
	std::cout << game_board.index_character_list(0)->get_name() << " ventures forward and enters the " << std::endl;
	game_board.index_room_list(room_counter)->get_info();
	std::cout << "Within this room is a " << std::endl;
	game_board.index_character_list(room_counter)->set_position(3, 4);
	game_board.index_character_list(room_counter)->get_info();

	//Set up encounter with generic enemy
	bool battle_end = false;
	while (!battle_end) {
		position room_limits = game_board.index_room_list(room_counter)->get_room_size();
		game_board.index_character_list(character_index)->get_allowed_moves(room_limits.get_x_axis(), room_limits.get_y_axis());

		std::cout << "Enter the x position you would like to move to, the player is currently at" << game_board.index_character_list(0)->get_tile() << std::endl;
		std::cout << "The " << game_board.index_character_list(room_counter)->get_name() << " is currently at " << game_board.index_character_list(room_counter)->get_tile() << std::endl;
		int x = check_input(room_limits.get_x_axis(), 1);
		std::cout << "Enter the y position you would like to move to" << std::endl;
		int y = check_input(room_limits.get_y_axis(), 1);
		game_board.index_character_list(character_index)->move_tiles(x, y);
		if (game_board.index_character_list(character_index)->in_range(*game_board.index_character_list(room_counter)) || game_board.index_character_list(room_counter)->in_range(*game_board.index_character_list(character_index))) {
			game_board.index_character_list(character_index)->attack_character(*game_board.index_character_list(room_counter));
			game_board.index_character_list(room_counter)->attack_character(*game_board.index_character_list(character_index));
		}
		if (game_board.index_character_list(room_counter)->get_hp() == 0) {
			std::cout << game_board.index_character_list(room_counter)->get_name() << " has been defeated" << std::endl;
			battle_end = true;
		}
		if (game_board.index_character_list(character_index)->get_hp() == 0) {
			std::cout << game_board.index_character_list(character_index)->get_name() << " has been defeated" << std::endl;
			battle_end = true;
			std::cout << "Game over" << std::endl;
			return 0;
		}
		else {
			continue;
		}
	}

	std::cout << "The " << game_board.index_character_list(0)->get_name() << " levelled up!" << std::endl;
	game_board.index_character_list(character_index)->increment_attack();
	game_board.index_character_list(character_index)->increment_defense();
	if (a == 1) {
		game_board.index_character_list(character_index)->get_item("Silver Sword");
	}
	else if (a == 2) {
		game_board.index_character_list(character_index)->get_item("Ancient Staff");
	}
	game_board.get_info();
	game_board.index_character_list(character_index)->set_damage_modifier();
	game_board.index_character_list(character_index)->heal_hp();

	//Set up the boss encounter
	game_board.add_character(6);
	game_board.add_room(3);
	room_counter++;
	game_board.index_character_list(room_counter)->set_position(4, 6);
	game_board.index_character_list(character_index)->set_position(4, 1);
	std::cout << game_board.index_character_list(character_index)->get_name() << " ventures forward and enters the ";
	game_board.index_room_list(room_counter)->get_info();
	std::cout << "Within this room is a " << std::endl;
	game_board.index_character_list(room_counter)->get_info();


	battle_end = false;
	while (!battle_end) {
		position room_limits = game_board.index_room_list(room_counter)->get_room_size();
		game_board.index_character_list(character_index)->get_allowed_moves(room_limits.get_x_axis(), room_limits.get_y_axis());

		std::cout << "Enter the x position you would like to move to, the player is currently at" << game_board.index_character_list(0)->get_tile() << std::endl;
		std::cout << "The " << game_board.index_character_list(room_counter)->get_name() << " is currently at " << game_board.index_character_list(room_counter)->get_tile() << std::endl;
		int x = check_input(room_limits.get_x_axis(), 1);
		std::cout << "Enter the y position you would like to move to" << std::endl;
		int y = check_input(room_limits.get_y_axis(), 1);
		game_board.index_character_list(character_index)->move_tiles(x, y);
		if (game_board.index_character_list(character_index)->in_range(*game_board.index_character_list(room_counter)) || game_board.index_character_list(room_counter)->in_range(*game_board.index_character_list(character_index))) {
			game_board.index_character_list(character_index)->attack_character(*game_board.index_character_list(room_counter));
			game_board.index_character_list(room_counter)->attack_character(*game_board.index_character_list(character_index));
		}
		if (game_board.index_character_list(room_counter)->get_hp() == 0) {
			std::cout << game_board.index_character_list(room_counter)->get_name() << " has been defeated" << std::endl;
			battle_end = true;
		}
		if (game_board.index_character_list(character_index)->get_hp() == 0) {
			std::cout << game_board.index_character_list(character_index)->get_name() << " has been defeated" << std::endl;
			battle_end = true;
			std::cout << "Game over" << std::endl;
			return 0;
		}
		else {
			continue;
		}
	}

	std::cout << "You win! Thanks for playing" << std::endl;
	game_board.get_info();
	

	return 0;
}
