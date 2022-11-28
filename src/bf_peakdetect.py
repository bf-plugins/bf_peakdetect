from bifrost.libbifrost import _check, _get, BifrostObject
from bifrost.ndarray import asarray

import bf_peakdetect_generated as _gen

class BfPeakdetect(BifrostObject):
    def __init__(self):
        BifrostObject.__init__(self, _gen.BfPeakdetectCreate, 
                               _gen.BfPeakdetectDestroy)
    def init(self):
        _check(_gen.BfPeakdetectInit(self.obj))

    def execute(self, in_BFarray, out_BFarray):
        _check(_gen.BfPeakdetectExecute(self.obj, asarray(in_BFarray).as_BFarray(),
                                asarray(out_BFarray).as_BFarray()))
        return out_BFarray

    def set_stream(self, stream_ptr_generic):
        _check(_gen.BfPeakdetectSetStream(self.obj, stream_ptr_generic))

    def reset_state(self):
        _check(_gen.BfPeakdetectResetState(self.obj))