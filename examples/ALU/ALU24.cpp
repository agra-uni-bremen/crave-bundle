#include <crave/SystemC.hpp>
#include <crave/ConstrainedRandom.hpp>
#include <systemc.h>
#include <boost/timer.hpp>

using crave::rand_obj;
using crave::randv;
using sc_dt::sc_bv;
using sc_dt::sc_uint;

struct ALU24 : public rand_obj {
  randv< sc_bv<2> >  op ;
  randv< sc_uint<24> > a, b ;

  ALU24()
  : op(this), a(this), b(this)
  {
    constraint ( (op() != 0x0) || ( 16777215 >= a() + b() ) );
    constraint ( (op() != 0x1) || ((16777215 >= a() - b()) && (b() <= a()) ) );
    constraint ( (op() != 0x2) || ( 16777215 >= a() * b() ) );
    constraint ( (op() != 0x3) || ( b() != 0        ) );
  }

  friend std::ostream & operator<< (std::ostream & o, ALU24 const & alu) 
  {
    o << alu.op 
      << ' ' << alu.a
      << ' ' << alu.b
      ;
    return o;
  }
};

int sc_main (int argc, char** argv)
{
  boost::timer timer;
  ALU24 c;
  c.next();
  std::cout << "first: " << timer.elapsed() << "\n";
  for (int i=0; i<1000; ++i) {
    c.next();
  }
  std::cout << "complete: " << timer.elapsed() << "\n";
  return 0;
}
