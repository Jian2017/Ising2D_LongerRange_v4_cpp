#ifndef NEXT_NEIGHBOR_H
#define NEXT_NEIGHBOR_H

#include <vector>
#include <iostream>
#include <cmath>
#include "ising_class.h"
#include "my_random.h"
#include "Alpha_random_generator.h"



int Para :: vector2int(std::vector<int>  &site ){
  //Fortran ordering
  int result=0;
  int temp=1;
  for (int i = 0; i < dimension; i++) {
    temp=1;
    for (int  k= 0; k < i; k++) {
      temp=temp*N[k];
    }
    result=result+temp*site[i];
  }

  return result;
}

void Para :: int2vector(int num, std::vector<int> & site ){
  site.clear();
  int prod=1;
  for (int i = dimension-1; i > -1; i--) {
    prod=1;
    for (int k = 0; k < i; k++) {
      prod=prod*N[k];
    }
    site.insert(site.begin(),(int)num/prod);
    num=num%prod;
  }

}


int Para :: intMint(int num,int d_index,int steps){
  std::vector<int> num_v;
  int2vector(num, num_v );

  int temp=num_v[d_index] + steps;
  while (temp<0) {
    temp=temp+N[d_index];
  }
  num_v[d_index]= temp%N[d_index];


  return vector2int(num_v);

}



void Para :: next_growing_neighbor(std::vector<int> & output){

}


void Para :: next_growing_neighbor(std::vector<int> & output, int site){
  output.clear();
  for (int i = 0; i < dimension; i++) {
    if ( rand_unit()>exp(-2.0*K[i]) ) {
      output.push_back( intMint(site,i,1)  );
    }
    if ( rand_unit()>exp(-2.0*K[i]) ) {
      output.push_back( intMint(site,i,-1)  );
    }
  }



  if ( isLongerRange ) {
    std::vector<int> longRange_direction;
    Alpha_random_generator(longRange_direction, N[0], A);

    for (size_t i = 0; i < longRange_direction.size(); i++) {
      output.push_back(   intMint(site,0, longRange_direction[i] )       );
    }
  }




}





#endif
