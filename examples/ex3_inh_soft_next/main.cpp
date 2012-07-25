#include <crave/ConstrainedRandom.hpp>

using crave::rand_obj;
using crave::randv;
using crave::reference;

class item : public rand_obj {
public:
	item(rand_obj* parent = 0) : rand_obj(parent), src_addr(this), dest_addr(this) {
		constraint(src_addr() <= 20);
		constraint.soft(src_addr() % 4 == 0);
		constraint(dest_addr() <= 100);
	} 
     
	friend ostream& operator<<(ostream& os, item& it) { 
		os << it.src_addr << " " << it.dest_addr;
		return os; 
	}

	randv<uint> src_addr;
	randv<uint> dest_addr;
};

class item_ext : public item {
public:
	item_ext(rand_obj* parent = 0) : item(parent), last_dest_addr(0) {
		// item_ext inherits all constraints of item		
		constraint(src_addr() % 4 == 3); // this constraint makes the soft constraint in item useless.
		constraint(dest_addr() > reference(last_dest_addr)); 
	} 

	bool next() {
		// custom next() saves the generated value of dest_addr
		if (item::next()) {
			last_dest_addr = dest_addr;
			return true;
		}
		return false;
	}

	uint last_dest_addr;
};


int main (int argc , char *argv[]) {
	item it;
	for (int i = 0; i < 10; i++) {
		it.next();
		std::cout << it << std::endl;
	}
	std::cout << "***********************" << std::endl;
	item_ext it_ext;
	while (it_ext.next()) {
		std::cout << it_ext << std::endl;
	}
	return 0;
}
