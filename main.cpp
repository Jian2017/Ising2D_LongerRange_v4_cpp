#include <iostream>
#include "ising_class.h"
#include "spin_next.h"

int main(int argc, char const *argv[]) {

  Para e1(0, 0.45,0.45, 32,32);

  for (size_t i = 0; i < 30000; i++) {

    e1.spin_next();
    std::cout << i << '\t';

    std::cout << e1.test_print() << '\n';


  }





  return 0;
}
