#include <iostream>
#include "ising_class.h"  //Para e1(xxxxx),  for construct our monte carlo process
#include "spin_next.h"  //spin_next()
#include "get_spin_power_spectrum.h"  // get_spin_power_spectrum(),    and spin_power_spectrum

#include <string>     // std::string, std::stoi

#include "stat_class.h"

int main(int argc, char const *argv[]) {

	double A0=std::stod(argv[1]); //0.05
	double K0=std::stod(argv[2]); //.136
	double K1=std::stod(argv[3]); //0.3

	int N0=std::stoi(argv[4]); //64
	int N1=std::stoi(argv[5]); //32
	


  Para e1(A0,K0,K1,N0,N1);
  Stat s1(40,N0,N1);   // 40 is the number of log bins, 28 will take one week long, 2^(40/28) weeks
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
