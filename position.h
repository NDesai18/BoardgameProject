#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include<string>
#include<memory>
#include<algorithm>

#ifndef coordinates
#define coordinates
class position //A class to track the position of characters in rooms
{
	
protected:
	int x_axis = 0;
	int y_axis = 0;

	friend std::ostream& operator<<(std::ostream& os, const position& p);

public:
	position() {};
	position(int x, int y) { x_axis = x, y_axis = y; }
	~position() {};
	int get_x_axis() { return x_axis; }
	int get_y_axis() { return y_axis; }
	void set_position(int x, int y);
	void set_x_axis(int x) { x_axis = x; }
	void set_y_axis(int y) { y_axis = y; }
	position relative_position(const position& p);
	int calculate_tile_difference(const position& p);

	position(const position& p);
	position(position&& p);

	position& operator=(const position& p);
	position& operator=(position&& p);

	position& operator=(const int a);
};
#endif
