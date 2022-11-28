#pragma once
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "fof.hpp"

size_t count_hits(double input_arr[][4], size_t npts_input);
int peak_detect(double input_arr[][4], int npts_input, int ndim_input, double linking_length);
