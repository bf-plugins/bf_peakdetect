#include <bifrost/array.h>
#include <bifrost/common.h>
#include <bifrost/ring.h>
#include "bf_peakdetect.h"
#include "peakdetect.hpp"


extern "C" {

BFarray bfPeakDetect(BFarray *bf_data, double link_length) {
  BFarray bf_peaks = PeakDetect(bf_data, link_length);
  return bf_peaks;
}

} // extern C
