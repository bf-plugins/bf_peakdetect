from bf_peakdetect import PeakDetect
import bifrost as bf
import numpy as np

input_data = bf.ndarray(np.array([
        [ 19.      , 493.      ,  69.166145,   0.     ],
        [ 18.      , 494.      ,  37.214165,   0.     ],
        [ 20.      , 492.      ,  37.28009 ,   0.     ],
        [ 16.      , 494.      ,  30.877373,   1.     ],
        [ 20.      , 492.      ,  44.028553,   1.     ],
        [ 19.      , 492.      ,  44.023758,   1.     ],
        [ 21.      , 492.      ,  35.27555 ,   1.     ],
        [ 17.      , 493.      ,  35.253258,   1.     ],
        [ 22.      , 491.      ,  30.816935,   1.     ],
        [ 18.      , 493.      ,  43.97715 ,   1.     ],
        [ 19.      , 493.      ,  43.981934,   1.     ],
        [ 19.      , 492.      ,  30.983809,   2.     ],
        [ 17.      , 492.      ,  31.328333,   2.     ],
        [ 20.      , 492.      ,  30.940197,   2.     ],
        [ 18.      , 492.      ,  31.30946 ,   2.     ],
        [ 19.      , 490.      ,  31.29538 ,   2.     ],
        [ 20.      , 490.      ,  31.233295,   2.     ],
        [ 22.      , 490.      ,  30.90926 ,   2.     ],
        [ 21.      , 490.      ,  31.212713,   2.     ],
        [  0.      ,   0.      ,   8.      ,   0.     ],
        [  1.      ,   1.      ,   10.      ,   0.    ],
        [  0.      ,   0.      ,   0.      ,   0.     ],
        [  0.      ,   0.      ,   0.      ,   0.     ],
        [  0.      ,   0.      ,   0.      ,   0.     ],
], dtype='float64'))

linking_length = 4.0

peaks = PeakDetect(input_data.as_BFarray(), linking_length)

print(f"Shape: [{peaks.shape[0]}, {peaks.shape[1]}]")
print(f"Strides: [{peaks.strides[0]}, {peaks.strides[1]}]")
print(f"Dtype: {peaks.dtype} space {peaks.space} ndim {peaks.ndim}")

shape  = (peaks.shape[0], peaks.shape[1])
strides = (peaks.strides[0], peaks.strides[1])

b = bf.ndarray.__new__(bf.ndarray,
                    space='system',
                    buffer=int(peaks.data),
                    shape=shape,
                    dtype='f64',
                    strides=strides)

print(b)