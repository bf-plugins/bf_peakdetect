from .libbf_peakdetect_wrapper import PeakDetect
import numpy as np 
import bifrost as bf

def peak_detect(input_data: bf.ndarray, link_length: float) -> bf.ndarray:
    """ Detect peaks from output of boxcar code 

    Args:
        input_arr (bf.ndarray): Input array. Should be list of 
                                [X index, Y index, SNR, boxcar_width]
    
    Returns:
        peaks (bf.ndarray): Peaks detected [X index, Y index, SNR, boxcar_width]
    """
    if str(input_data.dtype) != 'float64':
        print("Warning: recasting to float64")
        input_data = bf.ndarray(np.asarray(input_data).astype('float64'), dtype='f64')
    if input_data.shape[1] != 4:
        raise RuntimeError("Input array must be (Nx4) in shape")

    _peaks = PeakDetect(input_data.as_BFarray(), link_length)
    peaks  = bf.ndarray(_peaks)
    return peaks
