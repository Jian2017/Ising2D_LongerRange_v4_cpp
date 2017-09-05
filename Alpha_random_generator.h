#ifndef ALPHA_RANDOM_GENERATOR
#define ALPHA_RANDOM_GENERATOR



#include <vector>
#include <cmath>
#include "my_random.h"
#define PI 3.14159265358979323846

void Alpha_random_generator(std::vector<int> & rand_v, int N0, double alpha){
  rand_v.clear();
  std::vector<double> K_P(N0);


  for (size_t i = 1; i < N0; i++) {
    K_P[i]=(alpha/2.0)*pow( PI/N0 ,2)/ (  pow( sin(PI*i/N0) ,2)  );
  }

  for (size_t i = 1; i < N0; i++) {
    K_P[i]=1-exp(-2.0*K_P[i]);
  }
  //this can be stored as Class variable
  // to save the repition

  for (size_t i = 1; i < N0; i++) {
    if ( rand_unit() < K_P[i]  ) {
      rand_v.push_back(i);
    }
  }



}


#endif
