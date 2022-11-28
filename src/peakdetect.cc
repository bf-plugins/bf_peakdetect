#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "peakdetect.hpp"

#define DEBUG 1

// Count number of hits in input array 
// Finds first zero-valued entry and returns index
size_t count_hits(double input_arr[][4], size_t npts_input) {
  size_t npts = 1;
  for (uint i = 1; i < npts_input; i++) {
    npts = i;
    if(input_arr[i][2] < 0.001) {
      break;
    } 
  }
  return npts;
}

// input_arr [img X, img Y, img val, boxcar_width]
// npts_input is len(input_arr)
// ndim_input is input_arr.shape[1]
// linking_length is distance for FoF linking
int peak_detect(double input_arr[][4], int npts_input, int ndim_input, double linking_length){
  size_t ndim = 2;
  size_t npts = count_hits(input_arr, npts_input);

  #ifdef DEBUG
  std::cout << "Num points: " << npts << std::endl;
  #endif

  // Split off data indexes and 
  double idx_arr[npts][ndim];
  double vals_arr[npts];
  //int boxcar_arr[npts];

  for (uint i = 0; i < npts; i++) {
    idx_arr[i][0] = input_arr[i][0];
    idx_arr[i][1] = input_arr[i][1];
    vals_arr[i]    = input_arr[i][2];
    //boxcar_arr[i]  = input_arr[i][3];
  }

  // Setup for FoF algorithm
  double* data = (double *)idx_arr;

  // Run friends of friends
  std::vector< std::vector<size_t> > v;
  v = friends_of_friends(data, npts, ndim, linking_length);
  
  std::cout << "Size: " << v.size() << std::endl;

  // Create index array for detected maxima 
  double maxidx_arr[v.size()][ndim];
  
  // Loop through all groups
  for (uint i = 0; i < v.size(); i++) {
    uint v_idx = 0;
    double maxval = 0; 
    double curval = 0;
    uint maxidx   = 0;
    uint loop_idx;
      // Look through group for max value
      for (auto it = v[i].begin(); it != v[i].end(); it++) {
        loop_idx = std::distance(v[i].begin(), it);
        v_idx = *it;
        curval = vals_arr[v_idx];
        if (curval > maxval) {
          maxval = curval;
          maxidx = (int)std::round(v_idx);
        }
        #ifdef DEBUG
        std::cout << *it << " ";
        #endif
      }
      #ifdef DEBUG
      std::cout << std::endl;
      #endif 

      maxidx_arr[i][0] = input_arr[maxidx][0]; // X
      maxidx_arr[i][1] = input_arr[maxidx][1]; // Y 
      maxidx_arr[i][2] = input_arr[maxidx][2]; // Value
      maxidx_arr[i][3] = input_arr[maxidx][3]; // Boxcar width 

      #ifdef DEBUG
      std::cout << "Max index: " << maxidx << " val: " << maxval << std::endl;
      std::cout << "Index: " << idx_arr[maxidx][0] << ", " << idx_arr[maxidx][1] << std::endl;
      //std::cout << "Boxcar: " << boxcar_arr[maxidx]  << std::endl;
      #endif
  }

  return 0;
}