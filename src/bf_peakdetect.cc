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
    bf_peaks.dtype = BF_DTYPE_F32;
    bf_peaks.space = BF_SPACE_SYSTEM;
    bf_peaks.ndim = 2;
    bf_peaks.shape[0] = peaks.size();
    bf_peaks.data = peaks.data();
    
    return bf_peaks;
}

}
