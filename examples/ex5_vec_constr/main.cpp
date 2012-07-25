#include <crave/ConstrainedRandom.hpp>

using crave::rand_obj;
using crave::randv;
using crave::rand_vec;
using crave::_i;

#define IF_THEN(a, b) !(a) || (b)
#define IF_THEN_ELSE(a, b, c) (!(a) || (b)) && ((a) || (c))

class item : public rand_obj {
public:
	item(rand_obj* parent = 0) : rand_obj(parent), src_addr_vec(this), dest_addr_vec(this), data_vec(this), tmp(this) {
		tmp.range(5, 10);

		constraint(src_addr_vec().size() == reference(tmp));
		constraint.foreach(src_addr_vec, _i, src_addr_vec()[_i] < 0xFF);
		constraint.foreach(src_addr_vec, _i, src_addr_vec()[_i] % 4 == 0);
		constraint.unique(src_addr_vec);

		constraint(dest_addr_vec().size() == reference(tmp));
		constraint.foreach(dest_addr_vec, _i, IF_THEN(_i == 0, dest_addr_vec()[_i] < 0xF));
		constraint.foreach(dest_addr_vec, _i, dest_addr_vec()[_i] == dest_addr_vec()[_i - 1] + 8);
		constraint.unique(dest_addr_vec);

		constraint(data_vec().size() == 2 * reference(tmp));
		constraint.foreach(data_vec, _i, IF_THEN(_i % 2 == 0, data_vec()[_i] <= 10));
		constraint.foreach(data_vec, _i, IF_THEN(_i % 2 != 0, data_vec()[_i] == data_vec()[_i - 1] * data_vec()[_i - 1]));
	} 
     
	friend ostream& operator<<(ostream& os, item& it) { 
		os << "src_addr_vec = ";
		for (uint i = 0; i < it.src_addr_vec.size(); i++) 
			os << it.src_addr_vec[i] << " ";
		os << std::endl;
		os << "dest_addr_vec = ";
		for (uint i = 0; i < it.dest_addr_vec.size(); i++) 
			os << it.dest_addr_vec[i] << " ";
		os << std::endl;
		os << "data_vec = ";
		for (uint i = 0; i < it.data_vec.size(); i++) 
			os << it.data_vec[i] << " ";
		os << std::endl;
		return os; 
	}

	rand_vec<uint> src_addr_vec;
	rand_vec<uint> dest_addr_vec;
	rand_vec<uint> data_vec;
	randv<uint> tmp;
};

int main (int argc , char *argv[]) {
	item it;

	for (int i = 0; i < 10; i++) {
		it.next();
		std::cout << it << std::endl;
	}

	return 0;
}
