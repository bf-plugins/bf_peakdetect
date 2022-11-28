#pragma once
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "fof.hpp"

// Need to typedef a 2D array
#include "boost/multi_array.hpp"
typedef boost::multi_array<double, 2> array_type_2D;
typedef boost::multi_array<float, 2> float_array_type_2D;

size_t count_hits(array_type_2D input_arr, size_t npts_input);
array_type_2D peak_detect(array_type_2D input_arr, int npts_input, int ndim_input, double linking_length);
