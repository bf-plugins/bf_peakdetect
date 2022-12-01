#include <bifrost/array.h>
#include <bifrost/common.h>
#include <bifrost/ring.h>
#include <iostream>
#include <boost/multi_array.hpp>
#include "bf_peakdetect.h"
#include <cstring>

// Need to typedef a 2D array
#include "boost/multi_array.hpp"
typedef boost::multi_array<double, 2> array_type_2D;

//#define DEBUG 1

extern "C" {

BFarray bfArrayCreate(BFspace space, BFdtype dtype, int ndim ) {
    BFarray bf_arr; // Create empty output vector
    bf_arr.dtype = dtype;
    bf_arr.space = space;
    bf_arr.ndim  = ndim;

    // Setup shape and strides: max_dim is 8
    const size_t BF_MAX_DIMS = 8;

    // Set all dims to zero to start
    for (unsigned long i = 0; i < BF_MAX_DIMS; i++) {
        bf_arr.shape[i] = 0;
        bf_arr.strides[i] = 0;
    }

    return bf_arr;
}

// Count number of hits in input array 
// Finds first zero-valued entry and returns index
size_t count_hits(array_type_2D input_arr, size_t npts_input) {
  size_t npts = 1;
  for (uint i = 1; i < npts_input; i++) {
    npts = i;
    if(input_arr[i][2] < 0.001) {
      break;
    } 
  }
  return npts;
}

BFarray PeakDetect(BFarray *bf_data, double linking_length) {

  // get data and Ndims from BFarray input
  double* dataptr = (double *)bf_data->data;
  const int num_points = bf_data->shape[0];
  const int num_dimensions = 4;
  boost::multi_array_ref<double, 2> input_arr{(double *)dataptr, boost::extents[num_points][num_dimensions]};

  // Get rid of zeros 
  const size_t ndim = 2;
  const size_t npts = count_hits(input_arr, num_points);

  // Split off data indexes for FoF algorithm
  //double idx_arr[npts][ndim];
  array_type_2D idx_arr(boost::extents[npts][ndim]);  
  double vals_arr[npts];
  //int boxcar_arr[npts];

  // Copy over from input data to index array
  for (uint i = 0; i < npts; i++) {
    idx_arr[i][0] = input_arr[i][0];
    idx_arr[i][1] = input_arr[i][1];
    vals_arr[i]   = input_arr[i][2];
    //boxcar_arr[i]  = input_arr[i][3];
  }

  // Setup for FoF algorithm
  double* data = idx_arr.data();

  // Run friends of friends
  //std::vector< std::vector<size_t> > v;
  auto v = friends_of_friends(data, npts, ndim, linking_length);
  
  #ifdef DEBUG
  std::cout << "Size: " << v.size() << std::endl;
  #endif


  // Create boost array for detected maxima
  const uint n_groups =  v.size();
  array_type_2D maxidx_arr(boost::extents[n_groups][num_dimensions]);  

  // Loop through all groups
  for (uint i = 0; i < v.size(); i++) {
    uint v_idx = 0;
    double maxval = 0; 
    double curval = 0;
    uint maxidx   = 0;
    uint loop_idx = 0;

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
    
    //#ifdef DEBUG
    //std::cout << std::endl;
    //#endif 

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

  // Create array
  BFarray bf_peaks = bfArrayCreate(BF_SPACE_SYSTEM, BF_DTYPE_F64, 2);
  bf_peaks.shape[0]   = maxidx_arr.size();
  bf_peaks.shape[1]   = num_dimensions;
  bf_peaks.strides[0] = 8 * num_dimensions;
  bf_peaks.strides[1] = 8;

  // Copy data over
  bfArrayMalloc(&bf_peaks);
  long size_bytes = bf_peaks.strides[0] * bf_peaks.shape[0];
  memcpy(bf_peaks.data, maxidx_arr.data(), size_bytes);

  return bf_peaks;

}

} // extern C
