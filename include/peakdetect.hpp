#pragma once
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <bifrost/array.h>
#include <bifrost/common.h>
#include <bifrost/ring.h>

// Friends of friends
#include "fof.hpp"

// Need to typedef a 2D array
#include "boost/multi_array.hpp"
typedef boost::multi_array<double, 2> array_type_2D;

size_t count_hits(array_type_2D input_arr, size_t npts_input);
BFarray PeakDetect(BFarray *bf_data, double linking_length);
