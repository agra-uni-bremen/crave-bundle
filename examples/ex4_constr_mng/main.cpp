#include <crave/ConstrainedRandom.hpp>

using crave::rand_obj;
using crave::randv;
using crave::reference;

class item : public rand_obj {
public:
	item(rand_obj* parent = 0) : rand_obj(parent), src_addr(this), dest_addr(this), data(this) {
		src_addr.range(0, 0xFE);
		constraint(dest_addr() <= reference(src_addr));
		constraint("neg_data", -10 < data() && data() < 0 );
		constraint("pos_data", 10 > data() && data() > 0);
	} 
     
	friend ostream& operator<<(ostream& os, item& it) { 
		os << it.src_addr << " " << it.dest_addr << " " << it.data;
		return os; 
	}

	randv<uint> src_addr;
	randv<uint> dest_addr;
	randv<short> data;
};

int main (int argc , char *argv[]) {
	item it;
	assert( !it.next() ); // unsatisfiable constraints (data < 0) and (data > 0)
	
	it.disable_constraint("neg_data");
	for (int i = 0; i < 10; i++) {
		it.next();
		std::cout << it << std::endl;
	}

	std::cout << "***********************" << std::endl;

	it.enable_constraint("neg_data");
	it.disable_constraint("pos_data");
	for (int i = 0; i < 10; i++) {
		it.next();
		std::cout << it << std::endl;
	}


	return 0;
}
