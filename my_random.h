#ifndef MY_RANDOM
#define MY_RANDOM

#include <iostream>
#include <random>

std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(1,2);
std::uniform_real_distribution<double> disUnit(0.0,1.0);


int rand_pm(){
  return 3-distribution(generator)*2;
}

int rand_n(int n){
  std::uniform_int_distribution<int> dis(1,n);

  return dis(generator)-1;
}

double rand_unit(){
  return disUnit(generator);
}



#endif
