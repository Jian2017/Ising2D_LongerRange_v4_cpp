#ifndef GET_SPIN_POWER_SPECTRUM
#define GET_SPIN_POWER_SPECTRUM

#include "ising_class.h"
#include <fftw3.h>


void Para :: get_spin_power_spectrum(){

  for (size_t i = 0; i < spinsize; i++) {
    in[i][0]=spin[i];
    in[i][1]=0.0;
  }

  fftw_execute(p); /* FFT */


  for (size_t i = 0; i < spinsize; i++) {
    spin_power_spectrum[i]=out[i][0]*out[i][0]+out[i][1]*out[i][1];
  }


}




#endif
