#ifndef STAT_CLASS_H
#define STAT_CLASS_H


#include <iostream>
#include <vector>
#include <algorithm>    // std::transform
#include <cmath>

#include <fstream>
#include <string>


//on works for two dimensional case
class Stat{

public:
  int BINS;  // for example, 2^0  2^1 2^2 2^3 2^4  then BINS=5
  double total_steps; // 2^0 + 2^1 + 2^2 + 2^3 + 2^4 = 2^5 -1

  int N0;
  int N1;

  std::vector<double> temp;  // this will c

  int current_bin_index;
  double in_bin_index;

  std::vector< std::vector<double> > v;  //  log bins average values

  std::vector<double> v_best;  // this will c
  std::vector<double> v_error;  // this will c

  std::string filename="best.dat";
  std::ofstream savefile;



  Stat(int input_BINS, int input_N0, int input_N1){
    BINS=input_BINS;
    N0=input_N0;
    N1=input_N1;
    total_steps=pow(2,input_BINS);
    temp.assign( input_N0*input_N1  ,0.0);
    v_best.assign( input_N0*input_N1  ,0.0 );
    v_error.assign( input_N0*input_N1  ,0.0 );

    current_bin_index=0;
    in_bin_index=0.0;
  }


  void pushw(double * spin_power_spectrum){
    if (in_bin_index < pow(2,current_bin_index) )  {

      for (size_t i = 0; i < N0*N1; i++) {
        temp[i]+=spin_power_spectrum[i];
      }

      in_bin_index=in_bin_index+1;

    }
    else{

      for (size_t i = 0; i < N0*N1; i++) {
        temp[i]=temp[i]/pow(2,current_bin_index);
      }

      v.push_back(temp);


      if (current_bin_index>10) {
        get_best_error();
        save_current();
        std::cout << current_bin_index <<'\t'<<v_best[3] <<'\t'<<v_error[3] << '\n';
      }

      in_bin_index=0.0;
      current_bin_index=current_bin_index+1;   // attention here
      for (size_t i = 0; i < N0*N1; i++) {
        temp[i]=0.0;
      }

      pushw( spin_power_spectrum);

    }

  }


  void get_best_error(){
    for (size_t i = 0; i < N0*N1; i++) {
      v_best[i]=0.0;
      v_error[i]=0.0;
    }

    //only works for current_bin_index>5, better to be larger than 10;

    int binbin=5;

    double deno1=1.0;
    for (size_t i = current_bin_index; i > current_bin_index-binbin; i--) {
      deno1=pow(2, 1+current_bin_index-i );
      for (size_t j = 0; j < N0*N1; j++) {
        v_best[j]+=v[i][j] / deno1 ;
      }
    }
    deno1=1-1.0/pow(2,binbin);
    for (size_t i = 0; i < N0*N1; i++) {
      v_best[i]=v_best[i]/deno1;
    }


    for (size_t i = current_bin_index; i > current_bin_index-binbin; i--) {
      for (size_t j = 0; j < N0*N1; j++) {
        v_error[j]+=pow(v_best[j]-v[i][j],2);
      }
    }
    for (size_t j = 0; j < N0*N1; j++) {
      v_error[j]=sqrt(v_error[j]/binbin);
    }
  }


  void save_current(){
    filename.clear();
    filename+=std::to_string(current_bin_index);
    filename+="_best.dat";
    savefile.open(filename);
    for (size_t i = 0; i < N0*N1; i++) {
      savefile<< v_best[i]<<"\t";
    }
    savefile.close();


      filename.clear();
      filename+=std::to_string(current_bin_index);
      filename+="_error.dat";
      savefile.open(filename);
      for (size_t i = 0; i < N0*N1; i++) {
        savefile<< v_error[i]<<"\t";
      }
      savefile.close();
  }




};


#endif
