#include <bifrost/array.h>
#include <bifrost/common.h>
#include <bifrost/ring.h>
#include <iostream>
#include <boost/multi_array.hpp>
#include "bf_peakdetect.h"
#include "peakdetect.hpp"

extern "C" {

BFarray PeakDetect(BFarray *bf_data, double linking_length)
{
    
    // get data and Ndims from BFarray input
    double* data = (double *)bf_data->data;
    const int num_points = bf_data->shape[0];
    const int num_dimensions = 4;

    boost::multi_array_ref<double, 2> input_arr{(double *)data, boost::extents[num_points][num_dimensions]};
    auto peaks = peak_detect(input_arr, num_points, num_dimensions, linking_length);
    
    BFarray bf_peaks; // Create empty output vector
    bf_peaks.dtype = BF_DTYPE_F64;
    bf_peaks.space = BF_SPACE_SYSTEM;
    bf_peaks.ndim = 2;

    // Setup shape and strides: max_dim is 8
    const size_t BF_MAX_DIMS = 8;

    for (unsigned long i = 0; i < BF_MAX_DIMS; i++) {
        bf_peaks.shape[i] = 0;
        bf_peaks.strides[i] = 0;
    }

    bf_peaks.shape[0]   = peaks.size();
    bf_peaks.shape[1]   = num_dimensions;
    bf_peaks.strides[0] = 8 * num_dimensions;
    bf_peaks.strides[1] = 8;
    bf_peaks.data       = peaks.data();

    return bf_peaks;
}

}
