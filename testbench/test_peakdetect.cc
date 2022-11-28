
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "peakdetect.hpp"
#include <boost/multi_array.hpp>

int factorial(int number) { return number <= 1 ? number : factorial(number - 1) * number; }

TEST_CASE("Test suite for peak detection") {
    CHECK(factorial(1) == 1);

  double input_data[][4] = {
         { 19.      , 493.      ,  62.166145,   0.      },
         { 18.      , 494.      ,  37.214165,   0.      },
         { 20.      , 492.      ,  37.28009 ,   0.      },
         { 16.      , 494.      ,  30.877373,   1.      },
         { 20.      , 492.      ,  44.028553,   1.      },
         { 19.      , 492.      ,  44.023758,   1.      },
         { 21.      , 492.      ,  35.27555 ,   1.      },
         { 17.      , 493.      ,  35.253258,   1.      },
         { 22.      , 491.      ,  30.816935,   1.      },
         { 18.      , 493.      ,  43.97715 ,   1.      },
         { 19.      , 493.      ,  43.981934,   1.      },
         { 19.      , 492.      ,  30.983809,   2.      },
         { 17.      , 492.      ,  31.328333,   2.      },
         { 20.      , 492.      ,  30.940197,   2.      },
         { 18.      , 492.      ,  31.30946 ,   2.      },
         { 19.      , 490.      ,  31.29538 ,   2.      },
         { 20.      , 490.      ,  31.233295,   2.      },
         { 22.      , 490.      ,  30.90926 ,   2.      },
         { 21.      , 490.      ,  31.212713,   2.      },
         {  0.      ,   0.      ,   8.      ,   0.      },
         {  1.      ,   1.      ,   10.      ,   0.      },
         {  0.      ,   0.      ,   0.      ,   0.      },
         {  0.      ,   0.      ,   0.      ,   0.      },
         {  0.      ,   0.      ,   0.      ,   0.      },
  };
  

  const size_t npts_input = 24;
  const size_t ndim_input = 4;
  double linking_length = 4.0;

  // Multi array from existing array
  boost::multi_array_ref<double, 2> input_arr{(double *)input_data, boost::extents[npts_input][ndim_input]};
  
  // TEST: Count hits
  CHECK(count_hits(input_arr, npts_input) == 21);  // 21 non-zero entries in input_arr

  //TEST: peak_detect
  auto peak_arr = peak_detect(input_arr, npts_input, ndim_input, linking_length);
  CHECK(peak_arr.size() == 2); 
  CHECK(peak_arr.num_elements() == 8); 
  CHECK(peak_arr.num_dimensions() == 2); 

  // Max value in input array is 19, 493 for first group (index 0), and 1, 1 (index 20)
  CHECK(peak_arr[0][0] == input_arr[0][0]);
  CHECK(peak_arr[0][1] == input_arr[0][1]);
  CHECK(peak_arr[1][0] == input_arr[20][0]);
  CHECK(peak_arr[1][0] == input_arr[20][0]);

  //std::cout << "a.shape(): " << peak_arr.shape() << std::endl;
  //std::cout << "a.num_elements(): " << peak_arr.num_elements() << std::endl;
  //std::cout << "a.size(): " << peak_arr.size() << std::endl;
  //std::cout << "a.num_dimensions(): " <<  peak_arr.num_dimensions() << std::endl;
  //std::cout << "Max index: " << peak_arr[0][0] << peak_arr[0][1] << std::endl;

}