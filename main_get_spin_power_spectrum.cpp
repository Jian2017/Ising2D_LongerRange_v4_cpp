#include <iostream>
#include "ising_class.h"  //Para e1(xxxxx),  for construct our monte carlo process
#include "spin_next.h"  //spin_next()
#include "get_spin_power_spectrum.h"  // get_spin_power_spectrum(),    and spin_power_spectrum

#include "stat_class.h"

int main(int argc, char const *argv[]) {
  Para e1(0.05, .136, 0.3, 64,32);
  Stat s1(28, 64,32);   // 19 is the number of log bins
  for (size_t i = 0; i <s1.total_steps; i++) {  // total_steps is 2^(19+1)
    for (size_t j = 0; j <50; j++) {    // 20 should be the correlation time steps
      e1.spin_next();
    }
    e1.get_spin_power_spectrum();
    s1.pushw(e1.spin_power_spectrum);
  //  std::cout << s1.current_bin_index << '\n';
    // pushw, of course should push
    // but also call to stat, call to save at appropriate time
  }

  return 0;
}
