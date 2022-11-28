#pragma once

#include <vector>

using std::size_t;

std::vector< std::vector<size_t> > friends_of_friends_brute(double* data, size_t npts, size_t ndim, double linking_length);
