# code

cimport libvd_py
import numpy as np
cimport numpy as np

cdef class BIC:

  cdef double (*distance_cfunc) (double*, double*)

  def __cinit__(self):
    self.distance_cfunc = libvd_py.bic_distance

  def extract (self, np.ndarray[np.uint8_t, ndim=3, mode='c'] img):
    cdef np.ndarray[np.float64_t, ndim=1, mode='c'] desc

    if img.shape[2] != 3:
      raise Exception("Wrong dimension - It must be a RGB image (*,*,3)")

    desc = np.empty(128, dtype=np.float64)
    libvd_py.bic_extract (<unsigned char*>img.data, <int>img.shape[1], <int>img.shape[0], <double*>desc.data)
    return desc

  def distance (self, np.ndarray[np.float64_t, ndim=1, mode='c'] bic1, np.ndarray[np.float64_t, ndim=1, mode='c'] bic2):
    if bic1.shape[0] != 128 or bic2.shape[0] != 128:
      raise Exception("Wrong BIC descriptor size")

    return libvd_py.bic_distance (<double*>bic1.data, <double*>bic2.data)
