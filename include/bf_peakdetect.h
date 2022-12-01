#include <bifrost/common.h>
#include <bifrost/array.h>
#include "fof.hpp"

#ifdef __cplusplus
extern "C" {
#endif

BFarray PeakDetect(BFarray *bf_data, double linking_length);

#ifdef __cplusplus
} // extern "C"
#endif
