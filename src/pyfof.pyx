# -*- coding: utf-8 -*-
"""
Created on Thu Mar 26 17:59:28 2015

@author: simongibbons
"""

__all__ = ["friends_of_friends"]
__version__ = "0.1.3-dev"
__author__ = "Simon Gibbons (simongibbons@gmail.com)"
__copyright__ = "Copyright 2015 Simon Gibbons"

cimport numpy as np
import numpy as np
from libcpp.vector cimport vector

cdef extern from "fof.hpp":
    cdef vector[vector[size_t]] _friends_of_friends "friends_of_friends"(double*, size_t, size_t, double) except +

cdef extern from "fof_brute.hpp":
    cdef vector[vector[size_t]] _friends_of_friends_brute "friends_of_friends_brute"(double*, size_t, size_t, double) except +


def friends_of_friends(data, double linking_length, bint use_brute = False):
    """ Computes friends-of-friends clustering of data. Distances are computed
    using a euclidian metric.

        :param data: A numpy array with dimensions (npoints x ndim)

        :param linking_length: The linking length between cluster members

        :param use_brute: Use the brute force, non rtree code path

        :rtype: A list of lists of indices in each cluster type
    """

    cdef np.ndarray[double, ndim=2, mode='c'] data_array = np.asarray(
        data,
        order='C',
        dtype=np.float,
    )

    if np.any( np.isnan(data) ):
        raise ValueError("NaN detected in pyfof")

    num_points = data_array.shape[0]
    num_dimensions = data_array.shape[1]

    if num_points == 0:
        return []

    if use_brute:
        return _friends_of_friends_brute(
            &data_array[0,0],
            num_points,
            num_dimensions,
            linking_length,
        )
    else:
        return _friends_of_friends(
            &data_array[0,0],
            num_points,
            num_dimensions,
            linking_length,
        )
