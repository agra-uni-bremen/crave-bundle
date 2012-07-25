#include <crave/ConstrainedRandom.hpp>

using crave::randv;
using crave::DefaultGenerator;

int main (int argc , char *argv[]) {
	randv<int> x(NULL);
	randv<int> y(NULL);
	DefaultGenerator gen;
	gen
		(x() >= 0 && y() >= 0)
		(x() + y() == 4)
		(x() * y() == 4);

	assert(gen.next());
	std::cout << x << " " << y << std::endl;

	return 0;
}
