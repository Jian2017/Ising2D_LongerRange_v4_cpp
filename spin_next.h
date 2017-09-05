#ifndef SPIN_NEXT
#define SPIN_NEXT

#include "ising_class.h"
#include "next_neighbor.h"
#include "my_random.h"


void Para :: spin_next(){


  int * erdos=new int[spinsize];
  for (int i = 0; i < spinsize; i++) {
    erdos[i]=0;
  }

  int point_seed=rand_n(spinsize);
  int clusterSpin=spin[point_seed];
  erdos[point_seed]=1;

  std::vector<int> s1;
  std::vector<int> s2;

  std::vector<int> temp;

  s1.push_back(point_seed);

  while ( !(s1.empty()) ) {
    s2.clear();
    while ( !(s1.empty()) ) {


      temp.clear();
      next_growing_neighbor( temp, s1.back());

      for (int ich = 0; ich < temp.size(); ich++) {
        if ( spin[ temp[ich] ] == clusterSpin   ) {
          if (erdos[ temp[ich] ] == 0) {
              erdos[ temp[ich] ] =1;
              s2.push_back( temp[ich]  );
          }
        }
      }

      s1.pop_back();
    }

    s1.swap(s2);
  }


  for (int i = 0; i < spinsize; i++) {
    if (erdos[i]>0) {
      spin[i]=-spin[i];
    }
  }

  delete [] erdos;
}


#endif
