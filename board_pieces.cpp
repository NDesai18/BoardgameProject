#include"board_pieces.h"

void room::get_info()
{
	std::cout << "Room dimensions" << room_tiles << std::endl;
	//Add room print function here
}


void character::get_item(std::string item_in)
{
	items.push_back(item_in);
}

void character::attack_character(character& c)
{
	if (in_range(c) == true) {
		int damage_dealt = attack - c.defense;
		c.hit_points -= damage_dealt;
	}
	else {
		std::cout << "Attack target not in range" << std::endl;
	}
}

void character::move_tiles(int x, int y)
{
	position a(x, y);
	int tiles_moved = tile.calculate_tile_difference(a);
	if (tiles_moved > speed) {
		std::cout << "Tile out of range" << std::endl;
	}
	else {
		tile.set_position(x, y);
	}
}

void character::get_info()
{
	std::cout << name << ":" << std::endl;
	std::cout << "HP = " << hit_points << std::endl;
	std::cout << "Attack = " << attack << std::endl;
	std::cout << "Defense = " << defense << std::endl;
	std::cout << "Speed = " << speed << std::endl;
	std::cout << "Range = " << range << std::endl;
	std::cout << "Position: " << tile << std::endl;
}

bool character::in_range(const character& c)
{
	if (tile.calculate_tile_difference(c.tile) <= range) {
		return true;
	}
	else {
		return false;
	}
}

character::character(const character& c)
{
	name = c.name;
	hit_points = c.hit_points;
	attack = c.attack;
	defense = c.defense;
	speed = c.speed;
	range = c.range;
	for (int i = 0; i < c.items.size(); i++) {
		items[i] = c.items[i];
	}
	tile = c.tile;
}

character::character(character&& c)
{
	name = c.name;
	hit_points = c.hit_points;
	attack = c.attack;
	defense = c.defense;
	speed = c.speed;
	range = c.range;
	for (int i = 0; i < c.items.size(); i++) {
		items[i] = c.items[i];
	}
	tile = c.tile;
	c.name.clear();
	c.hit_points = 0;
	c.attack = 0;
	c.defense = 0;
	c.range = 0;
	c.speed = 0;
	c.tile = 0;
	c.items.~vector();
}

character& character::operator=(character& c)
{
	if (&c == this) {
		return *this;
	}
	name = c.name;
	hit_points = c.hit_points;
	attack = c.attack;
	defense = c.defense;
	speed = c.speed;
	range = c.range;
	for (int i = 0; i < c.items.size(); i++) {
		items[i] = c.items[i];
	}
	tile = c.tile;
	return *this;
}

double player_character::special_attack()
{
	double damage_dealt = attack * 2 * damage_modifier;
	return damage_dealt;
}

void player_character::get_item(std::string item_in)
{
	items.push_back(item_in);
}

double player_character::get_damage_modifier()
{
	return damage_modifier;
}

void player_character::attack_character(character& c)
{
	if (in_range(c) == true) {
		int damage_dealt = floor((attack - c.get_defense()) * damage_modifier);
		int temp_hp = c.get_hp();
		temp_hp -= damage_dealt;
		if (temp_hp < 0) {
			temp_hp = 0;
		}
		return c.set_hit_points(temp_hp);
	}
	else {
		std::cout << "Attack target not in range" << std::endl;
	}
}

double warrior::special_attack()
{
	double damage_dealt = attack * 3;
	return damage_dealt;
}

double warrior::set_damage_modifier(double mod_in)
{
	return damage_modifier = mod_in;
}


double mage::special_attack()
{
	double damage_dealt = attack * 2;
	return damage_dealt;
}

double mage::set_damage_modifier(double mod_in)
{
	return damage_modifier = mod_in;
}

int enemy::get_spawn_number()
{
	return spawn_number;
}

/*void merchant::show_items()
{
	for (int i = 0; i < items.size(); i++) {
		std::cout << items[i] << std::endl;
	}
}*/

void boss::attack_character(player_character& pc)
{
	if (in_range(pc) == true) {
		int damage_dealt = floor((attack - pc.get_defense()) * damage_modifier);
		int temp_hp = pc.get_hp() - damage_dealt;
		if (temp_hp < 0) {
			temp_hp = 0;
		}
		pc.set_hit_points(temp_hp);
	}
	else {
		std::cout << "Target out of range" << std::endl;
	}
}
