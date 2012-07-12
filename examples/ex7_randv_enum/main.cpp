
#include <crave/ConstrainedRandom.hpp>

using crave::rand_obj;
using crave::randv;

#define IF_THEN(a, b) !(a) || (b)
#define IF_THEN_ELSE(a, b, c) (!(a) || (b)) && ((a) || (c))

enum car_type_enum {
	AUDI = 1,
	BMW = 2,
	MERCEDES = 3,
	VW = -1		
};
CRAVE_ENUM(car_type_enum, 4, AUDI, BMW, MERCEDES, VW);

enum color_enum {
	RED,
	GREEN,
	BLUE
};
CRAVE_ENUM(color_enum, 3, RED, GREEN, BLUE);

class my_rand_obj : public rand_obj {
public:
	randv<car_type_enum> car; 
	randv<color_enum> color; 
	randv<int> price; 

	my_rand_obj(rand_obj* parent = 0) : rand_obj(parent), car(this), color(this), price(this) {
		constraint(IF_THEN(car() == AUDI, color() != GREEN));
		constraint(IF_THEN(car() == BMW, color() != RED));
		constraint(IF_THEN(car() == MERCEDES, color() != BLUE));
		constraint(20 < price() && price() < 100);
		constraint(price() % 5 == 0);
		constraint(IF_THEN(car() == VW, price() <= 40));
		constraint(IF_THEN(color() == RED, price() >= 40));
	} 

	friend ostream& operator<<(ostream& os, my_rand_obj& obj) { 
		switch (obj.color) {
			case RED: os << "RED"; break;
			case GREEN: os << "GREEN"; break;
			case BLUE: os << "BLUE"; break;
			default: os << "UNKNOWN(" << obj.color << ")";
		}
		os << " ";
		switch (obj.car) {
			case AUDI: os << "AUDI"; break;
			case BMW: os << "BMW"; break;
			case MERCEDES: os << "MERCEDES"; break;
			case VW: os << "VW"; break;
			default: os << "UNKNOWN(" << obj.car << ")";
		}
		os << " ";
		os << obj.price;
   		return os; 
	}
};

int main (int argc , char *argv[]) {
	my_rand_obj obj;
	for (int i = 0; i < 20; i++) {
		std::cout << obj.next() << " " << obj << std::endl;
	}
	return 0;
}
