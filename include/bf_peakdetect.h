#include <bifrost/common.h>
#include <bifrost/array.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct bf_peakdet* bfplugin;

BFstatus BfPeakdetectCreate(bfplugin* plan_ptr);
BFstatus BfPeakdetectInit(bfplugin  plan,
                  int   n_param1,
                  int   n_param2);
BFstatus BfPeakdetectSetStream(bfplugin plan,
                       void const* stream);
BFstatus BfPeakdetectResetState(bfplugin plan);
BFstatus BfPeakdetectExecute(bfplugin plan,
                     BFarray const* in,
                     BFarray*       out);
BFstatus BfPeakdetectDestroy(bfplugin plan);

#ifdef __cplusplus
} // extern "C"
#endif
