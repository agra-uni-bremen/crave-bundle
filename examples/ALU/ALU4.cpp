#include <crave/SystemC.hpp>
#include <crave/ConstrainedRandom.hpp>
#include <systemc.h>
#include <boost/timer.hpp>

using crave::rand_obj;
using crave::randv;
using sc_dt::sc_bv;
using sc_dt::sc_uint;

/**
 * ALU:
 * complete enumerated there are:
 * ADD 0x0: 136
 * SUB 0x1: 136
 * MUL 0x2:  76
 * DIV 0x3: 240
 * valid assignments.
 */
struct ALU4 : public rand_obj {
randv< sc_bv<2> >  op ;
  randv< sc_uint<4> > a, b ;

  ALU4()
  : op(this), a(this), b(this)
  {
    constraint ( (op() != (unsigned char)0x0) || ( (unsigned char)15 >= a() + b() ) );
    constraint ( (op() != (unsigned char)0x1) || (((unsigned char)15 >= a() - b()) && (b() <= a()) ) );
    constraint ( (op() != (unsigned char)0x2) || ( (unsigned char)15 >= a() * b() ) );
    constraint ( (op() != (unsigned char)0x3) || ( b() != (unsigned char)0        ) );
  }

  friend std::ostream & operator<< (std::ostream & o, ALU4 const & alu) 
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
  ALU4 c;
  std::cout << "first: " << timer.elapsed() << "\n";
  for (int i=0; i<1000; ++i) {
    c.next();
    //std::cout << i << ": " << c << std::endl;
  }
  std::cout << "complete: " << timer.elapsed() << "\n";
  return 0;
}


