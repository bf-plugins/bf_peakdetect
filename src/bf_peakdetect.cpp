#include <bifrost/array.h>
#include <bifrost/common.h>
#include <bifrost/ring.h>
#include "cuda.hpp"
#include <utils.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "fof.hpp"
#include "fof_brute.hpp"

#include "bf_peakdetect.h"

BFstatus PeakDetect(BFarray *bf_data, double linking_length)
{
    BFarray bf_peaks; // Create empty output vector
    
    // get data and Ndims from BFarray input
    float* data = (float *)bf_data->data;
    int num_points = bf_data->shape[0];
    int num_dimensions = bf_data->shape[1];
    
    // Run the FoF algorithm
    std::vector< std::vector<float> > result = friends_of_friends(double *data, size_t npts, size_t ndim, double linking_length);
    
    // TODO: Find centroid or max value
    // TODO: Return bifrost array of maxima
    
    bf_peaks.dtype = BF_DTYPE_I32;
    bf_peaks.space = BF_SPACE_SYSTEM;
    bf_peaks.ndim = 1;
    bf_peaks.shape[0] = N;
    BF_CHECK(bfArrayMalloc(&bf_peaks));
    
    return BF_STATUS_SUCCESS;
}