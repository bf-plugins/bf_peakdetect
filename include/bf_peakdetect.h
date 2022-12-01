#include <bifrost/common.h>
#include <bifrost/array.h>

#ifdef __cplusplus
extern "C" {
#endif

BFarray PeakDetect(BFarray *bf_data, double linking_length);
BFarray PeakDetect2(BFarray *bf_data, double linking_length);

#ifdef __cplusplus
} // extern "C"
#endif
