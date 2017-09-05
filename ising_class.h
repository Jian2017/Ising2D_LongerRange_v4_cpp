#ifndef ISING_CLASS_H
#define ISING_CLASS_H

#include <vector>
#include <iostream>
#include "my_random.h"
#include <fftw3.h>

class Para{

public:
  std::vector<int> N;
  std::vector<double> K;
  double A;

  int dimension;
  int spinsize;
  bool isLongerRange;

  int * spin;
  double * spin_power_spectrum; //the multi-dimension FFT of spin, then square (real,symatric)
  fftw_complex *in, *out;
  fftw_plan p;


//this only works for one dimensional
  Para(double A0,double K0,int N0){
    N.push_back(N0);
    K.push_back(K0);
    A=A0;

    dimension=1;
    spinsize=N0;

    if (A0==0) {
      isLongerRange=false;
    }
    else{
      isLongerRange=true;
    }

    spin=new int[spinsize];
    spin_power_spectrum=new double[spinsize];

    spin_intialize();

  }

  //this only works for two dimensional
  Para(double A0,double K0,double K1,int N0,int N1){
      N.push_back(N0);
      N.push_back(N1);
      K.push_back(K0);
      K.push_back(K1);
      A=A0;

      dimension=2;
      spinsize=N0*N1;

      if (A0==0) {
        isLongerRange=false;
      }
      else{
        isLongerRange=true;
      }

      spin=new int[spinsize];
      spin_power_spectrum=new double[spinsize];

      in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * spinsize);
      out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * spinsize);
      p=  fftw_plan_dft_2d(N1,N0,in,out,FFTW_FORWARD,FFTW_ESTIMATE);


      spin_intialize();

    }

  //this only works for three dimensional
  Para(double A0,double K0,double K1,double K2,int N0,int N1,int N2){
        N.push_back(N0);
        N.push_back(N1);
        N.push_back(N2);
        K.push_back(K0);
        K.push_back(K1);
        K.push_back(K2);
        A=A0;

        dimension=3;
        spinsize=N0*N1*N2;

        if (A0==0) {
          isLongerRange=false;
        }
        else{
          isLongerRange=true;
        }

        spin=new int[spinsize];
        spin_power_spectrum=new double[spinsize];

        spin_intialize();

      }


  void  spin_intialize(){
    for (size_t i = 0; i < spinsize; i++) {
      spin[i]=rand_pm();
    }
  }


  void spin_next();

  void get_spin_power_spectrum();

  int vector2int(std::vector<int>  &site);
  void int2vector(int num, std::vector<int> & site);

  int intMint(int num,int d_index,int steps);

  void next_growing_neighbor(std::vector<int> & output);
  void next_growing_neighbor(std::vector<int> & output, int site);



  double test_print() {

    double sum=0.0;
    for (size_t i = 0; i < spinsize; i++) {
          sum+=1.0*spin[i];
    }

    return sum/spinsize ;
  }


};




#endif
