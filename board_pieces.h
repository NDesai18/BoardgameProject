#include"position.h"
#ifndef board_pieces
#define board_pieces

class character //class to create player character and enemies
{
protected:
	std::string name = " ";
	int max_hp = 10;
	int hit_points = 10;
	int attack = 2;
	int defense = 2;
	int speed = 2;
	int range = 2;
	std::vector<std::string> items;
	position tile{1,1};

public:
	character() = default;
	character(std::string name_in, int hp, int atk, int def, int spd, int rng) { name = name_in, max_hp = hp, hit_points = hp, attack = atk, defense = def, speed = spd, range = rng; }
	virtual ~character() {};

	virtual void set_hit_points(int hp) { hit_points = hp; }
	virtual std::string get_name() { return name; }
	virtual int get_hp() { return hit_points; }
	virtual int get_attack() { return attack; }
	virtual int get_defense() { return defense; }
	virtual int get_speed() { return speed; }
	virtual int get_range() { return range; }
	virtual position get_tile() { return tile; }
	virtual void set_position(int x, int y) { tile.set_position(x, y); }
	virtual double set_damage_modifier() { return 1.0; }

	virtual void get_item(std::string item_in);
	virtual bool find_item(std::string item);
	virtual int heal_hp();
	virtual void increment_attack();
	virtual void increment_defense();
	virtual void attack_character(character& c);
	virtual void get_info();
	virtual void move_tiles(int x, int y);
	virtual bool in_range(const character& c); //function to check if a character is in range of another
	virtual void get_allowed_moves(int x_limit, int y_limit);

	character(const character&);
	character(character&&);

	character& operator=(character& c);
};

class non_player_character : public character
{
public:
	non_player_character() : character{} {};
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
	virtual double get_damage_modifier() { return damage_modifier; }
	virtual double set_damage_modifier() { return damage_modifier = 1.0; }

	virtual void attack_character(character& c);
	virtual void get_info();


	player_character(const player_character& pc) : character{pc} {};
	player_character(player_character&& pc) : character{pc} {};
};

class warrior : public player_character
{
protected:
public:
	warrior() : player_character{ "Warrior", 8, 2, 2, 2, 1 } { damage_modifier = 1.0; }
	~warrior() {};
	double set_damage_modifier();

	warrior(const warrior& w) : player_character(w) {};
	warrior(warrior&& w) : player_character(w) {};

};
class mage : public player_character
{
protected:
public:
	mage() : player_character{ "Mage", 7, 2, 2, 2, 2 } { damage_modifier = 1.0; }
	~mage() {};
	double set_damage_modifier();

	mage(const mage& m) : player_character(m) {};
	mage(mage&& m) : player_character(m) {};
};

class enemy : public non_player_character
{
protected:
	int spawn_number = 1;

public:
	enemy(int x, std::string name_in, int hp, int atk, int def, int spd, int rng) : non_player_character{ name_in, hp, atk, def, spd, rng } { spawn_number = x; }
	enemy() {};
	virtual ~enemy() {};
	virtual int get_spawn_number() { return spawn_number; }
};

class skeleton : public enemy
{
public:
	skeleton() : enemy{ 1, "Skeleton", 3, 3, 1, 1, 1 } {};
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

class boss : public non_player_character
{
protected:
	double damage_modifier = 1.2; //In order to make bosses tougher than regular enemies they gain modifiers to the amount of damage they will deal

public:
	boss() : non_player_character{} {};
	boss(std::string name_in, int hp, int atk, int def, int spd, int rng, double dmg_mod) : non_player_character(name_in, hp, atk, def, spd, rng) { damage_modifier = dmg_mod; }
	virtual ~boss() {};
	virtual double get_damage_modifier() { return damage_modifier; }
	virtual void attack_character(player_character& pc);
};

class gargoyle : public boss
{
public:
	gargoyle() : boss{ "Gargoyle", 10, 4, 2, 2, 2, 2.0} {};
	~gargoyle() {};
};

class room //purely virtual class to base rooms off of
{
protected:
	std::string name = " ";
	position room_tiles;
	

public:
	room() {};
	room(std::string name_in, int x, int y) { room_tiles.set_x_axis(x), room_tiles.set_y_axis(y), name = name_in; }
	~room() {};
	virtual position get_room_size() { return room_tiles; }
	virtual void get_info();

	room(const room& r);
	room(room&& r);

	room& operator=(const room& r);
};

class spawn_room : public room
{
public:
	spawn_room() : room{ "Spawn ", 2, 2 } {};
	~spawn_room() {};
};

class skeleton_room : public room
{
public:
	skeleton_room() : room{ "Skeleton ", 5, 5 } {};
	~skeleton_room() {};
};

class gargoyle_room : public room
{
public:
	gargoyle_room() : room{ "Gargoyle ", 7, 7 } {};
	~gargoyle_room() {};
};

#endif