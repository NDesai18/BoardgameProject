#include"board_pieces.h"

void character::get_item(std::string item_in)
{
	std::cout << name << " gained a " << item_in << std::endl;
	items.push_back(item_in);
}

bool character::find_item(std::string item)
{
	if (std::find(items.begin(), items.end(), item) != items.end()) {
		return true;
	}
	else {
		return false;
	}
}

void character::increment_attack()
{
	attack++;
	std::cout << "Attack increased by 1" << std::endl;
}

void character::increment_defense()
{
	defense++;
	std::cout << "Defense increased by 1" << std::endl;
}

void character::attack_character(character& c)
{
	if (in_range(c) == true) {
		int damage_dealt = attack - c.defense;
		c.hit_points -= damage_dealt;
		std::cout << c.name << " received " << damage_dealt << " damage." << std::endl;
	}
	else {
		std::cout << "Attack target not in range" << std::endl;
	}
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
		std::cout << c.get_name() << "received " << damage_dealt << " damage." << std::endl;
		return c.set_hit_points(temp_hp);
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
	std::cout << "Range = " << range << std::endl;
	std::cout << "Position: " << tile << std::endl;
}

void player_character::get_info()
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

int character::heal_hp()
{
	hit_points += floor(hit_points / 2);
	if (hit_points > max_hp) {
		std::cout << name << " was fully healed!" << std::endl;
		return hit_points = max_hp;
	}
	else {
		std::cout << name << " was healed for " << floor(hit_points / 2) << "HP" << std::endl;
		return hit_points;
	}
}

void character::get_allowed_moves(int x_limit, int y_limit)
{
	int x1, x2, y1, y2;
	x1 = tile.get_x_axis() + speed;
	x2 = tile.get_x_axis() - speed;
	y1 = tile.get_y_axis() + speed;
	y2 = tile.get_y_axis() - speed;

	if (x1 > x_limit) {
		x1 = x_limit;
	}
	if (x2 < 1) {
		x2 = 1;
	}
	if (y1 > y_limit) {
		y1 = y_limit;
	}
	if (y2 < 1) {
		y2 = 1;
	}

	position t1(x1, tile.get_y_axis());
	position t2(x2, tile.get_y_axis());
	position t3(tile.get_x_axis(), y1);
	position t4(tile.get_x_axis(), y2);

	std::cout << "Range of movement for the " << name << " is defined by anything within these 4 coordinates" << std::endl;
	std::cout << t1 << std::endl;
	std::cout << t2 << std::endl;
	std::cout << t3 << std::endl;
	std::cout << t4 << std::endl;
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

double warrior::set_damage_modifier()
{
	if (find_item("Silver Sword") == true) {
		std::cout << name << "'s damage modifier has increased" << std::endl;
		return damage_modifier = 2.0;
	}
}

double mage::set_damage_modifier()
{
	if (find_item("Ancient Staff") == true) {
		std::cout << name << "'s damage modifier has increased" << std::endl;
		return damage_modifier = 3.0;
	}
}

void boss::attack_character(player_character& pc)
{
	if (in_range(pc) == true) {
		int damage_dealt = floor((attack - pc.get_defense()) * damage_modifier);
		int temp_hp = pc.get_hp() - damage_dealt;
		if (temp_hp < 0) {
			temp_hp = 0;
		}
		pc.set_hit_points(temp_hp);
		std::cout << pc.get_name() << " received " << damage_dealt << " damage" << std::endl;
	}
	else {
		std::cout << "Target out of range" << std::endl;
	}
}

void room::get_info()
{
	std::cout << name << "Room, the dimensions are: " << room_tiles << std::endl;
	int x_counter, y_counter;
	for (y_counter = 0; y_counter < room_tiles.get_y_axis(); y_counter++) {
		for (x_counter = 0; x_counter <= room_tiles.get_x_axis(); x_counter++) {
			if (x_counter == room_tiles.get_x_axis()) {
				std::cout << std::endl;
			}
			else {
				std::cout << "O ";
			}
		}
	}
}

room::room(const room& r)
{
	name = r.name;
	room_tiles = r.room_tiles;
}

room::room(room&& r)
{
	name = r.name;
	room_tiles = r.room_tiles;
	r.name = " ";
	r.room_tiles = 0;
}

room& room::operator=(const room& r)
{
	if (&r == this) {
		return *this;
	}
	else {
		name = r.name;
		room_tiles = r.room_tiles;
		return *this;
	}
}