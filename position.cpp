#include"position.h"


std::ostream& operator<<(std::ostream& os, const position& p)
{
	os << "(x,y) = (" << p.x_axis << "," << p.y_axis << ")" << std::endl;
	return os;
}

position::position(const position& p)
{
	x_axis = p.x_axis;
	y_axis = p.y_axis;
}

position::position(position&& p)
{
	x_axis = p.x_axis;
	y_axis = p.y_axis;
	p.x_axis = 0;
	p.y_axis = 0;
}

void position::set_position(int x, int y)
{
	x_axis = x;
	y_axis = y;
}

position position::relative_position(const position& p)
{
	position temp;
	temp.x_axis = abs(x_axis - p.x_axis);
	temp.y_axis = abs(y_axis - p.y_axis);
	return temp;
}

int position::calculate_tile_difference(const position& p)
{
	position temp = relative_position(p);
	int tile_difference = temp.x_axis + temp.y_axis;
	return tile_difference;
}

position& position::operator=(const position& p)
{
	if (&p == this) {
		return *this;
	}
	else {
		x_axis = 0;
		y_axis = 0;
		x_axis = p.x_axis;
		y_axis = p.y_axis;
	}
	return *this;
}

position& position::operator=(position&& p)
{
	x_axis = p.x_axis;
	y_axis = p.y_axis;
	p.y_axis = 0;
	p.x_axis = 0;
	return *this;
}

position& position::operator=(const int a)
{
	position temp;
	temp.x_axis = a;
	temp.y_axis = a;
	return temp;
}
