#include"position.h"
#ifndef board_pieces
#define board_pieces

class room //purely virtual class to base rooms off of
{
protected:
	position room_tiles;

public:
	room() {};
	room(int x, int y) { room_tiles.set_x_axis(x), room_tiles.set_y_axis(y); }
	virtual ~room() {};
	virtual position get_room_size() { return room_tiles;}
	virtual void get_info();
};

class character //class to create player character and enemies
{
protected:
	std::string name = " ";
	int hit_points = 10;
	int attack = 2;
	int defense = 2;
	int speed = 2;
	int range = 2;
	std::vector<std::string> items;
	position tile{1,1};

public:
	character() = default;
	character(std::string name_in, int hp, int atk, int def, int spd, int rng) { name = name_in, hit_points = hp, attack = atk, defense = def, speed = spd, range = rng; }
	virtual ~character() {};
	virtual void get_item(std::string item_in);
	void set_hit_points(int hp) { hit_points = hp; }
	int get_hp() { return hit_points; }
	int get_attack() { return attack; }
	int get_defense() { return defense; }
	int get_speed() { return speed; }
	int get_range() { return range; }
	virtual void attack_character(character& c);
	virtual void get_info();
	virtual void set_position(int x, int y) { tile.set_position(x, y); }
	virtual void move_tiles(int x, int y);
	virtual bool in_range(const character &c); //function to check if a character is in range of another

	character(const character&);
	character(character&&);

	character& operator=(character& c);
};

class non_player_character : public character
{
public:
	non_player_character() : character() {};
	non_player_character(std::string name_in, int hp, int atk, int def, int spd, int rng) : character{ name_in, hp, atk, def, spd, rng } {};
	virtual ~non_player_character() {};

};

class player_character : public character
{
protected:
	double damage_modifier = 1.0;
public:
	player_character() : character{} {};
	player_character(std::string name_in, int hp, int atk, int def, int spd, int rng) : character{ name_in, hp, atk, def, spd, rng } {};
	virtual ~player_character() {};
	void attack_character(character& c);
	virtual double special_attack();
	void get_item(std::string item_in);
	double get_damage_modifier() { return damage_modifier; }
	virtual double set_damage_modifier(double mod_in) { return damage_modifier = mod_in; }
};

class warrior : public player_character
{
protected:
public:
	warrior() : player_character{ "Warrior", 8, 3, 2, 1, 2 } { damage_modifier = 1.5; }
	~warrior() {};
	double special_attack();
	double set_damage_modifier(double mod_in);

};
class mage : public player_character
{
protected:

public:
	mage() : player_character{ "Mage", 6, 3, 1, 1, 3 } { damage_modifier = 1.2; };
	~mage() {};
	double special_attack();
	double set_damage_modifier(double mod_in);
};

class enemy : public non_player_character
{
protected:
	int spawn_number = 1;

public:
	enemy(int x, std::string name_in, int hp, int atk, int def, int spd, double rng) : non_player_character{ name_in, hp, atk, def, spd, rng } { spawn_number = x; }
	enemy() {};
	virtual ~enemy() {};
	int get_spawn_number() { return spawn_number; }
};

class skeleton : public enemy
{
public:
	skeleton() : enemy{ 1, "Skeleton", 3, 2, 1, 1, 1 } {};
	~skeleton() {};

};

class goblin : public enemy
{
public:
	goblin() : enemy{ 1, "Goblin", 2, 1, 1, 3, 1 } {};
	~goblin() {};
};

class bat : public enemy
{
public:
	bat() : enemy{ 1, "Bat", 1, 2, 1, 3, 2 } {};
	~bat() {};
};

/*class merchant : public non_player_character
{
public:
	merchant() : non_player_character{} {};
	~merchant() {};
	void show_items();
};*/

class boss : public non_player_character
{
protected:
	double damage_modifier = 1.2; //In order to make bosses tougher than regular enemies they gain modifiers to the amount of damage they will deal

public:
	boss() : non_player_character{} {};
	boss(std::string name_in, int hp, int atk, int def, int spd, double rng, double dmg_mod) : non_player_character(name_in, hp, atk, def, spd, rng) { damage_modifier = dmg_mod; }
	virtual ~boss() {};
	virtual double get_damage_modifier() { return damage_modifier; }
	virtual void attack_character(player_character& pc);
};

class gargoyle : public boss
{
public:
	gargoyle() : boss{ "Gargoyle", 10, 2, 2, 2, 2, 1.5} {};
	~gargoyle() {};
};

#endif